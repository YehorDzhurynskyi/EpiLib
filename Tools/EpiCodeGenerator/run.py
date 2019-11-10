import os
import logging

from epi_code_generator.tokenizer import Tokenizer
from epi_code_generator.parser import Parser
from epi_code_generator.morpheme import EpiRegistry
from epi_code_generator.code_generator import CodeGenerator
from epi_code_generator.config import Config


logger = logging.getLogger()

stderr_handler = logging.StreamHandler()
stderr_handler.setLevel(logging.DEBUG)

file_handler = logging.FileHandler('epi_code_generator.log')
file_handler.setLevel(logging.DEBUG)

logger.addHandler(stderr_handler)
logger.addHandler(file_handler)


if __name__ == "__main__":

    config = Config()
    config.parse_cmd()

    registry = EpiRegistry()

    for root, _, files in os.walk(config.source_dir):

        for file in filter(lambda f: f.endswith('epi'), files):

            path = os.path.join(root, file)

            logger.info(f'Parsing: {path}')

            tokenizer = Tokenizer(open(path, "r").read())
            tokens = tokenizer.tokenize()

            logger.debug('\n'.join(str(t) for t in tokens))

            parser = Parser(tokens)
            errors = parser.parse(registry)
            logger.error('\n'.join(str(e) for e in errors))
