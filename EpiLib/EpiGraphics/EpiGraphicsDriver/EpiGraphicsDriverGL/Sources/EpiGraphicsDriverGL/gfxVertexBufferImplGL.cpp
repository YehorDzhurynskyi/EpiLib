#include "EpiGraphicsDriverGL/gfxVertexBufferImplGL.h"

#include <glad/glad.h>

EPI_NAMESPACE_BEGIN()

gfxVertexBufferLayoutAttributeImplGL::gfxVertexBufferLayoutAttributeImplGL(gfxVertexBufferLayoutAttributeImplGL&& rhs)
{
    m_Index = rhs.m_Index;
    m_Size = rhs.m_Size;
    m_Type = rhs.m_Type;
    m_Normalized = rhs.m_Normalized;
    m_Stride = rhs.m_Stride;
    m_Offset = rhs.m_Offset;

    m_Index = 0;
    m_Size = 0;
    m_Type = gfxVertexBufferLayoutAttributeType::NONE;
    m_Normalized = false;
    m_Stride = 0;
    m_Offset = 0;
}

gfxVertexBufferLayoutAttributeImplGL& gfxVertexBufferLayoutAttributeImplGL::operator=(gfxVertexBufferLayoutAttributeImplGL&& rhs)
{
    m_Index = rhs.m_Index;
    m_Size = rhs.m_Size;
    m_Type = rhs.m_Type;
    m_Normalized = rhs.m_Normalized;
    m_Stride = rhs.m_Stride;
    m_Offset = rhs.m_Offset;

    m_Index = 0;
    m_Size = 0;
    m_Type = gfxVertexBufferLayoutAttributeType::NONE;
    m_Normalized = false;
    m_Stride = 0;
    m_Offset = 0;

    return *this;
}

epiU32 gfxVertexBufferLayoutAttributeImplGL::GetIndex() const
{
    return m_Index;
}

void gfxVertexBufferLayoutAttributeImplGL::SetIndex(epiU32 value)
{
    m_Index = value;
}

epiSize_t gfxVertexBufferLayoutAttributeImplGL::GetSize() const
{
    return m_Size;
}

void gfxVertexBufferLayoutAttributeImplGL::SetSize(epiSize_t value)
{
    m_Size = value;
}

gfxVertexBufferLayoutAttributeType gfxVertexBufferLayoutAttributeImplGL::GetType() const
{
    return m_Type;
}

void gfxVertexBufferLayoutAttributeImplGL::SetType(gfxVertexBufferLayoutAttributeType value)
{
    m_Type = value;
}

epiBool gfxVertexBufferLayoutAttributeImplGL::GetNormalized() const
{
    return m_Normalized;
}

void gfxVertexBufferLayoutAttributeImplGL::SetNormalized(epiBool value)
{
    m_Normalized = value;
}

epiSize_t gfxVertexBufferLayoutAttributeImplGL::GetStride() const
{
    return m_Stride;
}

void gfxVertexBufferLayoutAttributeImplGL::SetStride(epiSize_t value)
{
    m_Stride = value;
}

epiSize_t gfxVertexBufferLayoutAttributeImplGL::GetOffset() const
{
    return m_Offset;
}

void gfxVertexBufferLayoutAttributeImplGL::SetOffset(epiSize_t value)
{
    m_Offset = value;
}

void gfxVertexBufferLayoutAttributeImplGL::Apply() const
{
    GLenum gltype = 0;
    switch (m_Type)
    {
    case gfxVertexBufferLayoutAttributeType::BYTE: gltype = GL_BYTE; break;
    case gfxVertexBufferLayoutAttributeType::UBYTE: gltype = GL_UNSIGNED_BYTE; break;
    case gfxVertexBufferLayoutAttributeType::SHORT: gltype = GL_SHORT; break;
    case gfxVertexBufferLayoutAttributeType::USHORT: gltype = GL_UNSIGNED_SHORT; break;
    case gfxVertexBufferLayoutAttributeType::INT: gltype = GL_INT; break;
    case gfxVertexBufferLayoutAttributeType::UINT: gltype = GL_UNSIGNED_INT; break;
    case gfxVertexBufferLayoutAttributeType::HALF_FLOAT: gltype = GL_HALF_FLOAT; break;
    case gfxVertexBufferLayoutAttributeType::FLOAT: gltype = GL_FLOAT; break;
    case gfxVertexBufferLayoutAttributeType::DOUBLE: gltype = GL_DOUBLE; break;
    default: epiAssert(false, "Unhandled case"); return;
    }

    glEnableVertexAttribArray(m_Index);
    glVertexAttribPointer(m_Index, m_Size, gltype, m_Normalized, m_Stride, (const void*)m_Offset);
}

void gfxVertexBufferLayoutImplGL::Apply() const
{
    for (auto& attr : m_Attributes)
    {
        attr.Apply();
    }
}

void gfxVertexBufferLayoutImplGL::Add(gfxVertexBufferLayoutAttributeImpl&& attr)
{
    m_Attributes.push_back(std::move(static_cast<gfxVertexBufferLayoutAttributeImplGL&&>(attr)));
}

gfxVertexBufferImplGL::gfxVertexBufferImplGL(gfxVertexBufferImplGL&& rhs)
{
    m_ID = rhs.m_ID;
    m_Capacity = rhs.m_Capacity;
    rhs.m_ID = 0;
    rhs.m_Capacity = 0;
}

gfxVertexBufferImplGL& gfxVertexBufferImplGL::operator=(gfxVertexBufferImplGL&& rhs)
{
    m_ID = rhs.m_ID;
    m_Capacity = rhs.m_Capacity;
    rhs.m_ID = 0;
    rhs.m_Capacity = 0;

    return *this;
}

void gfxVertexBufferImplGL::Create(const epiByte* initData, epiSize_t capacity, gfxVertexBufferUsage usage, const gfxVertexBufferLayoutImpl& layout)
{
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

    layout.Apply();
}

void gfxVertexBufferImplGL::Destroy()
{
    glDeleteBuffers(1, &m_ID);
    m_ID = 0;
    m_Capacity = 0;
}

epiBool gfxVertexBufferImplGL::GetIsCreated() const
{
    return m_ID != 0;
}

epiU32 gfxVertexBufferImplGL::GetID() const
{
    return m_ID;
}

epiSize_t gfxVertexBufferImplGL::GetCapacity() const
{
    return m_Capacity;
}

void gfxVertexBufferImplGL::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void gfxVertexBufferImplGL::UnBind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

epiByte* gfxVertexBufferImplGL::Map(gfxVertexBufferMapAccess access)
{
    GLenum glAccess;
    switch (access)
    {
    case gfxVertexBufferMapAccess::Read: glAccess = GL_READ_ONLY; break;
    case gfxVertexBufferMapAccess::Write: glAccess = GL_WRITE_ONLY; break;
    case gfxVertexBufferMapAccess::ReadWrite: glAccess = GL_READ_WRITE; break;
    default: epiAssert(false, "Unhandled case"); return nullptr;
    }

    return reinterpret_cast<epiByte*>(glMapBuffer(GL_ARRAY_BUFFER, glAccess));
}

epiBool gfxVertexBufferImplGL::UnMap()
{
    return glUnmapBuffer(GL_ARRAY_BUFFER);
}

EPI_NAMESPACE_END()
