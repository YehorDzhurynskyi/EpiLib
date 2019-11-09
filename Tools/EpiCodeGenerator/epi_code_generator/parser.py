from enum import Enum, auto

from .tokenizer import Tokenizer
from .tokenizer import Token
from .tokenizer import TokenType

from .morpheme import Attribute
from .morpheme import Property
from .morpheme import Class
from .morpheme import Struct
from .morpheme import Enum
from .morpheme import Interface


class SyntaxErrorCode(Enum):

    NoMatchingClosingBrace = auto()
    NoMatchingOpeningBrace = auto()
    NoMatchingClosingBracket = auto()
    NestedBracket = auto()
    UnexpectedToken = auto()
    UnexpectedKeywordUsage = auto()
    UnexpectedEOF = auto()
    IncorrectValueLiteral = auto()
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
    SyntaxErrorCode.MatchingTokenOnSameLine: "Matching token should be located on same line"
}


class SyntaxError:

    def __init__(self, token, err_code, tip = ''):

        self.token = token
        self.err_code = err_code
        self.err_message = SYNTAX_ERROR_MSGS[err_code]
        self.tip = tip

    def __str__(self):
        return f'[ERROR]{str(self.token)} message: "{self.err_message}"' + f' ({self.tip})' if len(self.tip) != 0 else ''


class ParamListParser:

    def __init__(self, ctx, param_list):

        self.ctx = ctx
        self.param_list = param_list
        self.__at = 0

    def parse(self):

        while True:

            ch = self._next()
            if ch == '@':

                begin = self.__at
                while self._curr().isalpha():
                    self._next()

                text = self.param_list[begin, self.__at]
                # TODO: finish

            elif ch == '(':
                pass
            elif ch == '{':
                pass

    def _curr(self):
        return self.param_list[self.__at]

    def _next(self):

        self.__at += next - 1
        curr = self._curr()
        self.__at += 1

        return curr


class Parser:

    def __init__(self, tokens):

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

    def parse(self, registry):

        if self.tokens[-1].type != TokenType.EOF:

            self.syntax_errors.append(SyntaxError(self.tokens[-1], SyntaxErrorCode.UnexpectedEOF))
            return self.syntax_errors

        try:

            while True:

                t = self._curr()
                if t.type == TokenType.EOF:
                    break

                attrs = self._parse_attr_list() if t.type == TokenType.OpenSqBracket else []

                user_type = None
                registry_collection = None

                t = self._curr()
                if t.type == TokenType.EnumType:
                    user_type = self._parse_enum()
                    registry_collection = registry.enums
                elif t.type == TokenType.StructType:
                    user_type = self._parse_struct()
                    registry_collection = registry.structs
                elif t.type == TokenType.ClassType:
                    user_type = self._parse_class()
                    registry_collection = registry.classes
                elif t.type == TokenType.InterfaceType:
                    user_type = self._parse_interface()
                    registry_collection = registry.interfaces
                else:
                    assert False

                if user_type:
                    user_type.attrs = attrs
                    registry_collection.append(user_type)

        except IndexError:
            assert False

        return self.syntax_errors

    def _parse_enum(self):
        return Enum('')

    def _parse_struct(self):
        return Struct('')

    def _parse_interface(self):

        t = self._next()
        if t.type != TokenType.InterfaceType:
            return None

        t = self._next()
        if t.type != TokenType.Identifier:
            return None

        interface = Interface(t.text)

        t = self._curr()
        if t.type == TokenType.Colon:

            t = self._next(2)
            if t.type != TokenType.Identifier:
                return None

            interface.parent = t.text

        t = self._next()
        if t.type != TokenType.OpenBracket:
            return None

        while True:

            t = self._curr()
            t

        t = self._next()
        if t.type != TokenType.CloseBracket:
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

        clss = Class(t.text)

        t = self._curr()
        if t.type == TokenType.Colon:

            t = self._next()
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

            if t.type == TokenType.Identifier or t.type in Tokenizer.BUILDIN_TYPES:

                prty = self._parse_property()
                if prty:
                    prty.attrs = attrs_inherent + attrs
                    clss.prts.append(prty)

            elif t.type == TokenType.OpenBrace:

                self._parse_scope(clss, attrs_inherent + attrs)

            else:
                break

        t = self._curr()
        if t.type != TokenType.CloseBrace:

            self.syntax_errors.append(SyntaxError(t, SyntaxErrorCode.NoMatchingClosingBrace, 'Expected \'}\''))
            return

    def _parse_attr_list(self):

        attrs = []
        while True:

            t = self._curr()
            if t.type == TokenType.OpenSqBracket:

                while t.type != TokenType.CloseSqBracket:

                    t = self._curr()
                    if t.type not in Tokenizer.BUILDIN_PRTY_ATTRS.keys() | Tokenizer.BUILDIN_CLSS_ATTRS.keys():

                        self._push_error_unexpected_token(t, 'Expected an \'attribute\'')
                        return None

                    attr = self._parse_attr()
                    if attr:
                        attrs.append(attr)

            else:
                break

        return attrs


    def _parse_attr(self):

        a_t = self._next()

        param_list = Attribute.PARAM_LISTS[a_t.type]
        assert param_list, "Property is unhandled in Attribute.PARAM_LISTS"

        attr = Attribute(a_t.type)

        if len(param_list) == 0:
            return attr

        ob_t = self._next()
        if ob_t.type != TokenType.OpenBracket:
            return None

        param_list_parser = ParamListParser(self, param_list)
        attr.params = param_list_parser.parse()
        if not attr.params:
            return None

        cb_t = self._next()
        if cb_t.type != TokenType.CloseBracket:
            return None

        return attr

    def _parse_property(self):

        t = self._next()
        if t.type not in Tokenizer.BUILDIN_TYPES and t.type != TokenType.Identifier:

            self._push_error_unexpected_token(t, 'Expected a \'type\'')
            return None

        is_pointer = False
        while True:

            t = self._curr()
            if t.type == TokenType.Asterisk:

                self._next()
                is_pointer = True

            else:
                break

        t = self._next()
        if t.type != TokenType.Identifier:

            self._push_error_unexpected_token(t, 'Expected an \'identifier\'')
            return None

        prty = Property(t.type, t.text, is_pointer)

        # NOTE: if property is virtual an assignment is invalid
        t = self._curr()
        if t.type == TokenType.Assing:

            self._next()
            t = self._curr()

            if prty.type == TokenType.BoolType:
                prty.value = self._parse_literal_boolean()
            elif prty.type in [TokenType.IntType, TokenType.ByteType, TokenType.FloatingType]:
                prty.value = self._parse_literal_signed()
            elif prty.type == TokenType.FloatingType:
                prty.value = self._parse_literal_floating()
            elif prty.type in [TokenType.SizeTType, TokenType.HashTType, TokenType.UIntType]:
                prty.value = self._parse_literal_unsigned()
            elif prty.type == TokenType.CharType:
                prty.value = self._parse_literal_char()
            elif prty.type == TokenType.StringType:
                prty.value = self._parse_literal_string()
            elif prty.is_pointer:

                self.syntax_errors.append(SyntaxError(t, SyntaxErrorCode.IncorrectValueLiteral, 'Pointers are unassingable and are set with \'null\' by default'))
                return None

            elif prty.type == TokenType.Identifier:

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

        elif t.type == TokenType.Semicolon:
            pass
        else:

            self._push_error_unexpected_token(t, 'Expected \'=\' or \';\'')
            return None

        return prty

    def _parse_literal_string(self):

        oq_t = self._next()
        if oq_t.type != TokenType.OpenQuote:
            return None

        lit_t = self._next()
        if lit_t.type != TokenType.TextLiteral:
            return None

        cq_t = self._next()
        if cq_t.type != TokenType.CloseQuote:
            return None

        if cq_t.line != oq_t.line:

            self.syntax_errors.append(SyntaxError(oq_t, SyntaxErrorCode.MatchingTokenOnSameLine, 'Closing token \'"\' should be on same line'))
            return None

        return lit_t.text

    def _parse_literal_char(self):

        # TODO: add unicode support (like: '\u8080')
        oq_t = self._next()
        if oq_t.type != TokenType.OpenSingleQuote:
            return None

        lit_t = self._next()
        if lit_t.type != TokenType.TextLiteral or len(lit_t.text) != 1:
            return None

        cq_t = self._next()
        if cq_t.type != TokenType.CloseSingleQuote:
            return None

        if cq_t.line != oq_t.line:

            self.syntax_errors.append(SyntaxError(oq_t, SyntaxErrorCode.MatchingTokenOnSameLine, 'Closing token \'\'\' should be on same line'))
            return None

        return lit_t.text

    def _parse_literal_unsigned(self):

        t = self._next()
        if t.type != TokenType.IntegerLiteral:
            return None

        return t.text

    def _parse_literal_floating(self):

        is_negative = False

        t = self._next()
        if t.type == TokenType.Minus:

            is_negative = True
            t = self._next()

        if t.type != TokenType.FloatingLiteral:
            return None

        return f"{'-' if is_negative else ''}{t.text}"

    def _parse_literal_signed(self):

        is_negative = False

        t = self._next()
        if t.type == TokenType.Minus:

            is_negative = True
            t = self._next()

        if t.type != TokenType.IntegerLiteral:
            return None

        return f"{'-' if is_negative else ''}{t.text}"

    def _parse_literal_boolean(self):

        t = self._next()
        return t.text if t.type in [TokenType.TrueLiteral, TokenType.FalseLiteral] else None

    def _push_error_unexpected_token(self, t, tip = ''):

        if Tokenizer.is_keyword(t.type):
            self.syntax_errors.append(SyntaxError(t, SyntaxErrorCode.UnexpectedKeywordUsage, tip))
        else:
            self.syntax_errors.append(SyntaxError(t, SyntaxErrorCode.UnexpectedToken, tip))
