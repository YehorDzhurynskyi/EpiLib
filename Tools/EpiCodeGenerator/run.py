import os
import logging
import argparse
import shutil

from epi_code_generator.tokenizer import Tokenizer
from epi_code_generator.inheritance_tree import InheritanceTree
from epi_code_generator.inheritance_tree import InheritanceError
from epi_code_generator.idlparser.idlparser import IDLParser
from epi_code_generator.code_generator import CodeGenerator
from epi_code_generator.code_generator import CodeGenerationError


logger = logging.getLogger()

def init_logger(log_level: int):

    logger.setLevel(log_level)

    formatter = logging.Formatter('[%(levelname)5s] %(message)s')

    stderr_handler = logging.StreamHandler()
    stderr_handler.setLevel(logging.INFO)
    stderr_handler.setFormatter(formatter)

    file_handler = logging.FileHandler('epi_code_generator.log', mode='w')
    file_handler.setLevel(log_level)
    file_handler.setFormatter(formatter)

    logger.addHandler(stderr_handler)
    logger.addHandler(file_handler)

if __name__ == "__main__":

    argparser = argparse.ArgumentParser()
    grp_required = argparser.add_argument_group('required')
    grp_optional = argparser.add_argument_group('optional')

    grp_required.add_argument(
        '-i',
        '--input-dir',
        type=str,
        required=True,
        help='TODO: fill'
    )

    grp_optional.add_argument(
        '-o',
        '--output-dir',
        type=str,
        help='TODO: fill'
    )

    grp_optional.add_argument(
        '--debug',
        action='store_true',
        help='TODO: fill'
    )

    grp_optional.add_argument(
        '--nobackup',
        action='store_true',
        help='TODO: fill'
    )

    args = argparser.parse_args()

    output_dir = args.output_dir if args.output_dir is not None else args.input_dir
    os.makedirs(output_dir, exist_ok=True)

    if args.debug:

        init_logger(logging.DEBUG)
        logger.info(f'Debug mode enabled')

    else:
        init_logger(logging.INFO)

    if not args.nobackup:

        from tempfile import TemporaryDirectory
        from tempfile import gettempdir
        from uuid import uuid1

        backupdir = f'{gettempdir()}/EpiCodeGenerator-{uuid1()}-backup'
        logger.info(f'Backup <input dir> into {backupdir}')
        shutil.copytree(args.input_dir, backupdir)

    logger.info(f'Input Dir: {args.input_dir}')
    logger.info(f'Output Dir: {output_dir}')

    registry_global = {}
    for root, _, files in os.walk(args.input_dir):

        for file in filter(lambda f: f.endswith('epi'), files):

            path = os.path.join(root, file)

            logger.info(f'Parsing: {file}')

            tokenizer = Tokenizer(root, file)
            tokens = tokenizer.tokenize()

            for t in tokens:
                logger.debug(str(t))

            parser = IDLParser(tokens)
            registry_local, errors_syntax = parser.parse()

            for e in errors_syntax:
                logger.error(str(e))

            if len(errors_syntax) != 0:
                exit(-1)

            registry_intersection = registry_global.keys() & registry_local.keys()
            if len(registry_intersection) == 0:
                registry_global = { **registry_global, **registry_local }
            else:

                for v in registry_intersection:
                    logging.error(f'{v} is already defined in {registry_global[v].token.filepath}')

                exit(-1)

    try:
        inherited_tree = InheritanceTree(registry_global)
    except InheritanceError as e:

        logger.error(str(e))
        exit(-1)

    code_generator = CodeGenerator(output_dir)
    for sym in registry_global.values():

        basename = os.path.splitext(sym.token.filepath)[0]

        try:
            code_generator.code_generate(sym, basename)
        except CodeGenerationError as e:

            logging.error(str(e))
            exit(-1)

    # TODO: check crc32 collisions
    code_generator.flush()
