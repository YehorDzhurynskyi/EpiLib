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

EPI_NAMESPACE_END()
