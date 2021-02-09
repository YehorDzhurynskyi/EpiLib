#include "EpiGraphicsDriverVK/gfxQueueFamilyImplVK.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxQueueFamilyImplVK::gfxQueueFamilyImplVK(epiU32 queueFamilyIndex, epiU32 queueCount, gfxQueueType supportedQueueTypes, epiBool isPresentSupported)
    : m_Index{queueFamilyIndex}
    , m_QueueCount{queueCount}
    , m_QueueTypeSupported{supportedQueueTypes}
    , m_IsPresentSupported{isPresentSupported}
{
}

epiBool gfxQueueFamilyImplVK::IsQueueTypeSupported(gfxQueueType mask) const
{
    return (m_QueueTypeSupported & mask) == mask;
}

epiU32 gfxQueueFamilyImplVK::QueueTypeSupportedCount() const
{
    return epiBitCount(m_QueueTypeSupported);
}

epiBool gfxQueueFamilyImplVK::IsPresentSupported() const
{
    return m_IsPresentSupported;
}

epiU32 gfxQueueFamilyImplVK::GetIndex() const
{
    return m_Index;
}

} // namespace internalgfx

EPI_NAMESPACE_END()
