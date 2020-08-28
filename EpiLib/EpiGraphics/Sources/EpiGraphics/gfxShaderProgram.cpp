EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxShaderProgram.h"
#include "EpiGraphics/gfxShaderProgram.cxx"
EPI_GENREGION_END(include)

#include <glad/glad.h>

EPI_NAMESPACE_BEGIN()

gfxShader::~gfxShader()
{
    if (GetIsCreated())
    {
        Destroy();
    }
}

gfxShader::gfxShader(gfxShader&& rhs)
{
    m_ShaderID = rhs.m_ShaderID;
    m_Type = rhs.m_Type;
    rhs.m_ShaderID = 0;
    rhs.m_Type = gfxShaderType::None;
}

gfxShader& gfxShader::operator=(gfxShader&& rhs)
{
    m_ShaderID = rhs.m_ShaderID;
    m_Type = rhs.m_Type;
    rhs.m_ShaderID = 0;
    rhs.m_Type = gfxShaderType::None;

    return *this;
}

void gfxShader::CreateFromSource(const epiChar* source, gfxShaderType type)
{
    epiExpect(!GetIsCreated(), "Create method should be called on destroyed shader");

    GLenum glType;
    switch (type)
    {
    case gfxShaderType::Vertex: glType = GL_VERTEX_SHADER; break;
    case gfxShaderType::Geometry: glType = GL_GEOMETRY_SHADER; break;
    case gfxShaderType::Pixel: glType = GL_FRAGMENT_SHADER; break;
    default: epiAssert(false, "Unhandled case"); return;
    }

    m_ShaderID = glCreateShader(glType);
    if (m_ShaderID == 0)
    {
        return;
    }

    m_Type = type;

    glShaderSource(m_ShaderID, 1, &source, nullptr);
    glCompileShader(m_ShaderID);

    GLint status = 0;
    glGetShaderiv(m_ShaderID, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLchar log[4096];
        glGetShaderInfoLog(m_ShaderID, sizeof(log), nullptr, log);

        // TODO: log
        epiAssert(false, "");

        Destroy();
    }
}

void gfxShader::Destroy()
{
    epiExpect(GetIsCreated(), "Destroy method should be called on already created shader");

    glDeleteShader(m_ShaderID);
    m_ShaderID = 0;
    m_Type = gfxShaderType::None;
}

epiBool gfxShader::GetIsCreated_Callback() const
{
    return m_ShaderID != 0;
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

gfxShaderProgram::gfxShaderProgram(gfxShaderProgram&& rhs)
{
    m_ProgramID = rhs.m_ProgramID;
    m_ShaderVertex = rhs.m_ShaderVertex;
    m_ShaderGeometry = rhs.m_ShaderGeometry;
    m_ShaderPixel = rhs.m_ShaderPixel;
    rhs.m_ProgramID = 0;
    rhs.m_ShaderVertex = nullptr;
    rhs.m_ShaderGeometry = nullptr;
    rhs.m_ShaderPixel = nullptr;
}

gfxShaderProgram& gfxShaderProgram::operator=(gfxShaderProgram&& rhs)
{
    m_ProgramID = rhs.m_ProgramID;
    m_ShaderVertex = rhs.m_ShaderVertex;
    m_ShaderGeometry = rhs.m_ShaderGeometry;
    m_ShaderPixel = rhs.m_ShaderPixel;
    rhs.m_ProgramID = 0;
    rhs.m_ShaderVertex = nullptr;
    rhs.m_ShaderGeometry = nullptr;
    rhs.m_ShaderPixel = nullptr;

    return *this;
}

void gfxShaderProgram::Create()
{
    epiExpect(!GetIsCreated(), "Create method should be called on destroyed shader program");

    m_ProgramID = glCreateProgram();
}

void gfxShaderProgram::Destroy()
{
    epiExpect(GetIsCreated(), "Destroy method should be called on already created shader program");

    glDeleteProgram(m_ProgramID);
    m_ProgramID = 0;
    m_ShaderVertex = nullptr;
    m_ShaderGeometry = nullptr;
    m_ShaderPixel = nullptr;
}

epiBool gfxShaderProgram::GetIsCreated_Callback() const
{
    return m_ProgramID != 0;
}

void gfxShaderProgram::ShaderAttach(const gfxShader& shader)
{
    epiExpect(GetIsCreated(), "A program expected to be created");
    epiExpect(shader.GetIsCreated(), "A shader expected to be created");

    const gfxShader** attached = nullptr;

    switch (shader.GetType())
    {
    case gfxShaderType::Vertex: attached = &m_ShaderVertex; break;
    case gfxShaderType::Geometry: attached = &m_ShaderGeometry; break;
    case gfxShaderType::Pixel: attached = &m_ShaderPixel; break;
    default: epiAssert(false, "Unhandled case"); return;
    }

    epiExpect(*attached == nullptr, "Shader type is already attached");
    if (*attached != nullptr)
    {
        return;
    }

    glAttachShader(m_ProgramID, shader.GetShaderID());
    *attached = &shader;
}

void gfxShaderProgram::ShaderDettach(gfxShaderType type)
{
    epiExpect(GetIsCreated(), "A program expected to be created");

    const gfxShader** attached = nullptr;

    switch (type)
    {
    case gfxShaderType::Vertex: attached = &m_ShaderVertex; break;
    case gfxShaderType::Geometry: attached = &m_ShaderGeometry; break;
    case gfxShaderType::Pixel: attached = &m_ShaderPixel; break;
    default: epiAssert(false, "Unhandled case"); return;
    }

    epiExpect(*attached != nullptr, "Shader type is already dettached");
    if (*attached == nullptr)
    {
        return;
    }

    glDetachShader(m_ProgramID, (*attached)->GetShaderID());
    *attached = nullptr;
}

void gfxShaderProgram::Build()
{
    epiExpect(GetIsCreated(), "A program expected to be created");
    epiExpect(m_ShaderVertex && m_ShaderPixel, "A program should have vertex and pixel shader be attached");

    glLinkProgram(m_ProgramID);

    GLint status = 0;
    glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLchar log[4096];
        glGetProgramInfoLog(m_ProgramID, sizeof(log), nullptr, log);

        // TODO: log
        epiAssert(false, "");

        Destroy();
    }
    else
    {
        if (m_ShaderVertex) ShaderDettach(gfxShaderType::Vertex);
        if (m_ShaderGeometry) ShaderDettach(gfxShaderType::Geometry);
        if (m_ShaderPixel) ShaderDettach(gfxShaderType::Pixel);
    }
}

void gfxShaderProgram::Bind()
{
    epiExpect(GetIsCreated(), "A program expected to be created");

    super::Bind();
    glUseProgram(m_ProgramID);
}

void gfxShaderProgram::UnBind()
{
    epiExpect(GetIsCreated(), "A program expected to be created");

    super::UnBind();
    glUseProgram(0);
}

EPI_NAMESPACE_END()
