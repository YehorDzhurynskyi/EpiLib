#include "EpiGraphicsImpl/gfxPhysicalDeviceImpl.h"

EPI_NAMESPACE_BEGIN()

gfxPhysicalDevice::Impl::Impl(const gfxInstance& instance)
    : m_Instance{instance}
{
}

const gfxInstance& gfxPhysicalDevice::Impl::GetInstance() const
{
    return m_Instance;
}

const epiArray<std::shared_ptr<gfxQueueFamilyDescriptor::Impl>>& gfxPhysicalDevice::Impl::GetQueueFamilyDescriptors() const
{
    return m_QueueFamilyDescriptors;
}

EPI_NAMESPACE_END()
