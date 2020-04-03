import os
import logging
import argparse

from epi_code_generator.tokenizer import Tokenizer
from epi_code_generator.idlparser.idlparser import Parser
from epi_code_generator.code_generator import CodeGenerator
from epi_code_generator.config import Config


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

    argparser.add_argument(
        '-i',
        '--input-dir',
        type=str,
        required=True,
        help='TODO: fill'
    )

    args = argparser.parse_args()

    registry_global = {}
    for root, _, files in os.walk(args.input_dir):

        for file in filter(lambda f: f.endswith('epi'), files):

            path = os.path.join(root, file)

            logger.info(f'Parsing: {path}')

            with open(path, 'r') as f:

                tokenizer = Tokenizer(f.read())
                tokens = tokenizer.tokenize()

            for t in tokens:
                logger.debug(str(t))

            parser = Parser(tokens)
            registry_local, errors_syntax = parser.parse()

            for e in errors_syntax:
                logger.error(str(e))

            if len(errors_syntax) != 0:
                exit(-1)

            # TODO: check duplicates
            registry_global = { **registry_global, **registry_local }

    # Build inheritance tree
    # Check local and inherited duplications
    registry_global
