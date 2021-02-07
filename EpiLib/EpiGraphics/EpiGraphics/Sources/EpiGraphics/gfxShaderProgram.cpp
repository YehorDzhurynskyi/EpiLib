EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxShaderProgram.h"
#include "EpiGraphics/gfxShaderProgram.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

gfxShader::~gfxShader()
{
    if (GetIsCreated())
    {
        Destroy();
    }
}

void gfxShader::CreateFromSource(const epiChar* source, gfxShaderType type)
{
    epiExpect(!GetIsCreated(), "Create method should be called on destroyed shader");

    m_Impl->CreateFromSource(source, type);
}

void gfxShader::Destroy()
{
    epiExpect(GetIsCreated(), "Destroy method should be called on already created shader");

    m_Impl->Destroy();
}

epiBool gfxShader::GetIsCreated_Callback() const
{
    return m_Impl->GetIsCreated();
}

epiU32 gfxShader::GetID_Callback() const
{
    return m_Impl->GetID();
}

gfxShaderType gfxShader::GetType_Callback() const
{
    return m_Impl->GetType();
}

gfxShaderProgram::gfxShaderProgram()
{
    Create();
}

gfxShaderProgram::~gfxShaderProgram()
{
    if (GetIsCreated())
    {
        Destroy();
    }
}

void gfxShaderProgram::Create()
{
    epiExpect(!GetIsCreated(), "Create method should be called on destroyed shader program");

    m_Impl->Create();
}

void gfxShaderProgram::Destroy()
{
    epiExpect(GetIsCreated(), "Destroy method should be called on already created shader program");

    m_Impl->Destroy();
}

epiBool gfxShaderProgram::GetIsCreated_Callback() const
{
    return m_Impl->GetIsCreated();
}

epiU32 gfxShaderProgram::GetID_Callback() const
{
    return m_Impl->GetID();
}

void gfxShaderProgram::ShaderAttach(const gfxShader& shader)
{
    epiExpect(GetIsCreated(), "A program expected to be created");
    epiExpect(shader.GetIsCreated(), "A shader expected to be created");

    m_Impl->ShaderAttach(*shader.m_Impl);
}

void gfxShaderProgram::ShaderDettach(gfxShaderType type)
{
    epiExpect(GetIsCreated(), "A program expected to be created");

    m_Impl->ShaderDettach(type);
}

void gfxShaderProgram::Build()
{
    epiExpect(GetIsCreated(), "A program expected to be created");

    m_Impl->Build();
}

void gfxShaderProgram::Bind()
{
    epiExpect(GetIsCreated(), "A program expected to be created");

    super::Bind();

    m_Impl->Bind();
}

void gfxShaderProgram::UnBind()
{
    epiExpect(GetIsCreated(), "A program expected to be created");

    super::UnBind();

    m_Impl->UnBind();
}

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

EPI_NAMESPACE_END()
