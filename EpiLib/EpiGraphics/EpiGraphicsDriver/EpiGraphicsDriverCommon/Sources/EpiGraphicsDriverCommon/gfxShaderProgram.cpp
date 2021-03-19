EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxShaderProgram.h"
#include "EpiGraphicsDriverCommon/gfxShaderProgram.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxShader::gfxShader(internalgfx::gfxShaderImpl* impl)
    : m_Impl{impl}
{
}

gfxShader::gfxShader(gfxShader&& rhs)
{
    m_Impl = rhs.m_Impl;
    rhs.m_Impl = nullptr;
}

gfxShader& gfxShader::operator=(gfxShader&& rhs)
{
    m_Impl = rhs.m_Impl;
    rhs.m_Impl = nullptr;

    return *this;
}

gfxShader::~gfxShader()
{
    delete m_Impl;
}

epiBool gfxShader::InitFromSource(const epiChar* source, gfxShaderType type, const epiChar* entryPoint)
{
    epiExpect(!GetIsCreated(), "Create method should be called on destroyed shader");

    return m_Impl->InitFromSource(source, type, entryPoint);
}

epiBool gfxShader::GetIsCreated_Callback() const
{
    return m_Impl->GetIsCreated();
}

gfxShaderType gfxShader::GetType_Callback() const
{
    return m_Impl->GetType();
}

epiBool gfxShaderProgramCreateInfo::GetIsEmpty_Callback() const
{
    static_assert(gfxShaderProgramCreateInfo::PID_COUNT == 4); // add another shader type or change counter
    return m_Vertex != nullptr || m_Geometry != nullptr || m_Fragment != nullptr;
}

gfxShaderProgram::gfxShaderProgram(internalgfx::gfxShaderProgramImpl* impl)
    : m_Impl{impl}
{
}

gfxShaderProgram::gfxShaderProgram(gfxShaderProgram&& rhs)
{
    m_Impl = rhs.m_Impl;
    rhs.m_Impl = nullptr;
}

gfxShaderProgram& gfxShaderProgram::operator=(gfxShaderProgram&& rhs)
{
    m_Impl = rhs.m_Impl;
    rhs.m_Impl = nullptr;

    return *this;
}

gfxShaderProgram::~gfxShaderProgram()
{
    delete m_Impl;
}

epiBool gfxShaderProgram::GetIsCreated_Callback() const
{
    return m_Impl->GetIsCreated();
}

#if 0
void gfxShaderProgram::Texture(const epiChar* name, epiU32 value)
{
    epiExpect(GetIsBounded());

    m_Impl->Texture(name, value);
}

void gfxShaderProgram::UniformFloat(const epiChar* name, epiFloat value)
{
    epiExpect(GetIsBounded());

    m_Impl->UniformFloat(name, value);
}

void gfxShaderProgram::UniformVec2f(const epiChar* name, const epiVec2f& value)
{
    epiExpect(GetIsBounded());

    m_Impl->UniformVec2f(name, value);
}

void gfxShaderProgram::UniformVec3f(const epiChar* name, const epiVec3f& value)
{
    epiExpect(GetIsBounded());

    m_Impl->UniformVec3f(name, value);
}

void gfxShaderProgram::UniformVec4f(const epiChar* name, const epiVec4f& value)
{
    epiExpect(GetIsBounded());

    m_Impl->UniformVec4f(name, value);
}

void gfxShaderProgram::UniformMat4x4f(const epiChar* name, const epiMat4x4f& value, epiBool transpose)
{
    epiExpect(GetIsBounded());

    m_Impl->UniformMat4x4f(name, value, transpose);
}

void gfxShaderProgram::UniformS32(const epiChar* name, epiS32 value)
{
    epiExpect(GetIsBounded());

    m_Impl->UniformS32(name, value);
}

void gfxShaderProgram::UniformVec2s(const epiChar* name, const epiVec2s& value)
{
    epiExpect(GetIsBounded());

    m_Impl->UniformVec2s(name, value);
}

void gfxShaderProgram::UniformVec3s(const epiChar* name, const epiVec3s& value)
{
    epiExpect(GetIsBounded());

    m_Impl->UniformVec3s(name, value);
}

void gfxShaderProgram::UniformVec4s(const epiChar* name, const epiVec4s& value)
{
    epiExpect(GetIsBounded());

    m_Impl->UniformVec4s(name, value);
}

void gfxShaderProgram::UniformU32(const epiChar* name, epiU32 value)
{
    epiExpect(GetIsBounded());

    m_Impl->UniformU32(name, value);
}

void gfxShaderProgram::UniformVec2u(const epiChar* name, const epiVec2u& value)
{
    epiExpect(GetIsBounded());

    m_Impl->UniformVec2u(name, value);
}

void gfxShaderProgram::UniformVec3u(const epiChar* name, const epiVec3u& value)
{
    epiExpect(GetIsBounded());

    m_Impl->UniformVec3u(name, value);
}

void gfxShaderProgram::UniformVec4u(const epiChar* name, const epiVec4u& value)
{
    epiExpect(GetIsBounded());

    m_Impl->UniformVec4u(name, value);
}
#endif

EPI_NAMESPACE_END()
