#include "EpiGraphicsDriverGL/gfxShaderProgramImplGL.h"

#include <glad/glad.h>

EPI_NAMESPACE_BEGIN()

gfxShaderImplGL::gfxShaderImplGL(gfxShaderImplGL&& rhs)
{
    m_ID = rhs.m_ID;
    m_Type = rhs.m_Type;
    rhs.m_ID = 0;
    rhs.m_Type = gfxShaderType::None;
}

gfxShaderImplGL& gfxShaderImplGL::operator=(gfxShaderImplGL&& rhs)
{
    m_ID = rhs.m_ID;
    m_Type = rhs.m_Type;
    rhs.m_ID = 0;
    rhs.m_Type = gfxShaderType::None;

    return *this;
}

void gfxShaderImplGL::CreateFromSource(const epiChar* source, gfxShaderType type)
{
    GLenum glType;
    switch (type)
    {
    case gfxShaderType::Vertex: glType = GL_VERTEX_SHADER; break;
    case gfxShaderType::Geometry: glType = GL_GEOMETRY_SHADER; break;
    case gfxShaderType::Pixel: glType = GL_FRAGMENT_SHADER; break;
    default: epiAssert(false, "Unhandled case"); return;
    }

    m_ID = glCreateShader(glType);
    if (m_ID == 0)
    {
        return;
    }

    m_Type = type;

    glShaderSource(m_ID, 1, &source, nullptr);
    glCompileShader(m_ID);

    GLint status = 0;
    glGetShaderiv(m_ID, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLchar log[4096];
        glGetShaderInfoLog(m_ID, sizeof(log), nullptr, log);

        epiLogFatal("OpenGL shader compilation has failed!: {}", log);

        Destroy();
    }
}

void gfxShaderImplGL::Destroy()
{
    glDeleteShader(m_ID);
    m_ID = 0;
    m_Type = gfxShaderType::None;
}

epiBool gfxShaderImplGL::GetIsCreated() const
{
    return m_ID != 0 && m_Type != gfxShaderType::None;
}

epiU32 gfxShaderImplGL::GetID() const
{
    return m_ID;
}

gfxShaderType gfxShaderImplGL::GetType() const
{
    return m_Type;
}

gfxShaderProgramImplGL::gfxShaderProgramImplGL(gfxShaderProgramImplGL&& rhs)
{
    m_ID = rhs.m_ID;
    m_ShaderVertex = rhs.m_ShaderVertex;
    m_ShaderGeometry = rhs.m_ShaderGeometry;
    m_ShaderPixel = rhs.m_ShaderPixel;
    rhs.m_ID = 0;
    rhs.m_ShaderVertex = nullptr;
    rhs.m_ShaderGeometry = nullptr;
    rhs.m_ShaderPixel = nullptr;
}

gfxShaderProgramImplGL& gfxShaderProgramImplGL::operator=(gfxShaderProgramImplGL&& rhs)
{
    m_ID = rhs.m_ID;
    m_ShaderVertex = rhs.m_ShaderVertex;
    m_ShaderGeometry = rhs.m_ShaderGeometry;
    m_ShaderPixel = rhs.m_ShaderPixel;
    rhs.m_ID = 0;
    rhs.m_ShaderVertex = nullptr;
    rhs.m_ShaderGeometry = nullptr;
    rhs.m_ShaderPixel = nullptr;

    return *this;
}

void gfxShaderProgramImplGL::Create()
{
    m_ID = glCreateProgram();
}

void gfxShaderProgramImplGL::Destroy()
{
    glDeleteProgram(m_ID);
    m_ID = 0;
    m_ShaderVertex = nullptr;
    m_ShaderGeometry = nullptr;
    m_ShaderPixel = nullptr;
}

epiBool gfxShaderProgramImplGL::GetIsCreated() const
{
    return m_ID != 0;
}

epiU32 gfxShaderProgramImplGL::GetID() const
{
    return m_ID;
}

void gfxShaderProgramImplGL::ShaderAttach(const gfxShaderImpl& shader)
{
    const gfxShaderImplGL** attached = nullptr;

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

    glAttachShader(m_ID, shader.GetID());
    *attached = static_cast<const gfxShaderImplGL*>(&shader);
}

void gfxShaderProgramImplGL::ShaderDettach(gfxShaderType type)
{
    const gfxShaderImplGL** attached = nullptr;

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

    glDetachShader(m_ID, (*attached)->GetID());
    *attached = nullptr;
}

void gfxShaderProgramImplGL::Build()
{
    epiExpect(m_ShaderVertex && m_ShaderPixel, "A program should have vertex and pixel shader be attached");

    glLinkProgram(m_ID);

    GLint status = 0;
    glGetProgramiv(m_ID, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLchar log[4096];
        glGetProgramInfoLog(m_ID, sizeof(log), nullptr, log);

        epiLogFatal("OpenGL shader linking has failed!: {}", log);

        Destroy();
    }
    else
    {
        if (m_ShaderVertex) ShaderDettach(gfxShaderType::Vertex);
        if (m_ShaderGeometry) ShaderDettach(gfxShaderType::Geometry);
        if (m_ShaderPixel) ShaderDettach(gfxShaderType::Pixel);
    }
}

void gfxShaderProgramImplGL::Bind()
{
    glUseProgram(m_ID);
}

void gfxShaderProgramImplGL::UnBind()
{
    glUseProgram(0);
}

EPI_NAMESPACE_END()
