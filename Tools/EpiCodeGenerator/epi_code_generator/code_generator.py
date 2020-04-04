import os
import zlib
from enum import Enum, auto

from .tokenizer import Token
from .tokenizer import TokenType
from .tokenizer import Tokenizer
from .symbol import EpiSymbol
from .symbol import EpiClass
from .symbol import EpiVariable


class CodeGenerationErrorCode(Enum):

    CorruptedFile = auto()


CODE_GENERATION_ERROR_MSGS = {
    CodeGenerationErrorCode.CorruptedFile: 'File corrupted'
}


class CodeGenerationError(Exception):

    def __init__(self, basename, err_code, tip = ''):

        self.basename = basename
        self.err_code = err_code
        self.err_message = CODE_GENERATION_ERROR_MSGS[err_code]
        self.tip = tip

    def __str__(self):

        s = f'Code Generation error {self.basename}: {self.err_message}'
        if len(self.tip) != 0:
            s = f'{s} ({self.tip})'

        return s


class CodeGenerator:

    def __init__(self, output_dir: str):

        self.output_dir = output_dir
        self.filecache = {}

    def flush(self):

        for path, content in self.filecache.items():

            with open(path, 'w') as f:
                f.write(content)

    def _code_generate_inject(self, inj: str, basename: str, ext: str):

        path = f'{os.path.join(self.output_dir, basename)}.{ext}'
        if path not in self.filecache:

            with open(path, 'r') as f:
                content = f.read()

        else:
            content = self.filecache[path]

        end = content.find('EPI_NAMESPACE_END()')
        if end == -1:

            tip = f'Can\'t find `EPI_NAMESPACE_END()` mark'
            raise CodeGenerationError(basename, CodeGenerationErrorCode.CorruptedFile, tip)

        self.filecache[path] = content[:end] + inj + content[end:]

    def code_generate(self, symbol: EpiSymbol, basename: str):

        class Builder:

            def __init__(self):

                self.indent = 0
                self.lines = []
                self.genregion_mark = False
                self.namespace_mark = False

            def line(self, line):
                self.lines.append(f'{"    " * self.indent}{line}')

            def line_empty(self, n: int = 1):
                for _ in range(n): self.lines.append('')

            def tab(self, t: int = 1):
                self.indent = max(0, self.indent + t)

            def mark_namespace_begin(self):

                assert not self.namespace_mark
                self.lines.append('EPI_NAMESPACE_BEGIN()')
                self.namespace_mark = True

            def mark_namespace_end(self):

                assert self.namespace_mark
                self.lines.append('EPI_NAMESPACE_END()')
                self.namespace_mark = False

            def mark_gen_region(self):

                assert not self.genregion_mark
                self.lines.append('EPI_GENREGION_BEGIN()')
                self.genregion_mark = True

            def mark_gen_endregion(self):

                assert self.genregion_mark
                self.lines.append('EPI_GENREGION_END()')
                self.genregion_mark = False

            def build(self):

                assert not self.genregion_mark
                assert not self.namespace_mark

                return '\n'.join(self.lines)

        def emit_sekeleton_file(basename: str, ext: str) -> str:

            builder = Builder()

            if ext in ['cxx', 'cpp', 'h']:

                builder.mark_gen_region()

                if ext == 'cxx':
                    builder.line(f'#include "{basename}.h"')
                elif ext == 'cpp':
                    builder.line(f'#include "{basename}.h"')
                    builder.line(f'#include "{basename}.cxx"')
                elif ext == 'h':
                    builder.line(f'#include "{basename}.hxx"')

                builder.mark_gen_endregion()
                builder.line_empty()

            builder.mark_namespace_begin()
            builder.line_empty()
            builder.mark_namespace_end()
            builder.line_empty()

            return builder.build()

        def emit_class_serialization(clss: EpiClass, builder: Builder = Builder()) -> Builder:

            builder.line(f'void {clss.name}::Serialization(json_t& json) const')
            builder.line('{')
            builder.tab()
            builder.line('super::Serialization(json);')
            builder.line_empty()

            for p in clss.properties:
                builder.line(f'epiSerialize({p.name}, json);')

            builder.tab(-1)
            builder.line('}')
            builder.line_empty()

            builder.line(f'void {clss.name}::Deserialization(const json_t& json)')
            builder.line('{')
            builder.tab()
            builder.line('super::Deserialization(json);')
            builder.line_empty()

            for p in clss.properties:
                builder.line(f'epiDeserialize({p.name}, json);')

            builder.tab(-1)
            builder.line('}')
            builder.line_empty()

            return builder

        def emit_class_declaration(clss: EpiClass, builder: Builder = Builder()) -> Builder:

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

            return builder

        if not os.path.exists(f'{os.path.join(self.output_dir, basename)}.cpp'):

            with open(f'{os.path.join(self.output_dir, basename)}.cpp', 'w') as f:
                f.write(emit_sekeleton_file(basename, 'cpp'))

        if not os.path.exists(f'{os.path.join(self.output_dir, basename)}.h'):

            with open(f'{os.path.join(self.output_dir, basename)}.h', 'w') as f:
                f.write(emit_sekeleton_file(basename, 'h'))

        with open(f'{os.path.join(self.output_dir, basename)}.hxx', 'w') as f:
            f.write(emit_sekeleton_file(basename, 'hxx'))

        with open(f'{os.path.join(self.output_dir, basename)}.cxx', 'w') as f:
            f.write(emit_sekeleton_file(basename, 'cxx'))

        assert isinstance(symbol, EpiClass)

        injection = f'{emit_class_serialization(symbol).build()}\n'
        self._code_generate_inject(injection, basename, 'cxx')
