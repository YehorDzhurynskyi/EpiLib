#include "EpiGraphicsDriverVK/gfxQueueImplVK.h"

#include "EpiGraphicsDriverVK/gfxDeviceImplVK.h"
#include "EpiGraphicsDriverVK/gfxQueueFamilyImplVK.h"

#include <vulkan/vulkan.hpp>

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxQueueImplVK::gfxQueueImplVK(const gfxDeviceImplVK& device, const gfxQueueFamilyImplVK& queueFamily, epiU32 queueIndex)
    : m_Type{queueFamily.GetQueueTypeSupported()}
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

epiBool gfxQueueImplVK::IsQueueTypeSupported(gfxQueueType mask) const
{
    return (m_Type & mask) == mask;
}

} // namespace internalgfx

EPI_NAMESPACE_END()
