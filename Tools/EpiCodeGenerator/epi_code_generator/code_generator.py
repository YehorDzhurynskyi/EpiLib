import os

from .symbol import EpiSymbol
from .symbol import EpiClass


class CodeGenerator:

    def __init__(self, symbol: EpiSymbol, filepath: str):

        assert isinstance(symbol, EpiClass)

        if not os.path.exists(filepath):
            with open(filepath, 'w+') as f:

