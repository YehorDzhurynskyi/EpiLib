import abc
from enum import Enum, auto

from .tokenizer import Tokenizer
from .tokenizer import Token
from .tokenizer import TokenType


class Attribute:

    PARAM_LISTS = {
        # NOTE: Common attributes
        TokenType.DllEntryAttr: '',

        # NOTE: Property attributes
        TokenType.OwnerAttr: '',
        TokenType.ReadOnlyAttr: '',
        TokenType.WriteOnlyAttr: '',
        TokenType.WriteCallbackAttr: '',
        TokenType.ReadCallbackAttr: '',
        TokenType.VirtualAttr: '',
        TokenType.AssertMinAttr: '@TokenType.IntegerLiteral|@TokenType.FloatingLiteral',
        TokenType.AssertMaxAttr: '@TokenType.IntegerLiteral|@TokenType.FloatingLiteral',
        TokenType.AssertMinMaxAttr: '(@TokenType.IntegerLiteral|@TokenType.FloatingLiteral){2}',
        TokenType.ForceMinAttr: '@TokenType.IntegerLiteral|@TokenType.FloatingLiteral',
        TokenType.ForceMaxAttr: '@TokenType.IntegerLiteral|@TokenType.FloatingLiteral',
        TokenType.ForceMinMaxAttr: '(@TokenType.IntegerLiteral|@TokenType.FloatingLiteral){2}',
        TokenType.NoDuplicateAttr: '',
        TokenType.TransientAttr: '',

        # NOTE: Class attributes
        TokenType.AdditionalInterfaceAttr: '(@TokenType.OpenQuote@TokenType.TextLiteral@TokenType.CloseQuote)+',
        TokenType.SerializationCallbackAttr: ''
    }
    assert len(PARAM_LISTS.keys()) == len(Tokenizer.BUILDIN_PRTY_ATTRS.keys() | Tokenizer.BUILDIN_CLSS_ATTRS.keys())

    def __init__(self, type):

        self.type = type
        self.params = []


class InvalidAttributeListError(Exception):
    pass


class Morpheme(abc.ABC):

    def __init__(self, name):

        self.name = name
        self.attrs = []

    @property
    def attrs(self):
        return self.__attrs

    @attrs.setter
    def attrs(self, attrs):

        if self._is_valid_attrs(attrs):
            self.__attrs = attrs
        else:
            raise InvalidAttributeListError

    @abc.abstractmethod
    def _is_valid_attrs(self, attrs):
        pass


class Method(Morpheme):

    def __init__(self, name):
        super(Method, self).__init__(name)

    def _is_valid_attrs(self, attrs):
        return False


class PropertySignature:

    class ViewType(Enum):

        Plain = auto()
        Reference = auto()
        Pointer = auto()

    def __init__(self, type):

        self.type = type
        self.view_type = PropertySignature.ViewType.Plain
        self.modifiers = []


class Property(Morpheme):

    def __init__(self, name, signature):

        super(Property, self).__init__(name)

        self.signature = signature
        self.value = self._default_value()

    def _default_value(self):

        value = None
        if self.view_type == PropertySignature.ViewType.Pointer:
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
            value = 'epiDebug_ONLY("Empty")'

        return value

    def _is_valid_attrs(self, attrs):
        return True


class Class(Morpheme):

    def __init__(self, name):

        super(Class, self).__init__(name)

        self.parent = None
        self.properties = []

    def _is_valid_attrs(self, attrs):
        return True


class Struct(Class):

    def __init__(self, name):
        super(Struct, self).__init__(name)


class Interface(Morpheme):

    def __init__(self, name):

        super(Interface, self).__init__(name)

        self.parent = None
        self.methods = []

    def _is_valid_attrs(self, attrs):
        return True


class EnumEntry(Morpheme):

    def __init__(self, name):
        super(EnumEntry, self).__init__(name)

    def _is_valid_attrs(self, attrs):
        return True


class Enum(Morpheme):

    def __init__(self, name):

        super(Enum, self).__init__(name)

        self.entries = []

    def _is_valid_attrs(self, attrs):
        return True


class Registry:

    def __init__(self):

        self.classes = []
        self.interfaces = []
        self.enums = []
        self.structs = []
