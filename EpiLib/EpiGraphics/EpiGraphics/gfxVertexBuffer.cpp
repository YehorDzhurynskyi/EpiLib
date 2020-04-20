#include "EpiGraphics/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxVertexBuffer.h"
#include "EpiGraphics/gfxVertexBuffer.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

gfxVertexBuffer::~gfxVertexBuffer()
{
    if (GetIsCreated())
    {
        Destroy();
    }
}

gfxVertexBuffer::gfxVertexBuffer(gfxVertexBuffer&& rhs)
{
    m_ID = rhs.m_ID;
    m_Capacity = rhs.m_Capacity;
    rhs.m_ID = 0;
    rhs.m_Capacity = 0;
}

gfxVertexBuffer& gfxVertexBuffer::operator=(gfxVertexBuffer&& rhs)
{
    m_ID = rhs.m_ID;
    m_Capacity = rhs.m_Capacity;
    rhs.m_ID = 0;
    rhs.m_Capacity = 0;

    return *this;
}

void gfxVertexBuffer::Create(void* initData, epiSize_t capacity, gfxVertexBufferUsage usage)
{
    epiExpect(!GetIsCreated(), "Create method should be called on destroyed vertex buffer");
    epiExpect(capacity > 0, "Capacity of buffer should be greater than 0");

    GLenum glUsage;
    switch (usage)
    {
    case gfxVertexBufferUsage::StaticRead: glUsage = GL_STATIC_READ; break;
    case gfxVertexBufferUsage::StaticDraw: glUsage = GL_STATIC_DRAW; break;
    case gfxVertexBufferUsage::DynamicRead:  glUsage = GL_DYNAMIC_READ; break;
    case gfxVertexBufferUsage::DynamicDraw: glUsage = GL_DYNAMIC_DRAW; break;
    case gfxVertexBufferUsage::StreamRead:  glUsage = GL_STREAM_READ; break;
    case gfxVertexBufferUsage::StreamDraw: glUsage = GL_STREAM_DRAW; break;
    default: epiAssert(false, "Unhandled case"); return;
    }

    glGenBuffers(1, &m_ID);
    if (m_ID == 0)
    {
        return;
    }

    Bind();
    glBufferData(GL_ARRAY_BUFFER, capacity, initData, glUsage);
    m_Capacity = capacity;
}

void gfxVertexBuffer::Destroy()
{
    epiExpect(GetIsCreated(), "Destroy method should be called on already created vertex buffer");

    glDeleteBuffers(1, &m_ID);
    m_ID = 0;
    m_Capacity = 0;
}

epiBool gfxVertexBuffer::GetIsCreated_Callback() const
{
    return m_ID != 0;
}

void gfxVertexBuffer::Bind()
{
    epiExpect(GetIsCreated(), "A vertex buffer expected to be created");

    super::Bind();
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void gfxVertexBuffer::UnBind()
{
    epiExpect(GetIsCreated(), "A vertex buffer expected to be created");

    super::UnBind();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void* gfxVertexBuffer::Map(gfxVertexBufferMapAccess access)
{
    epiExpect(GetIsCreated(), "A vertex buffer expected to be created");
    epiExpect(GetIsBounded(), "A vertex buffer expected to be bounded");
    epiExpect(!m_IsMapped, "A vertex buffer expected to be unmapped");

    GLenum glAccess;
    switch (access)
    {
    case gfxVertexBufferMapAccess::ReadOnly: glAccess = GL_READ_ONLY; break;
    case gfxVertexBufferMapAccess::WriteOnly: glAccess = GL_WRITE_ONLY; break;
    case gfxVertexBufferMapAccess::ReadWrite: glAccess = GL_READ_WRITE; break;
    default: epiAssert(false, "Unhandled case"); return nullptr;
    }

    m_IsMapped = true;
    return glMapBuffer(GL_ARRAY_BUFFER, glAccess);
}

epiBool gfxVertexBuffer::UnMap()
{
    epiExpect(GetIsCreated(), "A vertex buffer expected to be created");
    epiExpect(GetIsBounded(), "A vertex buffer expected to be bounded");
    epiExpect(m_IsMapped, "A vertex buffer expected to be mapped");

    m_IsMapped = false;
    return glUnmapBuffer(GL_ARRAY_BUFFER);
}

EPI_NAMESPACE_END()
