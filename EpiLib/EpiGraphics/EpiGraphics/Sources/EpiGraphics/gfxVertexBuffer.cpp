EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxVertexBuffer.h"
#include "EpiGraphics/gfxVertexBuffer.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverImpl/EpiGraphicsDriverImpl.h"

EPI_NAMESPACE_BEGIN()

epiU32 gfxVertexBufferLayoutAttribute::GetIndex_Callback() const
{
    return m_Impl->GetIndex();
}

void gfxVertexBufferLayoutAttribute::SetIndex_Callback(epiU32 value)
{
    m_Impl->SetIndex(value);
}

epiSize_t gfxVertexBufferLayoutAttribute::GetSize_Callback() const
{
    return m_Impl->GetSize();
}

void gfxVertexBufferLayoutAttribute::SetSize_Callback(epiSize_t value)
{
    m_Impl->SetSize(value);
}

gfxVertexBufferLayoutAttributeType gfxVertexBufferLayoutAttribute::GetType_Callback() const
{
    return m_Impl->GetType();
}

void gfxVertexBufferLayoutAttribute::SetType_Callback(gfxVertexBufferLayoutAttributeType value)
{
    m_Impl->SetType(value);
}

epiBool gfxVertexBufferLayoutAttribute::GetNormalized_Callback() const
{
    return m_Impl->GetNormalized();
}

void gfxVertexBufferLayoutAttribute::SetNormalized_Callback(epiBool value)
{
    m_Impl->SetNormalized(value);
}

epiSize_t gfxVertexBufferLayoutAttribute::GetStride_Callback() const
{
    return m_Impl->GetStride();
}

void gfxVertexBufferLayoutAttribute::SetStride_Callback(epiSize_t value)
{
    m_Impl->SetStride(value);
}

epiSize_t gfxVertexBufferLayoutAttribute::GetOffset_Callback() const
{
    return m_Impl->GetOffset();
}

void gfxVertexBufferLayoutAttribute::SetOffset_Callback(epiSize_t value)
{
    m_Impl->SetOffset(value);
}

gfxVertexBufferLayout::gfxVertexBufferLayout(gfxVertexBufferLayout&& rhs)
{
    m_Impl = rhs.m_Impl;
    rhs.m_Impl = nullptr;
}

gfxVertexBufferLayout& gfxVertexBufferLayout::operator=(gfxVertexBufferLayout&& rhs)
{
    m_Impl = rhs.m_Impl;
    rhs.m_Impl = nullptr;

    return *this;
}

gfxVertexBufferLayout::~gfxVertexBufferLayout()
{
    delete m_Impl;
}

void gfxVertexBufferLayout::Add(gfxVertexBufferLayoutAttribute&& attr)
{
    m_Impl->Add(std::move(*attr.m_Impl));
    m_Size++;
}

void gfxVertexBufferLayout::Add(epiSize_t size, gfxVertexBufferLayoutAttributeType type, epiBool normalized, epiSize_t stride, epiSize_t offset)
{
    gfxVertexBufferLayoutAttribute attr;
    attr.SetIndex(m_Size);
    attr.SetSize(size);
    attr.SetType(type);
    attr.SetNormalized(normalized);
    attr.SetStride(stride);
    attr.SetOffset(offset);

    Add(std::move(attr));
}

gfxVertexBuffer::gfxVertexBuffer(gfxVertexBuffer&& rhs)
{
    m_Impl = rhs.m_Impl;
    rhs.m_Impl = nullptr;
}

gfxVertexBuffer& gfxVertexBuffer::operator=(gfxVertexBuffer&& rhs)
{
    m_Impl = rhs.m_Impl;
    rhs.m_Impl = nullptr;

    return *this;
}

gfxVertexBuffer::~gfxVertexBuffer()
{
    if (GetIsCreated())
    {
        Destroy();
    }

    delete m_Impl;
}

void gfxVertexBuffer::Create(const epiByte* initData, epiSize_t capacity, gfxVertexBufferUsage usage, const gfxVertexBufferLayout& layout)
{
    epiExpect(!GetIsCreated(), "Create method should be called on destroyed vertex buffer");
    epiExpect(capacity > 0, "Capacity of buffer should be greater than 0");

    m_Impl->Create(initData, capacity, usage, *layout.m_Impl);
}

void gfxVertexBuffer::Destroy()
{
    epiExpect(GetIsCreated(), "Destroy method should be called on already created vertex buffer");

    m_Impl->Destroy();
}

epiBool gfxVertexBuffer::GetIsCreated_Callback() const
{
    return m_Impl->GetIsCreated();
}

epiU32 gfxVertexBuffer::GetID_Callback() const
{
    return m_Impl->GetID();
}

epiSize_t gfxVertexBuffer::GetCapacity_Callback() const
{
    return m_Impl->GetCapacity();
}

void gfxVertexBuffer::Bind()
{
    epiExpect(GetIsCreated(), "A vertex buffer expected to be created");

    super::Bind();

    m_Impl->Bind();
}

void gfxVertexBuffer::UnBind()
{
    epiExpect(GetIsCreated(), "A vertex buffer expected to be created");

    super::UnBind();

    m_Impl->UnBind();
}

epiByte* gfxVertexBuffer::Map(gfxVertexBufferMapAccess access)
{
    epiExpect(GetIsCreated(), "A vertex buffer expected to be created");
    epiExpect(GetIsBounded(), "A vertex buffer expected to be bounded");
    epiExpect(!m_IsMapped, "A vertex buffer expected to be unmapped");

    m_IsMapped = true;

    return m_Impl->Map(access);
}

epiBool gfxVertexBuffer::UnMap()
{
    epiExpect(GetIsCreated(), "A vertex buffer expected to be created");
    epiExpect(GetIsBounded(), "A vertex buffer expected to be bounded");
    epiExpect(m_IsMapped, "A vertex buffer expected to be mapped");

    m_IsMapped = false;

    return m_Impl->UnMap();
}

EPI_NAMESPACE_END()
