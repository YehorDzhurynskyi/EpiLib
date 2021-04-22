#include "EpiGraphicsDriverVK/gfxQueueFamilyImplVK.h"

#include "EpiGraphicsDriverVK/gfxQueueImplVK.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

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

gfxQueueFamilyImplVK::gfxQueueFamilyImplVK(const gfxQueueFamilyDescriptorImplVK& queueFamilyDesc, const gfxQueueDescriptor& queueDesc)
    : gfxQueueFamilyImpl{queueFamilyDesc, queueDesc}
    , m_Index{queueFamilyDesc.GetIndex()}
{
}

void gfxQueueFamilyImplVK::Init(const gfxDeviceImpl& device)
{
    for (epiU32 i = 0; i < GetQueueCountEnabled(); ++i)
    {
        std::unique_ptr<gfxQueueImpl> queue = std::make_unique<gfxQueueImplVK>(device, *this, i);

        m_Queues.push_back(std::move(queue));
    }
}

epiU32 gfxQueueFamilyImplVK::GetIndex() const
{
    return m_Index;
}

} // namespace internalgfx

EPI_NAMESPACE_END()
