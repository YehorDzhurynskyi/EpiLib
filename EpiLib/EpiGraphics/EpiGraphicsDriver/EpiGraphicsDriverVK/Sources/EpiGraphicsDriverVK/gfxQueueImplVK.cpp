#include "EpiGraphicsDriverVK/gfxQueueImplVK.h"

#include "EpiGraphicsDriverVK/gfxDeviceImplVK.h"
#include "EpiGraphicsDriverVK/gfxQueueFamilyImplVK.h"

#include <vulkan/vulkan.hpp>

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxQueueImplVK::gfxQueueImplVK(const gfxDeviceImplVK& device, const gfxQueueFamilyImplVK& queueFamily, epiU32 queueIndex, epiFloat priority)
    : m_Type{queueFamily.GetQueueTypeSupportedMask()}
    , m_Priority{priority}
{
    vkGetDeviceQueue(device.GetVkDevice(), queueFamily.GetIndex(), queueIndex, &m_VkQueue);
}

gfxQueueImplVK::gfxQueueImplVK(gfxQueueImplVK&& rhs)
{
    m_VkQueue = rhs.m_VkQueue;
    m_Type = rhs.m_Type;

    rhs.m_VkQueue = nullptr;
    rhs.m_Type = static_cast<gfxQueueType>(0);
}

gfxQueueImplVK& gfxQueueImplVK::operator=(gfxQueueImplVK&& rhs)
{
    m_VkQueue = rhs.m_VkQueue;
    m_Type = rhs.m_Type;

    rhs.m_VkQueue = nullptr;
    rhs.m_Type = static_cast<gfxQueueType>(0);

    return *this;
}

gfxQueueType gfxQueueImplVK::GetType() const
{
    return m_Type;
}

epiFloat gfxQueueImplVK::GetPriority() const
{
    return m_Priority;
}

epiBool gfxQueueImplVK::IsQueueTypeSupported(gfxQueueType mask) const
{
    return (m_Type & mask) == mask;
}

VkQueue gfxQueueImplVK::GetVkQueue() const
{
    return m_VkQueue;
}

} // namespace internalgfx

EPI_NAMESPACE_END()
