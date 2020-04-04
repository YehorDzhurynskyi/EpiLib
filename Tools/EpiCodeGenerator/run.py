import os
import logging
import argparse

from epi_code_generator.tokenizer import Tokenizer
from epi_code_generator.inheritance_tree import InheritanceTree
from epi_code_generator.inheritance_tree import InheritanceError
from epi_code_generator.idlparser.idlparser import IDLParser
from epi_code_generator.code_generator import code_generate


logger = logging.getLogger()
logger.setLevel(logging.DEBUG)

formatter = logging.Formatter('[%(levelname)5s] %(message)s')

stderr_handler = logging.StreamHandler()
stderr_handler.setLevel(logging.INFO)
stderr_handler.setFormatter(formatter)

file_handler = logging.FileHandler('epi_code_generator.log', mode='w')
file_handler.setLevel(logging.DEBUG)
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

    args = argparser.parse_args()

    output_dir = args.output_dir if args.output_dir is not None else args.input_dir

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

    os.makedirs(output_dir, exist_ok=True)
    for sym in registry_global.values():

        # printsym.token.filepath
        name = os.path.splitext(sym.token.filepath)[0]
        prefixpath = os.path.join(output_dir, name)
        code_generate(sym, prefixpath)
