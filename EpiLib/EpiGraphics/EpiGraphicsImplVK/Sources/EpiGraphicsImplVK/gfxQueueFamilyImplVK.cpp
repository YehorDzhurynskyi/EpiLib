#include "EpiGraphicsImplVK/gfxQueueFamilyImplVK.h"

#include "EpiGraphicsImplVK/gfxDeviceImplVK.h"
#include "EpiGraphicsImplVK/gfxQueueImplVK.h"

EPI_NAMESPACE_BEGIN()

gfxQueueFamilyDescriptorImplVK::gfxQueueFamilyDescriptorImplVK(epiU32 queueFamilyIndex, epiU32 queueCount, gfxQueueType supportedQueueTypes)
    : m_Index{queueFamilyIndex}
    , m_QueueCount{queueCount}
    , m_QueueTypeSupportedMask{supportedQueueTypes}
{
}

epiBool gfxQueueFamilyDescriptorImplVK::IsQueueTypeSupported(gfxQueueType mask) const
{
    return (m_QueueTypeSupportedMask & mask) == mask;
}

gfxQueueType gfxQueueFamilyDescriptorImplVK::GetQueueTypeSupportedMask() const
{
    return m_QueueTypeSupportedMask;
}

epiU32 gfxQueueFamilyDescriptorImplVK::GetQueueCount() const
{
    return m_QueueCount;
}

epiU32 gfxQueueFamilyDescriptorImplVK::GetIndex() const
{
    return m_Index;
}

gfxQueueFamilyImplVK::gfxQueueFamilyImplVK(const gfxQueueFamilyDescriptorImplVK& queueFamilyDesc)
    : gfxQueueFamily::Impl{queueFamilyDesc}
    , m_Index{queueFamilyDesc.GetIndex()}
{
}

void gfxQueueFamilyImplVK::Init(const gfxDevice::Impl& device, const gfxQueueDescriptor& queueDesc)
{
    const gfxDeviceImplVK& deviceVk = static_cast<const gfxDeviceImplVK&>(device);

    for (epiU32 i = 0; i < queueDesc.GetQueueCount(); ++i)
    {
        const epiFloat priority = queueDesc.GetPriorities()[i];
        std::shared_ptr<gfxQueue::Impl> queue = std::make_shared<gfxQueueImplVK>(deviceVk, *this, i, priority);

        m_Queues.push_back(std::move(queue));
    }
}

epiU32 gfxQueueFamilyImplVK::GetIndex() const
{
    return m_Index;
}

EPI_NAMESPACE_END()
