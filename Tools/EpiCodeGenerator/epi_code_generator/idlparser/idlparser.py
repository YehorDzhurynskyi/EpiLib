from enum import Enum, auto

from epi_code_generator.tokenizer import Tokenizer
from epi_code_generator.tokenizer import Token
from epi_code_generator.tokenizer import TokenType

from epi_code_generator.symbol import EpiVariable
from epi_code_generator.symbol import EpiClass


class IDLSyntaxErrorCode(Enum):

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
    IDLSyntaxErrorCode.NoMatchingClosingBrace: 'No matching closing brace for',
    IDLSyntaxErrorCode.NoMatchingOpeningBrace: 'No matching opening brace for',
    IDLSyntaxErrorCode.NoMatchingClosingBracket: 'No matching closing bracket for',
    IDLSyntaxErrorCode.NestedBracket: 'Nested brackets \'[]\', \'()\' are forbidden',
    IDLSyntaxErrorCode.UnexpectedToken: 'Unexpected token',
    IDLSyntaxErrorCode.UnexpectedKeywordUsage: 'Unexpected keyword usage',
    IDLSyntaxErrorCode.UnexpectedEOF: 'Unexpected end of file',
    IDLSyntaxErrorCode.IncorrectValueLiteral: 'Incorrect value literal',
    IDLSyntaxErrorCode.UnsupportedProperty: 'Specified property declaration is unsupported',
    IDLSyntaxErrorCode.MatchingTokenOnSameLine: 'Matching token should be located on same line'
}


class IDLSyntaxError:

    def __init__(self, token, err_code, tip = ''):

        self.token = token
        self.err_code = err_code
        self.err_message = SYNTAX_ERROR_MSGS[err_code]
        self.tip = tip

    def __str__(self):

        s = f'Syntax error {str(self.token)}: {self.err_message}'
        if len(self.tip) != 0:
            s = f'{s} ({self.tip})'

        return s

class IDLParser:

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

            self.syntax_errors.append(IDLSyntaxError(self.tokens[-1], IDLSyntaxErrorCode.UnexpectedEOF))
            return self.syntax_errors

        registry = {}
        try:

            while True:

                t = self._curr()
                if t.type == TokenType.EOF:
                    break

                # attrs = self._parse_attr_list() if t.type == TokenType.OpenSqBracket else []

                t = self._curr()

                if t.text not in Tokenizer.BUILTIN_USER_TYPES:

                    self._error_push_unexpected_token(t, f'Expected an usertype: {",".join(Tokenizer.BUILTIN_USER_TYPES.keys())}')
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

        clss = EpiClass(t)

        t = self._curr()
        if t.type == TokenType.Colon:

            t = self._next(2)
            if t.type != TokenType.Identifier:

                self._error_push_unexpected_token(t, 'Expected an \'<identifier>\'')
                return None

            clss.parent = t.text

        def unpack_scope(s):

            for e in s:

                if isinstance(e, EpiVariable):
                    clss.properties.append(e)
                elif isinstance(e, list):
                    unpack_scope(e)

        scope = self._parse_scope()
        unpack_scope(scope)

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

            if self._curr().type == TokenType.CloseBrace:
                break
            elif self._curr().type == TokenType.OpenBrace:
                scope.append(self._parse_scope())
            else:
                scope.append(self._parse_variable())

        t = self._next()
        if t.type != TokenType.CloseBrace:

            self.syntax_errors.append(IDLSyntaxError(t, IDLSyntaxErrorCode.NoMatchingClosingBrace, 'Expected \'}\''))
            return None

        return scope

    """
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
    """

    def _parse_variable(self):

        if not self._is_next_type():

            self._error_push_unexpected_token(self._curr())
            return None

        tokentype = self._next()
        form = EpiVariable.Form.Plain

        if self._curr().type == TokenType.OpenAngleBracket:

            self._next()
            form = EpiVariable.Form.Array
            if not self._is_next_type():

                self._error_push_unexpected_token(self._curr(), 'Expected a <typename>')
                return None

            nestedtokentype = self._next()

            t = self._next()
            if t.type != TokenType.CloseAngleBracket:

                self.syntax_errors.append(IDLSyntaxError(t, IDLSyntaxErrorCode.NoMatchingClosingBracket, 'Expected \'>\''))
                return None

        while True:

            t = self._curr()
            if t.type == TokenType.Asterisk:

                form = EpiVariable.Form.Pointer
                tokentype.text += '*'
                self._next()

            else:
                break

        t = self._curr()
        if t.type == TokenType.Ampersand:

                assert False
                # form = EpiVariable.Form.Reference
                # self._next()

        t = self._next()
        if t.type != TokenType.Identifier:

            self._error_push_unexpected_token(t, 'Expected an <identifier>')
            return None

        var = EpiVariable(t, tokentype, form)

        if var.form == EpiVariable.Form.Array:
            var.nestedtokentype = nestedtokentype

        # NOTE: if property is virtual an assignment is invalid
        t = self._next()
        if t.type == TokenType.Assing:

            t = self._curr()
            if var.tokentype.type == TokenType.BoolType:
                var.value = self._parse_literal_boolean()
            elif var.tokentype.type in [
                TokenType.ByteType,
                TokenType.IntType,
                TokenType.UIntType,
                TokenType.SizeTType,
                TokenType.HashTType
            ]:
                var.value = self._parse_literal_integer()
            elif var.tokentype.type == TokenType.FloatingType:
                var.value = self._parse_literal_floating()
            elif var.tokentype.type == TokenType.CharType:
                var.value = self._parse_literal_char()
            elif var.tokentype.type == TokenType.StringType:
                var.value = self._parse_literal_string()
            elif var.form == EpiVariable.Form.Pointer:

                self.syntax_errors.append(IDLSyntaxError(t, IDLSyntaxErrorCode.IncorrectValueLiteral, 'Pointers are unassingable and are set with \'null\' by default'))
                return None

            elif var.tokentype.type == TokenType.Identifier:

                self.syntax_errors.append(IDLSyntaxError(t, IDLSyntaxErrorCode.IncorrectValueLiteral, 'Custom types are unassingable'))
                return None

            else:
                assert False, 'Unhandled branch'

            if var.value is None:

                self.syntax_errors.append(IDLSyntaxError(t, IDLSyntaxErrorCode.IncorrectValueLiteral))
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

    def _is_next_type(self):

        t = self._curr()
        return t.text in (
            Tokenizer.BUILTIN_PRIMITIVE_TYPES.keys() |
            Tokenizer.BUILTIN_COMPOUND_TYPES.keys()
        ) or t.type == TokenType.Identifier

    def _is_next_variable(self):

        # NOTE: could be a method
        t = self._curr()
        return  t.type == TokenType.Identifier or\
                t.text in Tokenizer.BUILTIN_PRIMITIVE_TYPES or\
                t.text in Tokenizer.BUILTIN_COMPOUND_TYPES or\
                t.text in Tokenizer.BUILTIN_MODIFIERS

    def _error_push_unexpected_token(self, t, tip = ''):

        if Tokenizer.is_keyword(t.type):
            self.syntax_errors.append(IDLSyntaxError(t, IDLSyntaxErrorCode.UnexpectedKeywordUsage, tip))
        else:
            self.syntax_errors.append(IDLSyntaxError(t, IDLSyntaxErrorCode.UnexpectedToken, tip))
