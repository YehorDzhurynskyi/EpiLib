from enum import Enum, auto

from .tokenizer import Tokenizer
from .tokenizer import Token
from .tokenizer import TokenType

from .symbol import EpiVariable
from .symbol import EpiClass


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
    SyntaxErrorCode.NoMatchingClosingBrace: 'No matching closing brace for',
    SyntaxErrorCode.NoMatchingOpeningBrace: 'No matching opening brace for',
    SyntaxErrorCode.NoMatchingClosingBracket: 'No matching closing bracket for',
    SyntaxErrorCode.NestedBracket: 'Nested brackets \'[]\', \'()\' are forbidden',
    SyntaxErrorCode.UnexpectedToken: 'Unexpected token',
    SyntaxErrorCode.UnexpectedKeywordUsage: 'Unexpected keyword usage',
    SyntaxErrorCode.UnexpectedEOF: 'Unexpected end of file',
    SyntaxErrorCode.IncorrectValueLiteral: 'Incorrect value literal',
    SyntaxErrorCode.UnsupportedProperty: 'Specified property declaration is unsupported',
    SyntaxErrorCode.MatchingTokenOnSameLine: 'Matching token should be located on same line'
}


class SyntaxError:

    def __init__(self, token, err_code, tip = ''):

        self.token = token
        self.err_code = err_code
        self.err_message = SYNTAX_ERROR_MSGS[err_code]
        self.tip = tip

    def __str__(self):
        return \
            f'Syntax error {str(self.token)} message: '{self.err_message}'' + \
            f' ({self.tip})' if len(self.tip) != 0 else ''


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

    def parse(self):

        if self.tokens[-1].type != TokenType.EOF:

            self.syntax_errors.append(SyntaxError(self.tokens[-1], SyntaxErrorCode.UnexpectedEOF))
            return self.syntax_errors

        registry = {}
        try:

            while True:

                t = self._curr()
                if t.type == TokenType.EOF:
                    break

                # attrs = self._parse_attr_list() if t.type == TokenType.OpenSqBracket else []

                t = self._curr()

                if t.text not in Tokenizer.BUILTIN_USERTYPES:

                    self._error_push_unexpected_token(t, f'Expected an usertype: {','.join(Tokenizer.BUILTIN_USERTYPES.keys())}')
                    break

                if not t.type == TokenType.ClassType:
                    assert False, 'Handle other usertypes'

                clss = self._parse_class()
                registry[clss.name] = clss

        except IndexError:
            assert False

        return registry, self.syntax_errors

    def _parse_class(self):

        t = self._next()
        if t.type != TokenType.ClassType:

            self._error_push_unexpected_token(t, 'Expected a \'class\' type')
            return None

        t = self._next()
        if t.type != TokenType.Identifier:

            self._error_push_unexpected_token(t, 'Expected an \'<identifier>\'')
            return None

        clss = EpiClass(t.text)

        t = self._curr()
        if t.type == TokenType.Colon:

            t = self._next(2)
            if t.type != TokenType.Identifier:

                self._error_push_unexpected_token(t, 'Expected an \'<identifier>\'')
                return None

            clss.parent = t.text

        scope = self._parse_scope()
        # TODO: process scope

        t = self._next()
        if t.type != TokenType.Semicolon:

            self._error_push_unexpected_token(t, 'Expected \';\'')
            return None

        return clss

    def _parse_scope(self):

        t = self._next()
        if t.type != TokenType.OpenBrace:

            self._error_push_unexpected_token(t, 'Expected \'{\'')
            return None

        scope = []
        while True:

            # t = self._curr()
            # attrs = self._parse_attr_list() if t.type == TokenType.OpenSqBracket else []

            # TODO: check if property isn't reference

            if self._curr().type == TokenType.OpenBrace:
                scope.append(self._parse_scope())
            else
                scope.append(self._parse_property())

        t = self._next()
        if t.type != TokenType.CloseBrace:

            self.syntax_errors.append(SyntaxError(t, SyntaxErrorCode.NoMatchingClosingBrace, 'Expected \'}\''))
            return None

        return scope

'''
    def _parse_attr_list(self):

        attrs = []
        while True:

            t = self._curr()
            if t.type != TokenType.OpenSqBracket:
                break

            self._next()
            while self._curr().text in Tokenizer.BUILTIN_PRTY_ATTRS.keys() | Tokenizer.BUILTIN_CLSS_ATTRS.keys():

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
'''

    def _parse_variable(self):

        typetoken = self._next()
        if typetoken.text not in Tokenizer.BUILTIN_PRIMITIVES and typetoken.type != TokenType.Identifier:
            return None

        form = EpiVariable.Form.Plain
        while True:

            t = self._curr()
            if t.type == TokenType.Asterisk:

                form = EpiVariable.Form.Pointer
                self._next()

            else:
                break

        t = self._curr()
        if t.type == TokenType.Ampersand:

                form = EpiVariable.Form.Reference
                self._next()

        t = self._next()
        if t.type != TokenType.Identifier:
            return None

        var = EpiVariable(t, typetoken.type, form)

        # NOTE: if property is virtual an assignment is invalid
        t = self._next()
        if t.type == TokenType.Assing:

            if var.type == TokenType.BoolType:
                var.value = self._parse_literal_boolean()
            elif var.type in
            [
                TokenType.ByteType,
                TokenType.IntType,
                TokenType.UIntType,
                TokenType.SizeTType,
                TokenType.HashTType
            ]:
                var.value = self._parse_literal_integer()
            elif var.type == TokenType.FloatingType:
                var.value = self._parse_literal_floating()
            elif var.type == TokenType.CharType:
                var.value = self._parse_literal_char()
            elif var.type == TokenType.StringType:
                var.value = self._parse_literal_string()
            elif var.view_type == EpiVariable.Form.Pointer:

                self.syntax_errors.append(SyntaxError(t, SyntaxErrorCode.IncorrectValueLiteral, 'Pointers are unassingable and are set with \'null\' by default'))
                return None

            elif var.type == TokenType.Identifier:

                self.syntax_errors.append(SyntaxError(t, SyntaxErrorCode.IncorrectValueLiteral, 'Custom types are unassingable'))
                return None

            else:
                assert False, 'Unhandled branch'

            if var.value is None:

                self.syntax_errors.append(SyntaxError(t, SyntaxErrorCode.IncorrectValueLiteral))
                return None

            t = self._next()

        if t.type != TokenType.Semicolon:

            self._error_push_unexpected_token(t, 'Expected \';\'')
            return None

        return var

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

        # NOTE: could be a method
        t = self._curr()
        return  t.type == TokenType.Identifier or\
                t.text in Tokenizer.BUILTIN_PRIMITIVES or\
                t.text in Tokenizer.BUILTIN_MODIFIERS

    def _error_push_unexpected_token(self, t, tip = ''):

        if Tokenizer.is_keyword(t.type):
            self.syntax_errors.append(SyntaxError(t, SyntaxErrorCode.UnexpectedKeywordUsage, tip))
        else:
            self.syntax_errors.append(SyntaxError(t, SyntaxErrorCode.UnexpectedToken, tip))
