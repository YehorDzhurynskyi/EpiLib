EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxQueueFamily.h"
#include "EpiGraphicsDriverCommon/gfxQueueFamily.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxQueueFamilyDescriptor::gfxQueueFamilyDescriptor(internalgfx::gfxQueueFamilyDescriptorImpl* impl)
    : m_Impl{impl}
{
}

gfxQueueFamilyDescriptor::gfxQueueFamilyDescriptor(gfxQueueFamilyDescriptor&& rhs)
{
    if (this != &rhs)
    {
        m_Impl = rhs.m_Impl;
        rhs.m_Impl = nullptr;
    }
}

gfxQueueFamilyDescriptor& gfxQueueFamilyDescriptor::operator=(gfxQueueFamilyDescriptor&& rhs)
{
    if (this != &rhs)
    {
        m_Impl = rhs.m_Impl;
        rhs.m_Impl = nullptr;
    }

    return *this;
}

gfxQueueFamilyDescriptor::~gfxQueueFamilyDescriptor()
{
    delete m_Impl;
}

epiBool gfxQueueFamilyDescriptor::IsQueueTypeSupported(gfxQueueType mask) const
{
    return m_Impl->IsQueueTypeSupported(mask);
}

gfxQueueType gfxQueueFamilyDescriptor::GetQueueTypeSupportedMask_Callback() const
{
    return m_Impl->GetQueueTypeSupportedMask();
}

epiSize_t gfxQueueFamilyDescriptor::GetQueueCount_Callback() const
{
    return m_Impl->GetQueueCount();
}

gfxQueueFamily::gfxQueueFamily(internalgfx::gfxQueueFamilyImpl* impl)
    : m_Impl{impl}
{
}

gfxQueueFamily::gfxQueueFamily(gfxQueueFamily&& rhs)
{
    if (this != &rhs)
    {
        m_Impl = rhs.m_Impl;
        rhs.m_Impl = nullptr;
    }
}

gfxQueueFamily& gfxQueueFamily::operator=(gfxQueueFamily&& rhs)
{
    if (this != &rhs)
    {
        m_Impl = rhs.m_Impl;
        rhs.m_Impl = nullptr;
    }

    return *this;
}

gfxQueueFamily::~gfxQueueFamily()
{
    delete m_Impl;
}

EPI_NAMESPACE_END()
