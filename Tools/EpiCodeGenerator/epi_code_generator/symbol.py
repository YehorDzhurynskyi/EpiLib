import abc
import sys
from enum import Enum, auto

from .tokenizer import Tokenizer
from .tokenizer import Token
from .tokenizer import TokenType


'''
class EpiAttribute:

    PARAM_RANGES = {
        # NOTE: Common attributes
        TokenType.DllEntryAttr: range(0, 1),

        # NOTE: Property attributes
        TokenType.OwnerAttr: range(0, 1),
        TokenType.ReadOnlyAttr: range(0, 1),
        TokenType.WriteOnlyAttr: range(0, 1),
        TokenType.WriteCallbackAttr: range(0, 1),
        TokenType.ReadCallbackAttr: range(0, 1),
        TokenType.VirtualAttr: range(0, 1),
        TokenType.AssertMinAttr: range(1, 2),
        TokenType.AssertMaxAttr: range(1, 2),
        TokenType.AssertMinMaxAttr: range(2, 3),
        TokenType.ForceMinAttr: range(1, 2),
        TokenType.ForceMaxAttr: range(1, 2),
        TokenType.ForceMinMaxAttr: range(2, 3),
        TokenType.NoDuplicateAttr: range(0, 1),
        TokenType.TransientAttr: range(0, 1),

        # NOTE: Class attributes
        TokenType.AdditionalInterfaceAttr: range(1, sys.maxsize),
        TokenType.SerializationCallbackAttr: range(0, 1)
    }
    assert len(PARAM_RANGES.keys()) == len(Tokenizer.BUILDIN_PRTY_ATTRS.keys() | Tokenizer.BUILDIN_CLSS_ATTRS.keys())

    def __init__(self, type):

        self.type = type
        self.params = []


class EpiInvalidAttributeListError(Exception):
    pass
'''

class EpiSymbol(abc.ABC):

    def __init__(self, name):

        self.name = name
'''
        self.attrs = []

    @property
    def attrs(self):
        return self.__attrs

    @attrs.setter
    def attrs(self, attrs):

        if self._is_valid_attrs(attrs):
            self.__attrs = attrs
        else:
            raise EpiInvalidAttributeListError

    @abc.abstractmethod
    def _is_valid_attrs(self, attrs):
        pass
'''

class EpiMethod(EpiSymbol):

    def __init__(self, name):

        super(EpiMethod, self).__init__(name)
        self.params = []

'''
    def _is_valid_attrs(self, attrs):
        return len(attrs) == 0
'''


class EpiVariable(EpiSymbol):

    class Form(Enum):

        Plain = auto()
        Pointer = auto()

    def __init__(self, name, type, form):

        self.name = name
        self.type = type
        self.form = form
        self.value = self._default_value()

    def _default_value(self):

        value = None
        if self.form == EpiVariable.Form.Pointer:
            value = 'nullptr'
        elif type == TokenType.BoolType:
            value = 'false'
        elif type in [
            TokenType.IntType,
            TokenType.UIntType,
            TokenType.ByteType,
            TokenType.SizeTType,
            TokenType.HashTType,
            TokenType.FloatingType
        ]:
            value = '0'
        elif type == TokenType.CharType:
            value = "'\\0'"
        elif type == TokenType.StringType:
            value = 'epiDEBUG_ONLY("Empty")'

        return value

'''
    def _is_valid_attrs(self, attrs):
        return True
'''


class EpiClass(EpiSymbol):

    def __init__(self, name):

        super(EpiClass, self).__init__(name)

        self.parent = None
        self.properties = []

'''
    def _is_valid_attrs(self, attrs):
        return True
'''


'''
class EpiInterface(EpiSymbol):

    def __init__(self, name):

        super(EpiInterface, self).__init__(name)

        self.parent = None
        self.methods = []

    def _is_valid_attrs(self, attrs):
        return True


class EpiEnumEntry(EpiSymbol):

    def __init__(self, name):
        super(EpiEnumEntry, self).__init__(name)

    def _is_valid_attrs(self, attrs):
        return True


class EpiEnum(EpiSymbol):

    def __init__(self, name):

        super(EpiEnum, self).__init__(name)

        self.entries = []

    def _is_valid_attrs(self, attrs):
        return True
'''
