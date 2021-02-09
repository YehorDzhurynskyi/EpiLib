EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriver/gfxPhysicalDevice.h"
#include "EpiGraphicsDriver/gfxPhysicalDevice.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverImpl/EpiGraphicsDriverImpl.h"

EPI_NAMESPACE_BEGIN()

gfxPhysicalDevice::gfxPhysicalDevice(internalgfx::gfxPhysicalDeviceImpl* impl)
    : m_Impl{impl}
{
}

gfxPhysicalDevice::gfxPhysicalDevice(gfxPhysicalDevice&& rhs)
{
    m_Impl = rhs.m_Impl;
    rhs.m_Impl = nullptr;
}

gfxPhysicalDevice& gfxPhysicalDevice::operator=(gfxPhysicalDevice&& rhs)
{
    m_Impl = rhs.m_Impl;
    rhs.m_Impl = nullptr;

    return *this;
}

gfxPhysicalDevice::~gfxPhysicalDevice()
{
    delete m_Impl;
}

gfxDevice* gfxPhysicalDevice::AddDevice(gfxQueueType queueTypeMask, gfxPhysicalDeviceExtension extensionMask, epiBool presentSupportRequired)
{
    internalgfx::gfxDeviceImpl* impl = m_Impl->CreateDevice(queueTypeMask, extensionMask, presentSupportRequired);
    if (impl == nullptr)
    {
        return nullptr;
    }

    gfxDevice dev(impl);
    m_Devices.push_back(std::move(dev));

    return &m_Devices.back();
}

epiString gfxPhysicalDevice::GetName_Callback() const
{
    return m_Impl->GetName();
}

gfxPhysicalDeviceType gfxPhysicalDevice::GetType_Callback() const
{
    return m_Impl->GetType();
}

epiBool gfxPhysicalDevice::GetIsPresentSupported_Callback() const
{
    return m_Impl->IsPresentSupported();
}

epiBool gfxPhysicalDevice::IsFeatureSupported(gfxPhysicalDeviceFeature feature) const
{
    return m_Impl->IsFeatureSupported(feature);
}

epiBool gfxPhysicalDevice::IsQueueTypeSupported(gfxQueueType mask) const
{
    return m_Impl->IsQueueTypeSupported(mask);
}

EPI_NAMESPACE_END()
