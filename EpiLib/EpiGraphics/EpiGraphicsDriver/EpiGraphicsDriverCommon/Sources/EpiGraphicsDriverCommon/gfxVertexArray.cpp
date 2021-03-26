EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxVertexArray.h"
#include "EpiGraphicsDriverCommon/gfxVertexArray.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxVertexArray::gfxVertexArray(internalgfx::gfxVertexArrayImpl* impl)
    : m_Impl{impl}
{
}

gfxVertexArray::gfxVertexArray(gfxVertexArray&& rhs)
{
    m_Impl = rhs.m_Impl;

    rhs.m_Impl = nullptr;
}

gfxVertexArray& gfxVertexArray::operator=(gfxVertexArray&& rhs)
{
    m_Impl = rhs.m_Impl;

    rhs.m_Impl = nullptr;

    return *this;
}

gfxVertexArray::~gfxVertexArray()
{
    delete m_Impl;
}

epiBool gfxVertexArray::GetIsCreated_Callback() const
{
    return m_Impl->GetIsCreated();
}

EPI_NAMESPACE_END()
