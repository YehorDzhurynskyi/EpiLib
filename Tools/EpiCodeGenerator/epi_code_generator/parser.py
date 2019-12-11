from enum import Enum, auto

from .tokenizer import Tokenizer
from .tokenizer import Token
from .tokenizer import TokenType

from .symbol import EpiAttribute
from .symbol import EpiVariable
from .symbol import EpiProperty
from .symbol import EpiMethod
from .symbol import EpiClass
from .symbol import EpiEnumEntry
from .symbol import EpiEnum
from .symbol import EpiInterface


class SyntaxErrorCode(Enum):

    NoMatchingClosingBrace = auto()
    NoMatchingOpeningBrace = auto()
    NoMatchingClosingBracket = auto()
    NestedBracket = auto()
    UnexpectedToken = auto()
    UnexpectedKeywordUsage = auto()
    UnexpectedEOF = auto()
    IncorrectValueLiteral = auto()
    UnsupportedProperty = auto()
    MatchingTokenOnSameLine = auto()


SYNTAX_ERROR_MSGS = {
    SyntaxErrorCode.NoMatchingClosingBrace: "No matching closing brace for",
    SyntaxErrorCode.NoMatchingOpeningBrace: "No matching opening brace for",
    SyntaxErrorCode.NoMatchingClosingBracket: "No matching closing bracket for",
    SyntaxErrorCode.NestedBracket: "Nested brackets '[]', '()' are forbidden",
    SyntaxErrorCode.UnexpectedToken: "Unexpected token",
    SyntaxErrorCode.UnexpectedKeywordUsage: "Unexpected keyword usage",
    SyntaxErrorCode.UnexpectedEOF: "Unexpected end of file",
    SyntaxErrorCode.IncorrectValueLiteral: "Incorrect value literal",
    SyntaxErrorCode.UnsupportedProperty: "Specified property declaration is unsupported",
    SyntaxErrorCode.MatchingTokenOnSameLine: "Matching token should be located on same line"
}


class SyntaxError:

    def __init__(self, token, err_code, tip = ''):

        self.token = token
        self.err_code = err_code
        self.err_message = SYNTAX_ERROR_MSGS[err_code]
        self.tip = tip

    def __str__(self):
        return f'Syntax error {str(self.token)} message: "{self.err_message}"' + f' ({self.tip})' if len(self.tip) != 0 else ''


class Parser:

    def __init__(self, registry, tokens):

        self.registry = registry
        self.tokens = tokens
        self.__at = 0
        self.syntax_errors = []

    def _curr(self):
        return self.tokens[self.__at]

    def _next(self, next=1):

        self.__at += next - 1
        curr = self._curr()
        self.__at += 1

        return curr

    def parse(self):

        if self.tokens[-1].type != TokenType.EOF:

            self.syntax_errors.append(SyntaxError(self.tokens[-1], SyntaxErrorCode.UnexpectedEOF))
            return self.syntax_errors

        try:

            while True:

                t = self._curr()
                if t.type == TokenType.EOF:
                    break

                attrs = self._parse_attr_list() if t.type == TokenType.OpenSqBracket else []

                t = self._curr()

                if t.text not in Tokenizer.BUILDIN_USERTYPES:
                    assert False

                user_type = None
                registry_collection = None
                if t.type == TokenType.EnumType:
                    user_type = self._parse_enum()
                    registry_collection = self.registry.enums
                elif t.type == TokenType.ClassType:
                    user_type = self._parse_class()
                    registry_collection = self.registry.classes
                elif t.type == TokenType.InterfaceType:
                    user_type = self._parse_interface()
                    registry_collection = self.registry.interfaces

                if user_type:
                    user_type.attrs = attrs
                    registry_collection.append(user_type)

        except IndexError:
            assert False

        return self.syntax_errors

    def _parse_enum(self):

        t = self._next()
        if t.type != TokenType.EnumType:
            return None

        t = self._next()
        if t.type != TokenType.Identifier:
            return None

        enum = EpiEnum(t.text)

        t = self._next()
        if t.type != TokenType.OpenBrace:
            return None

        while True:

            t = self._curr()
            if t.type == TokenType.CloseBrace:
                break
            else:
                enum_entry = self._parse_enum_entry()
                if not enum_entry:
                    return None

                enum.entries.append(enum_entry)

        t = self._next(2)
        if t.type != TokenType.Semicolon:
            return None

        return enum

    def _parse_enum_entry(self):

        t = self._next()
        if t.type != TokenType.Identifier:
            return None

        return EpiEnumEntry(t.text)

    def _parse_interface(self):

        t = self._next()
        if t.type != TokenType.InterfaceType:
            return None

        t = self._next()
        if t.type != TokenType.Identifier:
            return None

        interface = EpiInterface(t.text)

        t = self._curr()
        if t.type == TokenType.Colon:

            t = self._next(2)
            if t.type != TokenType.Identifier:
                return None

            interface.parent = t.text

        t = self._next()
        if t.type != TokenType.OpenBrace:
            return None

        while True:

            t = self._curr()
            if t.type == TokenType.CloseBrace:
                self._next()
                break
            else:
                method = self._parse_method()
                if not method:
                    return None

                interface.methods.append(method)

        t = self._next()
        if t.type != TokenType.Semicolon:
            return None

        return interface

    def _parse_class(self):

        t = self._next()
        if t.type != TokenType.ClassType:

            self.syntax_errors.append(SyntaxError(t, SyntaxErrorCode.UnexpectedToken, 'Expected a \'class\' type'))
            return None

        t = self._next()
        if t.type != TokenType.Identifier:

            self._push_error_unexpected_token(t, 'Expected an \'identifier\'')
            return None

        clss = EpiClass(t.text)

        t = self._curr()
        if t.type == TokenType.Colon:

            t = self._next(2)
            if t.type != TokenType.Identifier:

                self._push_error_unexpected_token(t, 'Expected an \'identifier\'')
                return None

            clss.parent = t.text

        self._parse_scope(clss, [])

        t = self._next()
        if t.type != TokenType.Semicolon:

            self.syntax_errors.append(SyntaxError(t, SyntaxErrorCode.UnexpectedToken, 'Expected \';\''))
            return None

        return clss

    def _parse_scope(self, clss, attrs_inherent):

        t = self._next()
        if t.type != TokenType.OpenBrace:

            self.syntax_errors.append(SyntaxError(t, SyntaxErrorCode.UnexpectedToken, 'Expected \'{\''))
            return

        while True:

            t = self._curr()
            attrs = self._parse_attr_list() if t.type == TokenType.OpenSqBracket else []

            if self._is_next_variable():

                # NOTE: could be method

                prty = self._parse_property()
                if prty:
                    prty.attrs = attrs_inherent + attrs
                    clss.properties.append(prty)

            elif self._curr().type == TokenType.OpenBrace:

                self._parse_scope(clss, attrs_inherent + attrs)

            elif self._curr().type == TokenType.EnumType:

                nested_enum = self._parse_enum()
                if nested_enum:
                    nested_enum.attrs = attrs_inherent + attrs
                    self.registry.enums.append(nested_enum)


            else:
                break

        t = self._next()
        if t.type != TokenType.CloseBrace:

            self.syntax_errors.append(SyntaxError(t, SyntaxErrorCode.NoMatchingClosingBrace, 'Expected \'}\''))
            return

    def _parse_attr_list(self):

        attrs = []
        while True:

            t = self._curr()
            if t.type != TokenType.OpenSqBracket:
                break

            self._next()
            while self._curr().text in Tokenizer.BUILDIN_PRTY_ATTRS.keys() | Tokenizer.BUILDIN_CLSS_ATTRS.keys():

                attr = self._parse_attr()
                if not attr:
                    return None

                attrs.append(attr)

                t = self._curr()
                if t.type != TokenType.Comma:
                    break

                self._next()

            t = self._next()
            if t.type != TokenType.CloseSqBracket:
                return None

        return attrs

    def _parse_attr(self):

        a_t = self._next()

        attr = EpiAttribute(a_t.type)

        if self._curr().type != TokenType.OpenBracket:
            return attr

        ob_t = self._next()
        if ob_t.type != TokenType.OpenBracket:
            return None

        while self._curr().type != TokenType.CloseBracket:

            attr.params.append(self._next())
            t = self._curr()
            if t.type != TokenType.Comma:
                break

            self._next()

        cb_t = self._next()
        if cb_t.type != TokenType.CloseBracket:
            return None

        return attr

    def _parse_method(self):

        rt_t = self._parse_variable(has_name=False)
        if not rt_t:
            return None

        fn_t = self._next()
        if fn_t.type != TokenType.Identifier:
            return None

        method = EpiMethod(fn_t.text)

        t = self._next()
        if t.type != TokenType.OpenBracket:
            return None

        while self._is_next_variable():

            param = self._parse_variable(has_name=True)
            if not param:
                return None

            method.params.append(param)

            t = self._curr()
            if t.type != TokenType.Comma:
                break

            self._next()

        t = self._next()
        if t.type != TokenType.CloseBracket:
            return None

        t = self._next()
        if t.type != TokenType.Semicolon:
            return None

        return method

    def _parse_variable(self, has_name=True):

        modifiers = []

        while True:

            t = self._curr()
            if t.text in Tokenizer.BUILDIN_MODIFIERS:
                modifiers.append(t.text)
            else:
                break

        t = self._next()
        if t.text not in Tokenizer.BUILDIN_PRIMITIVES and t.type != TokenType.Identifier:
            return None

        var = EpiVariable(None, t.type)

        while True:

            t = self._curr()
            if t.type == TokenType.Asterisk:

                var.view_type = EpiVariable.ViewType.Pointer
                self._next()

            else:
                break

        t = self._curr()
        if t.type == TokenType.Ampersand:

                var.view_type = EpiVariable.ViewType.Reference
                self._next()

        if not has_name:
            return var

        t = self._next()
        if t.type != TokenType.Identifier:
            return None

        var.name = t.text

        return var

    def _parse_property(self):

        var = self._parse_variable(has_name=True)
        if not var:
            return None

        if var.view_type == EpiVariable.ViewType.Reference:

            self.syntax_errors.append(SyntaxError(self._curr(), SyntaxErrorCode.UnsupportedProperty, "Property coudn't be a reference"))
            return None

        prty = EpiProperty(var)

        # NOTE: if property is virtual an assignment is invalid
        t = self._next()
        if t.type == TokenType.Assing:

            if var.type == TokenType.BoolType:
                prty.value = self._parse_literal_boolean()
            elif var.type in [TokenType.ByteType, TokenType.IntType, TokenType.UIntType, TokenType.SizeTType, TokenType.HashTType]:
                prty.value = self._parse_literal_integer()
            elif var.type == TokenType.FloatingType:
                prty.value = self._parse_literal_floating()
            elif var.type == TokenType.CharType:
                prty.value = self._parse_literal_char()
            elif var.type == TokenType.StringType:
                prty.value = self._parse_literal_string()
            elif var.view_type == EpiVariable.ViewType.Pointer:

                self.syntax_errors.append(SyntaxError(t, SyntaxErrorCode.IncorrectValueLiteral, 'Pointers are unassingable and are set with \'null\' by default'))
                return None

            elif var.type == TokenType.Identifier:

                self.syntax_errors.append(SyntaxError(t, SyntaxErrorCode.IncorrectValueLiteral, 'Custom types are unassingable'))
                return None

            else:
                assert False, "Unhandled branch"

            if not prty.value:

                self.syntax_errors.append(SyntaxError(t, SyntaxErrorCode.IncorrectValueLiteral))
                return None

            t = self._next()

        if t.type != TokenType.Semicolon:

            self._push_error_unexpected_token(t, 'Expected \';\'')
            return None

        return prty

    def _parse_literal_string(self):

        lit_t = self._next()
        if lit_t.type != TokenType.StringLiteral:
            return None

        return lit_t.text

    def _parse_literal_char(self):

        lit_t = self._next()
        if lit_t.type != TokenType.CharLiteral:
            return None

        return lit_t.text

    def _parse_literal_integer(self):

        t = self._next()
        if t.type != TokenType.IntegerLiteral:
            return None

        return t.text

    def _parse_literal_floating(self):

        t = self._next()
        if t.type != TokenType.FloatingLiteral:
            return None

        return t.text

    def _parse_literal_boolean(self):

        t = self._next()
        return t.text if t.type in [TokenType.TrueLiteral, TokenType.FalseLiteral] else None

    def _is_next_variable(self):

        t = self._curr()
        return  t.type == TokenType.Identifier or\
                t.text in Tokenizer.BUILDIN_PRIMITIVES or\
                t.text in Tokenizer.BUILDIN_MODIFIERS

    def _push_error_unexpected_token(self, t, tip = ''):

        if Tokenizer.is_keyword(t.type):
            self.syntax_errors.append(SyntaxError(t, SyntaxErrorCode.UnexpectedKeywordUsage, tip))
        else:
            self.syntax_errors.append(SyntaxError(t, SyntaxErrorCode.UnexpectedToken, tip))
