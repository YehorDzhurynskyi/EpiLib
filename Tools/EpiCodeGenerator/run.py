import os
import logging

from epi_code_generator.tokenizer import Tokenizer
from epi_code_generator.parser import Parser
from epi_code_generator.symbol import EpiSymbolRegistry
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

    config = Config()
    config.parse_cmd()

    for root, _, files in os.walk(config.source_dir):

        for file in filter(lambda f: f.endswith('epi'), files):

            path = os.path.join(root, file)

            logger.info(f'Parsing: {path}')

            tokenizer = Tokenizer(open(path, "r").read())
            tokens = tokenizer.tokenize()

            for t in tokens:
                logger.debug(str(t))

            parser = Parser(tokens)
            registry, errors = parser.parse()

            for e in errors:
                logger.error(str(e))
