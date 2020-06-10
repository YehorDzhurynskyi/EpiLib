import os
import zlib
import pickle
import hashlib
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

    def __init__(self, input_dir: str, output_dir: str, output_dir_cxx_hxx: str):

        self.input_dir = input_dir
        self.output_dir = output_dir
        self.output_dir_cxx_hxx = output_dir_cxx_hxx
        self.generated_files_cache = {}
        self.files_outbuff_cache = {}

        if os.path.exists(f'{output_dir_cxx_hxx}/epigen_cache.bin'):

            with open(f'{output_dir_cxx_hxx}/epigen_cache.bin', 'rb') as f:
                self.generated_files_cache = pickle.load(f)

    def dump(self):

        for path, content in self.files_outbuff_cache.items():

            with open(path, 'w') as f:
                f.write(content)

            self.generated_files_cache[path] = hashlib.md5(content.encode()).hexdigest()

        with open(f'{self.output_dir_cxx_hxx}/epigen_cache.bin', 'wb') as f:
            pickle.dump(self.generated_files_cache, f)

    def _lookup(self, needle: str, basename: str, ext: str) -> int:

        assert ext == 'h' or ext == 'cpp'

        path = f'{os.path.join(self.output_dir, basename)}.{ext}'
        if path not in self.files_outbuff_cache:

            with open(path, 'r') as f:

                content = f.read()
                self.files_outbuff_cache[path] = content

        content = self.files_outbuff_cache[path]

        return content.find(needle)

    def _should_be_regenerated(self, basename: str, ext: str):

        if ext == 'cxx' or ext == 'hxx':
            filename = f'{os.path.join(self.output_dir_cxx_hxx, basename)}.{ext}'
        elif ext == 'cpp' or ext == 'h':
            filename = f'{os.path.join(self.output_dir, basename)}.{ext}'
        else:
            assert False, "Unexpected file extension"

        if not os.path.exists(filename):
            return True

        if filename not in self.generated_files_cache:
            return True

        checksum = self.generated_files_cache[filename]
        if self._calc_file_checksum(filename) != checksum:
            return True

        epifilename = f'{os.path.join(self.input_dir, basename)}.epi'
        assert os.path.exists(epifilename)

        if epifilename not in self.generated_files_cache:
            return True

        epichecksum = self.generated_files_cache[epifilename]
        if self._calc_file_checksum(epifilename) != epichecksum:
            return True

        return False

    def _calc_file_checksum(self, filename: str):

        with open(filename, 'r') as f:

            content = f.read()
            digest = hashlib.md5(content.encode()).hexdigest()

        return digest

    def _code_generate_inject(self,
                              inj: str,
                              basename: str,
                              ext: str,
                              before: str = None,
                              after: str = None):

        outdir = self.output_dir if ext == 'h' or ext == 'cpp' else self.output_dir_cxx_hxx

        path = f'{os.path.join(outdir, basename)}.{ext}'
        if path not in self.files_outbuff_cache:

            with open(path, 'r') as f:
                content = f.read()

        else:
            content = self.files_outbuff_cache[path]

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

        self.files_outbuff_cache[path] = content[:lbound] + inj + content[rbound:]

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

                # TODO: remove rstrip
                hash_type = f'epiHashCompileTime({p.tokentype.text.rstrip("*")})'

                flags = []

                attr_readcallback = p.find_attr(TokenType.ReadCallback)
                attr_writecallback = p.find_attr(TokenType.WriteCallback)
                attr_readonly = p.find_attr(TokenType.ReadOnly)
                attr_writeonly = p.find_attr(TokenType.WriteOnly)

                if attr_readcallback is not None:
                    flags.append('ReadCallback')
                if attr_writecallback is not None:
                    flags.append('WriteCallback')
                if attr_readonly is not None:
                    flags.append('ReadOnly')
                if attr_writeonly is not None:
                    flags.append('WriteOnly')

                builder.line('{')
                builder.tab()
                builder.line('MetaProperty m = epiMetaProperty(')
                builder.tab()
                builder.line(f'/* Name */ "{p.name}",')

                ptrread = '/* PtrRead */ nullptr,'
                if attr_writeonly is None:
                    if attr_readcallback is None:
                        ptrread = f'/* PtrRead */ (void*)offsetof({clss.name}, m_{p.name}),'
                    elif attr_writeonly is None:
                        ptrread = f'/* PtrRead */ (void*)offsetof({clss.name}, Get{p.name}_FuncPtr),'

                builder.line(ptrread)

                ptrwrite = '/* PtrWrite */ nullptr,'
                if attr_readonly is None:
                    if attr_writecallback is None:
                        ptrwrite = f'/* PtrWrite */ (void*)offsetof({clss.name}, m_{p.name}),'
                    else:
                        ptrwrite = f'/* PtrWrite */ (void*)offsetof({clss.name}, Set{p.name}_FuncPtr),'

                builder.line(ptrwrite)

                flags = [f'MetaProperty::Flags::Mask{f}' for f in flags]
                builder.line(f'/* Flags */ {{{ " | ".join(flags) }}},')
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
            builder.line('public: \\')

            content = \
f'''

using super = {clss_parent};

static MetaClass EmitMetaClass();

const MetaClass& GetMetaClass() const override
{{
    super::GetMetaClass();
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

                    elif a.tokentype == TokenType.ExpectMax:

                        v = a.params[0].text
                        body_prologue_set = f'{body_prologue_set}epiExpect(value <= {v});'

                    elif a.tokentype == TokenType.ForceMin:

                        v = a.params[0].text
                        body_prologue_set = f'{body_prologue_set}value = std::max(value, {v});'

                    elif a.tokentype == TokenType.ForceMax:

                        v = a.params[0].text
                        body_prologue_set = f'{body_prologue_set}value = std::min(value, {v});'

                    elif a.tokentype == TokenType.ReadCallback:
                        body_epilogue_get = f'return Get{p.name}_Callback();'

                    elif a.tokentype == TokenType.WriteCallback:
                        body_epilogue_set = f'Set{p.name}_Callback(value);'

                body_get = f'{body_prologue_get}{body_epilogue_get}'
                body_set = f'{body_prologue_set}{body_epilogue_set}'

                if not any(a.tokentype == TokenType.WriteOnly for a in p.attrs):

                    pptype = ptype
                    if pptype not in Tokenizer.BUILTIN_PRIMITIVE_TYPES and p.form != EpiVariable.Form.Pointer:

                        attr_readcallback = p.find_attr(TokenType.ReadCallback)
                        if not attr_readcallback or attr_readcallback.find_param('"SuppressRef"') is None:

                            if not attr_readcallback:
                                builder.line(f'{pptype}& Get{p.name}() {{ {body_get} }} \\')

                            pptype = f'const {pptype}&'

                    builder.line(f'{pptype} Get{p.name}() const {{ {body_get} }} \\')

                if not any(a.tokentype == TokenType.ReadOnly for a in p.attrs):

                    pptype = ptype
                    if ptype not in Tokenizer.BUILTIN_PRIMITIVE_TYPES and p.form != EpiVariable.Form.Pointer:

                        attr_writecallback = p.find_attr(TokenType.WriteCallback)
                        if not attr_writecallback or attr_writecallback.find_param('"SuppressRef"') is None:
                            pptype = f'const {pptype}&'

                    builder.line(f'void Set{p.name}({pptype} value) {{ {body_set} }} \\')

            builder.line('\\')

            # pidx
            builder.line(f'enum {clss.name}_PIDXs \\')
            builder.line('{ \\')
            builder.tab()

            for i, p in enumerate(clss.properties):
                builder.line(f'PIDX_{p.name} = {i}, \\')

            builder.line(f'PIDX_COUNT = {len(clss.properties)} \\')

            builder.tab(-1)
            builder.line('}; \\')

            builder.line(' \\')
            builder.line('private: \\')

            # getters/setters function pointers
            for p in clss.properties:

                ptype = p.tokentype.text

                if p.form == EpiVariable.Form.Array:
                    ptype = f'{ptype}<{p.nestedtokentype.text}>'

                attr_readcallback = p.find_attr(TokenType.ReadCallback)
                attr_writecallback = p.find_attr(TokenType.WriteCallback)
                attr_readonly = p.find_attr(TokenType.ReadOnly)
                attr_writeonly = p.find_attr(TokenType.WriteOnly)

                if attr_readcallback is not None and attr_writeonly is None:

                    if ptype not in Tokenizer.BUILTIN_PRIMITIVE_TYPES and p.form != EpiVariable.Form.Pointer and attr_readcallback.find_param('"SuppressRef"') is None:
                        builder.line(f'const {ptype}& ({clss.name}::*Get{p.name}_FuncPtr)() const {{ &{clss.name}::Get{p.name} }}; \\')
                    else:
                        builder.line(f'{ptype} ({clss.name}::*Get{p.name}_FuncPtr)() const {{ &{clss.name}::Get{p.name} }}; \\')

                if attr_writecallback is not None and attr_readonly is None:

                    if ptype not in Tokenizer.BUILTIN_PRIMITIVE_TYPES and p.form != EpiVariable.Form.Pointer and attr_writecallback.find_param('"SuppressRef"') is None:
                        builder.line(f'void ({clss.name}::*Set{p.name}_FuncPtr)(const {ptype}&) {{ &{clss.name}::Set{p.name} }}; \\')
                    else:
                        builder.line(f'void ({clss.name}::*Set{p.name}_FuncPtr)({ptype}) {{ &{clss.name}::Set{p.name} }}; \\')

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

        def emit_properties(properties: list, accessor_modifier: str, builder: Builder = Builder()) -> Builder:

            if len(properties) == 0:
                return builder

            builder.tab(-1)
            builder.line(f'{accessor_modifier}:')
            builder.tab()

            for p in properties:

                typename = f'{p.tokentype.text}'
                if p.form == EpiVariable.Form.Array:
                    typename = f'{typename}<{p.nestedtokentype.text}>'
                value = f'{{{p.value}}}' if p.value is not None else ''

                builder.line(f'{typename} m_{p.name}{value};')

            builder.line_empty()

            return builder

        def emit_property_callbacks(properties: list, accessor_modifier: str, builder: Builder = Builder()) -> Builder:

            if len(properties) == 0:
                return builder

            builder.tab(-1)
            builder.line(f'{accessor_modifier}:')
            builder.tab()

            for p in properties:

                attr_readcallback = p.find_attr(TokenType.ReadCallback)
                attr_writecallback = p.find_attr(TokenType.WriteCallback)

                ptype = p.tokentype.text
                if p.form == EpiVariable.Form.Array:
                    ptype = f'{ptype}<{p.nestedtokentype.text}>'

                if attr_readcallback and not any(a.tokentype == TokenType.WriteOnly for a in p.attrs):

                    pptype = ptype
                    if pptype not in Tokenizer.BUILTIN_PRIMITIVE_TYPES and p.form != EpiVariable.Form.Pointer:
    
                        if attr_readcallback.find_param('"SuppressRef"') is None:
                            pptype = f'const {pptype}&'

                    builder.line(f'{pptype} Get{p.name}_Callback() const;')

                if attr_writecallback and not any(a.tokentype == TokenType.ReadOnly for a in p.attrs):

                    pptype = ptype
                    if pptype not in Tokenizer.BUILTIN_PRIMITIVE_TYPES and p.form != EpiVariable.Form.Pointer:

                        if attr_writecallback.find_param('"SuppressRef"') is None:
                            pptype = f'const {pptype}&'

                    builder.line(f'void Set{p.name}_Callback({pptype} value);')

            builder.line_empty()

            return builder

        def emit_class_declaration(clss: EpiClass, builder: Builder = Builder()) -> Builder:

            builder.line_empty()
            builder.line(f'EPI_GENHIDDEN_{clss.name}()')
            builder.line_empty()
            builder.line('public:')
            builder.tab()

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

            filter_properties_non_virtual = lambda p: not any(a.tokentype in [
                TokenType.Virtual,
            ] for a in p.attrs)

            filter_properties_cb = lambda p: any(a.tokentype in [
                TokenType.ReadCallback,
                TokenType.WriteCallback
            ] for a in p.attrs)

            filter_properties_non_private = lambda p: not any(a.tokentype in [
                TokenType.Private
            ] for a in p.attrs)

            filter_properties_private = lambda p: any(a.tokentype in [
                TokenType.Private
            ] for a in p.attrs)

            properties_cb = list(filter(filter_properties_cb, clss.properties))
            properties_non_private = list(filter(filter_properties_non_private, properties_cb))
            properties_private = list(filter(filter_properties_private, properties_cb))

            emit_property_callbacks(properties_non_private, 'protected', builder)
            emit_property_callbacks(properties_private, 'private', builder)

            properties_non_virtual = list(filter(filter_properties_non_virtual, clss.properties))
            properties_non_private = list(filter(filter_properties_non_private, properties_non_virtual))
            properties_private = list(filter(filter_properties_private, properties_non_virtual))

            emit_properties(properties_non_private, 'protected', builder)
            emit_properties(properties_private, 'private', builder)

            return builder

        os.makedirs(os.path.dirname(os.path.join(self.output_dir, basename)), exist_ok=True)
        os.makedirs(os.path.dirname(os.path.join(self.output_dir_cxx_hxx, basename)), exist_ok=True)
        basename = os.path.splitext(basename)[0]

        assert isinstance(symbol, EpiClass)

        if self._should_be_regenerated(basename, 'hxx'):

            filename = f'{os.path.join(self.output_dir_cxx_hxx, basename)}.hxx'
            with open(filename, 'w') as f:
                f.write(emit_sekeleton_file(basename, 'hxx'))

            injection = f'\n{emit_class_declaration_hidden(symbol).build()}'
            self._code_generate_inject(injection, basename, 'hxx')

        if self._should_be_regenerated(basename, 'cxx'):

            filename = f'{os.path.join(self.output_dir_cxx_hxx, basename)}.cxx'
            with open(filename, 'w') as f:
                f.write(emit_sekeleton_file(basename, 'cxx'))

            injection = f'{emit_class_serialization(symbol).build()}\n'
            self._code_generate_inject(injection, basename, 'cxx', before='EPI_NAMESPACE_END()')

            injection = f'{emit_class_meta(symbol).build()}\n'
            self._code_generate_inject(injection, basename, 'cxx', before='EPI_NAMESPACE_END()')

        if self._should_be_regenerated(basename, 'cpp'):

            filename = f'{os.path.join(self.output_dir, basename)}.cpp'
            if not os.path.exists(filename):
                with open(filename, 'w') as f:
                    f.write(emit_sekeleton_file(basename, 'cpp'))

            # NOTE: fake injection to force cache its content
            self._code_generate_inject('', basename, 'cpp', before='EPI_NAMESPACE_END()')

        if self._should_be_regenerated(basename, 'h'):

            filename = f'{os.path.join(self.output_dir, basename)}.h'
            if not os.path.exists(filename):
                with open(filename, 'w') as f:
                    f.write(emit_sekeleton_file(basename, 'h'))

            if self._lookup(f'EPI_GENREGION_END({symbol.name})', basename, 'h') == -1:

                if self._lookup(f'EPI_GENREGION_BEGIN({symbol.name})', basename, 'h') != -1:

                    tip = f'`EPI_GENREGION_END({symbol.name})` is absent while corresponding anchor `EPI_GENREGION_BEGIN({symbol.name})` is present'
                    raise CodeGenerationError(f'{basename}.h', CodeGenerationErrorCode.CorruptedAnchor, tip)

                # NOTE: symbol isn't present add it to the end
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

                # NOTE: symbol is present add it to the corresponding region
                injection = f'\n{emit_class_declaration(symbol).build()}\n'
                self._code_generate_inject(
                    injection,
                    basename,
                    'h',
                    before=f'EPI_GENREGION_END({symbol.name})',
                    after=f'EPI_GENREGION_BEGIN({symbol.name})'
                )

        epifilename = f'{os.path.join(self.input_dir, basename)}.epi'
        with open(epifilename, 'r') as f:
            epicontent = f.read()

        self.generated_files_cache[epifilename] = hashlib.md5(epicontent.encode()).hexdigest()

