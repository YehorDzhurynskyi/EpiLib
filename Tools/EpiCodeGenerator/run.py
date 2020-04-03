import os
import logging
import argparse

from epi_code_generator.tokenizer import Tokenizer
from epi_code_generator.inheritance_tree import InheritanceTree
from epi_code_generator.inheritance_tree import InheritanceTreeError
from epi_code_generator.idlparser.idlparser import Parser
from epi_code_generator.code_generator import CodeGenerator


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

    registry_global = {}
    for root, _, files in os.walk(args.input_dir):

        for file in filter(lambda f: f.endswith('epi'), files):

            path = os.path.join(root, file)

            logger.info(f'Parsing: {path}')

            tokenizer = Tokenizer(path)
            tokens = tokenizer.tokenize()

            for t in tokens:
                logger.debug(str(t))

            parser = Parser(tokens)
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
    except InheritanceTreeError as e:
        logger.error(str(e))

    output_dir = args.output_dir if args.output_dir is not None else args.input_dir
    code_generator = CodeGenerator(registry_global)
    code_generator.generate()
