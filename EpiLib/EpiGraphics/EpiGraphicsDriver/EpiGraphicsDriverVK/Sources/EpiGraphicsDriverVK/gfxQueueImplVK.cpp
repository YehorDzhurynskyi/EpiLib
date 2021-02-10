#include "EpiGraphicsDriverVK/gfxQueueImplVK.h"

#include "EpiGraphicsDriverVK/gfxDeviceImplVK.h"
#include "EpiGraphicsDriverVK/gfxQueueFamilyImplVK.h"

#include <vulkan/vulkan.hpp>

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxQueueImplVK::gfxQueueImplVK(const gfxDeviceImplVK& device, const gfxQueueFamilyImplVK& queueFamily, epiU32 queueIndex)
    : m_QueueFamily{&queueFamily}
{
    vkGetDeviceQueue(device.GetVkDevice(), m_QueueFamily->GetIndex(), queueIndex, &m_VkQueue);
}

gfxQueueImplVK::gfxQueueImplVK(gfxQueueImplVK&& rhs)
{
    m_VkQueue = rhs.m_VkQueue;
    m_QueueFamily = rhs.m_QueueFamily;

    rhs.m_VkQueue = nullptr;
    rhs.m_QueueFamily = nullptr;
}

gfxQueueImplVK& gfxQueueImplVK::operator=(gfxQueueImplVK&& rhs)
{
    m_VkQueue = rhs.m_VkQueue;
    m_QueueFamily = rhs.m_QueueFamily;

    rhs.m_VkQueue = nullptr;
    rhs.m_QueueFamily = nullptr;

    return *this;
}

epiBool gfxQueueImplVK::IsQueueTypeSupported(gfxQueueType mask) const
{
    return m_QueueFamily->IsQueueTypeSupported(mask);
}

epiBool gfxQueueImplVK::IsPresentSupported() const
{
    return m_QueueFamily->IsPresentSupported();
}

} // namespace internalgfx

EPI_NAMESPACE_END()
