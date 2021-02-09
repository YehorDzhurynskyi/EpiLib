#include "EpiGraphicsDriverVK/gfxQueueImplVK.h"

#include "EpiGraphicsDriverVK/gfxDeviceImplVK.h"
#include "EpiGraphicsDriverVK/gfxQueueFamilyImplVK.h"

#include <vulkan/vulkan.hpp>

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxQueueImplVK::gfxQueueImplVK(const gfxDeviceImplVK& device, gfxQueueType type, const gfxQueueFamilyImplVK& queueFamily, epiU32 queueIndex)
    : m_Type(type)
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

gfxQueueType gfxQueueImplVK::Type() const
{
    epiAssert(epiBitCount(m_Type) == 1);
    return m_Type;
}

} // namespace internalgfx

EPI_NAMESPACE_END()
