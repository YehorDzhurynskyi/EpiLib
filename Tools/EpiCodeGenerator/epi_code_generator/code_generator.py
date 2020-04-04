import os
import zlib

from .tokenizer import Token
from .tokenizer import TokenType
from .tokenizer import Tokenizer
from .symbol import EpiSymbol
from .symbol import EpiClass
from .symbol import EpiVariable

def code_generate(symbol: EpiSymbol, prefixpath: str):

    class Builder:

        def __init__(self):

            self.indent = 0
            self.lines = []
            self.gen_region_mark = False

        def line(self, line):
            self.lines.append(f'{"    " * self.indent}{line}')

        def line_empty(self, n: int = 1):
            for _ in range(n): self.lines.append('')

        def tab(self, t: int = 1):
            self.indent = max(0, self.indent + t)

        def mark_gen_region(self):

            assert self.gen_region_mark == False
            self.lines.append('EPI_GEN_REGION()')
            self.gen_region_mark = True

        def mark_gen_endregion(self):

            assert self.gen_region_mark == True
            self.lines.append('EPI_GEN_ENDREGION()')
            self.gen_region_mark = False

        def build(self):
            return '\n'.join(self.lines)

    def emit_sekeleton_file_cpp(filepath: str) -> str:
        return ''

    def emit_sekeleton_file_h(filepath: str) -> str:
        return ''

    def emit_sekeleton_class(clss: EpiClass) -> str:

        builder = Builder()

        clss_parent = clss.parent if clss.parent is not None else 'Object'
        builder.line(f'class {clss.name} : public {clss_parent}')
        builder.line('{')
        builder.mark_gen_region()
        builder.line('public:')
        builder.tab()
        builder.line(f'using super = {clss_parent};')
        builder.line_empty()

        # pids
        builder.line(f'enum {clss.name}_PIDs')
        builder.line('{')
        builder.tab()

        for p in clss.properties:

            crc = hex(zlib.crc32(f'm_{p.name}'.encode()) & 0xffffffff)
            builder.line(f'PID_{p.name} = {crc},')

        builder.line(f'COUNT = {len(clss.properties)}')

        builder.tab(-1)
        builder.line('};')
        builder.line_empty()
        builder.tab(-1)
        builder.line('protected:')
        builder.tab()

        # getters/setters
        for p in clss.properties:

            ptype = p.tokentype.text
            if ptype not in Tokenizer.BUILTIN_PRIMITIVE_TYPES:
                ptype = f'const {ptype}&'

            builder.line(f'{ptype} Get{p.name}() const ' '{' f'return m_{p.name};' '}')
            builder.line(f'void Set{p.name}({ptype} value) ' '{' f'm_{p.name} = value;' '}')

        builder.line_empty()

        # prts
        for p in clss.properties:
            builder.line(f'{p.tokentype.text} m_{p.name}' '{' f'{p.value}' '};')

        builder.mark_gen_endregion()
        builder.tab(-1)
        builder.line('};')
        builder.line_empty()

        return builder.build()

    if not os.path.exists(f'{prefixpath}.cpp'):

        with open(f'{prefixpath}.cpp', 'w') as f:
            f.write(emit_sekeleton_file_cpp(prefixpath))

    if not os.path.exists(f'{prefixpath}.h'):

        with open(f'{prefixpath}.h', 'w') as f:
            f.write(emit_sekeleton_file_h(prefixpath))

    assert isinstance(symbol, EpiClass)

    if isinstance(symbol, EpiClass):
        print(emit_sekeleton_class(symbol))
