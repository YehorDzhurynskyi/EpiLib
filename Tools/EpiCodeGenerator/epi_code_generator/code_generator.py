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
    CorruptedAnchor = auto()


CODE_GENERATION_ERROR_MSGS = {
    CodeGenerationErrorCode.CorruptedFile: 'File corrupted',
    CodeGenerationErrorCode.CorruptedAnchor: 'Anchor corrupted'
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

    def __init__(self, output_dir: str, output_dir_cxx_hxx: str):

        self.output_dir = output_dir
        self.output_dir_cxx_hxx = output_dir_cxx_hxx
        self.filecache = {}

    def flush(self):

        for path, content in self.filecache.items():

            with open(path, 'w') as f:
                f.write(content)

    def _lookup(self, needle: str, basename: str, ext: str) -> int:

        assert ext == 'h' or ext == 'cpp'

        path = f'{os.path.join(self.output_dir, basename)}.{ext}'
        if path not in self.filecache:

            with open(path, 'r') as f:

                content = f.read()
                self.filecache[path] = content

        content = self.filecache[path]

        return content.find(needle)

    def _code_generate_inject(self,
                              inj: str,
                              basename: str,
                              ext: str,
                              before: str = None,
                              after: str = None):

        outdir = self.output_dir if ext == 'h' or ext == 'cpp' else self.output_dir_cxx_hxx

        path = f'{os.path.join(outdir, basename)}.{ext}'
        if path not in self.filecache:

            with open(path, 'r') as f:
                content = f.read()

        else:
            content = self.filecache[path]

        if before is None and after is None:
            lbound = len(content)
            rbound = len(content)
        else:
            if before is not None and after is not None:
                lbound = content.find(after) + len(after)
                rbound = content.find(before)
            elif before is not None:
                rbound = content.find(before)
                lbound = rbound
            elif after is not None:
                lbound = content.find(after) + len(after)
                rbound = lbound

        if rbound == -1 or lbound == -1:

            tip = f'Can\'t find `{before if before is not None else after}` anchor'
            raise CodeGenerationError(f'{basename}.{ext}', CodeGenerationErrorCode.CorruptedFile, tip)

        self.filecache[path] = content[:lbound] + inj + content[rbound:]

    def code_generate(self, symbol: EpiSymbol, basename: str):

        class Builder:

            def __init__(self):

                self.indent = 0
                self.lines = []
                self.genregion_anchor = False
                self.namespace_anchor = False

            def line(self, line):
                self.lines.append(f'{"    " * self.indent}{line}')

            def line_empty(self, n: int = 1):
                for _ in range(n): self.lines.append('')

            def tab(self, t: int = 1):
                self.indent = max(0, self.indent + t)

            def anchor_namespace_begin(self):

                assert not self.namespace_anchor
                self.lines.append('EPI_NAMESPACE_BEGIN()')
                self.namespace_anchor = True

            def anchor_namespace_end(self):

                assert self.namespace_anchor
                self.lines.append('EPI_NAMESPACE_END()')
                self.namespace_anchor = False

            def anchor_gen_region(self, caption):

                assert not self.genregion_anchor

                self.lines.append(f'EPI_GENREGION_BEGIN({caption})')
                self.genregion_anchor = True

            def anchor_gen_endregion(self, caption):

                assert self.genregion_anchor
                self.lines.append(f'EPI_GENREGION_END({caption})')
                self.genregion_anchor = False

            def build(self):

                assert not self.genregion_anchor
                assert not self.namespace_anchor

                return '\n'.join(self.lines)

        def emit_sekeleton_file(basename: str, ext: str) -> str:

            builder = Builder()

            if ext == 'h':

                builder.line('#pragma once')
                builder.line_empty()

            if ext in ['cxx', 'hxx']:
                header = \
'''
/*                                                      */
/*  ______       _                                      */
/* |  ____|     (_)                                     */
/* | |__   _ __  _                                      */
/* |  __| | '_ \| |   THIS FILE IS AUTO-GENERATED       */
/* | |____| |_) | |   manual changes won't be saved     */
/* |______| .__/|_|                                     */
/*        | |                                           */
/*        |_|                                           */
/*                                                      */
'''

                builder.line(header.strip())
                builder.line_empty()

            if ext in ['cpp', 'h']:

                builder.anchor_gen_region('include')

                if ext == 'cpp':
                    builder.line(f'#include "{basename}.h"')
                    builder.line(f'#include "{basename}.cxx"')
                elif ext == 'h':
                    builder.line(f'#include "{basename}.hxx"')

                builder.anchor_gen_endregion('include')
                builder.line_empty()

            if ext in ['cxx', 'cpp', 'h']:

                builder.anchor_namespace_begin()
                builder.line_empty()
                builder.anchor_namespace_end()
                builder.line_empty()

            return builder.build()

        def emit_class_serialization(clss: EpiClass, builder: Builder = Builder()) -> Builder:

            builder.line(f'void {clss.name}::Serialization(json_t& json)')
            builder.line('{')
            builder.tab()
            builder.line('super::Serialization(json);')
            builder.line_empty()

            for p in clss.properties:

                if not any(a.tokentype == TokenType.Transient for a in p.attrs):
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

                if not any(a.tokentype == TokenType.Transient for a in p.attrs):
                    builder.line(f'epiDeserialize({p.name}, json);')

            builder.tab(-1)
            builder.line('}')
            builder.line_empty()

            return builder

        def emit_class_meta(clss: EpiClass, builder: Builder = Builder()) -> Builder:

            # TODO: make it constexpr
            builder.line(f'MetaClass {clss.name}::EmitMetaClass()')
            builder.line('{')
            builder.tab()
            builder.line('MetaClassData data;')
            builder.line_empty()

            for p in clss.properties:

                hash_typenested = '0'
                if p.form == EpiVariable.Form.Array:
                    hash_typenested = f'epiHashCompileTime({p.nestedtokentype.text})'

                # TODO: handle properly
                if any(a.tokentype == TokenType.Virtual for a in p.attrs):
                    continue

                # TODO: remove rstrip
                hash_type = f'epiHashCompileTime({p.tokentype.text.rstrip("*")})'

                builder.line('{')
                builder.tab()
                builder.line('MetaProperty m = epiMetaProperty(')
                builder.tab()
                builder.line(f'/* Name */ "{p.name}",')
                builder.line(f'/* PtrRead */ (void*)offsetof({clss.name}, m_{p.name}),')
                builder.line(f'/* PtrWrite */ (void*)offsetof({clss.name}, m_{p.name}),')
                builder.line('/* Flags */ {},')
                builder.line(f'/* typeID */ {hash_type},')
                builder.line(f'/* nestedTypeID */ {hash_typenested}')
                builder.tab(-1)
                builder.line(');')
                builder.line(f'data.AddProperty(epiHashCompileTime({p.name}), std::move(m));')
                builder.tab(-1)
                builder.line('}')

            builder.line_empty()

            clss_parent = clss.parent if clss.parent is not None else 'Object'
            hash_parent = f'epiHashCompileTime({clss_parent})'
            hash_clss = f'epiHashCompileTime({clss.name})'
            builder.line(f'return MetaClass(std::move(data), {hash_clss}, {hash_parent}, sizeof({clss.name}), "{clss.name}");')

            builder.tab(-1)
            builder.line('}')
            builder.line_empty()

            return builder

        def emit_class_declaration_hidden(clss: EpiClass, builder: Builder = Builder()) -> Builder:

            clss_parent = clss.parent if clss.parent is not None else 'Object'
            builder.line(f'#define EPI_GENHIDDEN_{clss.name}() \\')
            builder.line(' \\')

            content = \
f'''

using super = {clss_parent};

static MetaClass EmitMetaClass();

const MetaClass& GetMetaClass() const override
{{
    return ClassRegistry_GetMetaClass<{clss.name}>();
}}

epiBool Is(MetaTypeID rhs) const override
{{
    return rhs == {clss.name}::TypeID || super::Is(rhs);
}}

void Serialization(json_t& json) override;
void Deserialization(const json_t& json) override;

'''
            builder.line(' \\\n'.join(content.strip().split('\n')) + ' \\')
            builder.line('\\')

            # getters/setters
            for p in clss.properties:

                ptype = p.tokentype.text

                if p.form == EpiVariable.Form.Array:
                    ptype = f'{ptype}<{p.nestedtokentype.text}>'

                body_prologue_set = ''
                body_epilogue_set = f'm_{p.name} = value;'
                body_prologue_get = ''
                body_epilogue_get = f'return m_{p.name};'

                for a in p.attrs:

                    if a.tokentype == TokenType.ExpectMin:

                        v = a.params[0].text
                        body_prologue_set = f'{body_prologue_set}epiExpect(value >= {v});'

                    if a.tokentype == TokenType.ExpectMax:

                        v = a.params[0].text
                        body_prologue_set = f'{body_prologue_set}epiExpect(value <= {v});'

                    if a.tokentype == TokenType.ForceMin:

                        v = a.params[0].text
                        body_prologue_set = f'{body_prologue_set}value = std::max(value, {v});'

                    if a.tokentype == TokenType.ForceMax:

                        v = a.params[0].text
                        body_prologue_set = f'{body_prologue_set}value = std::min(value, {v});'

                    if a.tokentype == TokenType.Virtual:

                        body_epilogue_get = f'return Get{p.name}_Callback();'
                        body_epilogue_set = f'Set{p.name}_Callback(value);'

                body_get = f'{body_prologue_get}{body_epilogue_get}'
                body_set = f'{body_prologue_set}{body_epilogue_set}'
                if ptype not in Tokenizer.BUILTIN_PRIMITIVE_TYPES and p.form != EpiVariable.Form.Pointer:

                    builder.line(f'inline {ptype}& Get{p.name}() {{ {body_get} }} \\')
                    ptype = f'const {ptype}&'

                builder.line(f'inline {ptype} Get{p.name}() const {{ {body_get} }} \\')

                if not any(a.tokentype == TokenType.ReadOnly for a in p.attrs):
                    builder.line(f'inline void Set{p.name}({ptype} value) {{ {body_set} }} \\')

            builder.line('\\')

            # pidx
            builder.line(f'enum {clss.name}_PIDXs \\')
            builder.line('{ \\')
            builder.tab()

            for i, p in enumerate(clss.properties):
                builder.line(f'PIDX_{p.name} = {i}, \\')

            builder.line(f'PIDX_COUNT = {len(clss.properties)} \\')

            builder.tab(-1)
            builder.line('};')

            builder.line_empty()

            return builder

        def emit_skeleton_class(clss: EpiClass, builder: Builder = Builder()) -> Builder:

            clss_parent = clss.parent if clss.parent is not None else 'Object'
            builder.line(f'class {clss.name} : public {clss_parent}')
            builder.line('{')
            builder.anchor_gen_region(f'{clss.name}')

            emit_class_declaration(clss, builder)

            builder.anchor_gen_endregion(f'{clss.name}')
            builder.tab(-1)
            builder.line('};')
            builder.line_empty()

            return builder

        def emit_class_declaration(clss: EpiClass, builder: Builder = Builder()) -> Builder:

            builder.line('public:')
            builder.tab()
            builder.line(f'EPI_GENHIDDEN_{clss.name}()')
            builder.line_empty()

            crc = hex(zlib.crc32(clss.name.encode()) & 0xffffffff)
            builder.line(f'constexpr static MetaTypeID TypeID{{{crc}}};')
            builder.line_empty()

            # pids
            builder.line(f'enum {clss.name}_PIDs')
            builder.line('{')
            builder.tab()

            for p in clss.properties:

                crc = hex(zlib.crc32(p.name.encode()) & 0xffffffff)
                builder.line(f'PID_{p.name} = {crc},')

            builder.line(f'PID_COUNT = {len(clss.properties)}')

            builder.tab(-1)
            builder.line('};')
            builder.line_empty()

            # prts
            distinguished = False
            for p in clss.properties:

                if not any(a.tokentype == TokenType.Virtual for a in p.attrs):
                    continue

                if not distinguished:

                    builder.tab(-1)
                    builder.line('protected:')
                    builder.tab()
                    distinguished = True

                ptype = p.tokentype.text

                if p.form == EpiVariable.Form.Array:
                    ptype = f'{ptype}<{p.nestedtokentype.text}>'

                if ptype not in Tokenizer.BUILTIN_PRIMITIVE_TYPES and p.form != EpiVariable.Form.Pointer:

                    builder.line(f'{ptype}& Get{p.name}_Callback();')
                    ptype = f'const {ptype}&'

                builder.line(f'{ptype} Get{p.name}_Callback() const;')

                if not any(a.tokentype == TokenType.ReadOnly for a in p.attrs):
                    builder.line(f'void Set{p.name}_Callback({ptype} value);')

            if distinguished:
                builder.line_empty()

            builder.tab(-1)
            builder.line('protected:')
            builder.tab()

            # prts
            for p in clss.properties:

                if any(a.tokentype == TokenType.Virtual for a in p.attrs):
                    continue

                typename = f'{p.tokentype.text}'
                if p.form == EpiVariable.Form.Array:
                    typename = f'{typename}<{p.nestedtokentype.text}>'
                value = f'{{{p.value}}}' if p.value is not None else ''

                builder.line(f'{typename} m_{p.name}{value};')

            builder.line_empty()

            return builder

        os.makedirs(os.path.dirname(os.path.join(self.output_dir, basename)), exist_ok=True)
        os.makedirs(os.path.dirname(os.path.join(self.output_dir_cxx_hxx, basename)), exist_ok=True)
        basename = os.path.splitext(basename)[0]

        if not os.path.exists(f'{os.path.join(self.output_dir, basename)}.cpp'):

            with open(f'{os.path.join(self.output_dir, basename)}.cpp', 'w') as f:
                f.write(emit_sekeleton_file(basename, 'cpp'))

        if not os.path.exists(f'{os.path.join(self.output_dir, basename)}.h'):

            with open(f'{os.path.join(self.output_dir, basename)}.h', 'w') as f:
                f.write(emit_sekeleton_file(basename, 'h'))

        with open(f'{os.path.join(self.output_dir_cxx_hxx, basename)}.hxx', 'w') as f:
            f.write(emit_sekeleton_file(basename, 'hxx'))

        with open(f'{os.path.join(self.output_dir_cxx_hxx, basename)}.cxx', 'w') as f:
            f.write(emit_sekeleton_file(basename, 'cxx'))

        assert isinstance(symbol, EpiClass)

        injection = f'{emit_class_serialization(symbol).build()}\n'
        self._code_generate_inject(injection, basename, 'cxx', before='EPI_NAMESPACE_END()')

        injection = f'{emit_class_meta(symbol).build()}\n'
        self._code_generate_inject(injection, basename, 'cxx', before='EPI_NAMESPACE_END()')

        injection = f'\n{emit_class_declaration_hidden(symbol).build()}'
        self._code_generate_inject(injection, basename, 'hxx')

        if self._lookup(f'EPI_GENREGION_END({symbol.name})', basename, 'h') == -1:

            if self._lookup(f'EPI_GENREGION_BEGIN({symbol.name})', basename, 'h') != -1:

                tip = f'`EPI_GENREGION_END({symbol.name})` is absent while corresponding anchor `EPI_GENREGION_BEGIN({symbol.name})` is present'
                raise CodeGenerationError(f'{basename}.h', CodeGenerationErrorCode.CorruptedAnchor, tip)

            injection = f'{emit_skeleton_class(symbol).build()}\n'
            self._code_generate_inject(
                injection,
                basename,
                'h',
                before='EPI_NAMESPACE_END()'
            )

        else:

            if self._lookup(f'EPI_GENREGION_BEGIN({symbol.name})', basename, 'h') == -1:

                tip = f'`EPI_GENREGION_BEGIN({symbol.name})` is absent while corresponding anchor `EPI_GENREGION_END({symbol.name})` is present'
                raise CodeGenerationError(f'{basename}.h', CodeGenerationErrorCode.CorruptedAnchor, tip)

            injection = f'\n{emit_class_declaration(symbol).build()}\n'
            self._code_generate_inject(
                injection,
                basename,
                'h',
                before=f'EPI_GENREGION_END({symbol.name})',
                after=f'EPI_GENREGION_BEGIN({symbol.name})'
            )
