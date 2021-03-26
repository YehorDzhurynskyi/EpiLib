EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxVertexBuffer.h"
#include "EpiGraphicsDriverCommon/gfxVertexBuffer.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

epiU32 gfxVertexBufferLayoutAttribute::GetLocation_Callback() const
{
    return m_Impl->GetLocation();
}

void gfxVertexBufferLayoutAttribute::SetLocation_Callback(epiU32 value)
{
    m_Impl->SetLocation(value);
}

gfxFormat gfxVertexBufferLayoutAttribute::GetFormat_Callback() const
{
    return m_Impl->GetFormat();
}

void gfxVertexBufferLayoutAttribute::SetFormat_Callback(gfxFormat value)
{
    m_Impl->SetFormat(value);
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

void gfxVertexBufferLayout::Add(epiU32 location, gfxFormat format, epiSize_t offset)
{
    gfxVertexBufferLayoutAttribute attr;
    attr.SetLocation(location);
    attr.SetFormat(format);
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
// TODO: implement       Destroy();
    }

    delete m_Impl;
}

#if 0
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

epiSize_t gfxVertexBuffer::GetCapacity_Callback() const
{
    return m_Impl->GetCapacity();
}

epiByte* gfxVertexBuffer::Map(gfxVertexBufferMapAccess access)
{
    epiExpect(GetIsCreated(), "A vertex buffer expected to be created");
    epiExpect(!m_IsMapped, "A vertex buffer expected to be unmapped");

    m_IsMapped = true;

    return m_Impl->Map(access);
}

epiBool gfxVertexBuffer::UnMap()
{
    epiExpect(GetIsCreated(), "A vertex buffer expected to be created");
    epiExpect(m_IsMapped, "A vertex buffer expected to be mapped");

    m_IsMapped = false;

    return m_Impl->UnMap();
}
#endif

EPI_NAMESPACE_END()
