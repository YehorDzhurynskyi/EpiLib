EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxQueueFamily.h"
#include "EpiGraphicsDriverCommon/gfxQueueFamily.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxQueueFamily::gfxQueueFamily(internalgfx::gfxQueueFamilyImpl* impl)
    : m_Impl{impl}
{
}

gfxQueueFamily::gfxQueueFamily(gfxQueueFamily&& rhs)
{
    m_Impl = rhs.m_Impl;

    rhs.m_Impl = nullptr;
}

gfxQueueFamily& gfxQueueFamily::operator=(gfxQueueFamily&& rhs)
{
    m_Impl = rhs.m_Impl;

    rhs.m_Impl = nullptr;

    return *this;
}

gfxQueueFamily::~gfxQueueFamily()
{
    delete m_Impl;
}

epiBool gfxQueueFamily::HasImpl() const
{
    return m_Impl != nullptr;
}

gfxQueueType gfxQueueFamily::GetQueueTypeSupported_Callback() const
{
    return m_Impl->GetQueueTypeSupported();
}

epiSize_t gfxQueueFamily::GetQueueCount_Callback() const
{
    return m_Impl->GetQueueCount();
}

EPI_NAMESPACE_END()
