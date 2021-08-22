#include "EpiGraphicsImpl/gfxDeviceImpl.h"

EPI_NAMESPACE_BEGIN()

gfxDevice::Impl::Impl(const gfxPhysicalDevice& physicalDevice)
    : m_PhysicalDevice{physicalDevice}
{
}

const gfxPhysicalDevice& gfxDevice::Impl::GetPhysicalDevice() const
{
    return m_PhysicalDevice;
}

const epiArray<std::shared_ptr<gfxQueueFamily::Impl>>& gfxDevice::Impl::GetQueueFamilies() const
{
    return m_QueueFamilies;
}

EPI_NAMESPACE_END()
