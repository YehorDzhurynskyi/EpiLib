#include "EpiGraphicsDriverVK/gfxQueueImplVK.h"

#include "EpiGraphicsDriverVK/gfxErrorVK.h"
#include "EpiGraphicsDriverVK/gfxDeviceImplVK.h"
#include "EpiGraphicsDriverVK/gfxQueueFamilyImplVK.h"
#include "EpiGraphicsDriverVK/gfxCommandBufferImplVK.h"

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxQueueImplVK::gfxQueueImplVK(const gfxDeviceImplVK& device, const gfxQueueFamilyImplVK& queueFamily, epiU32 queueIndex, epiFloat priority)
    : m_Type{queueFamily.GetQueueTypeMask()}
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

epiBool gfxQueueImplVK::Submit(const gfxQueueSubmitInfo& info, const epiPtrArray<const gfxCommandBufferImpl>& commandBuffers)
{
    std::vector<VkCommandBuffer> commandBuffersVk;
    commandBuffersVk.reserve(commandBuffers.Size());

    std::transform(commandBuffers.begin(), commandBuffers.end(), std::back_inserter(commandBuffersVk), [](const gfxCommandBufferImpl* commandBuffer)
    {
        return static_cast<const gfxCommandBufferImplVK*>(commandBuffer)->GetVkCommandBuffer();
    });

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = commandBuffersVk.size();
    submitInfo.pCommandBuffers = commandBuffersVk.data();

    if (const VkResult result = vkQueueSubmit(m_VkQueue, 1, &submitInfo, VK_NULL_HANDLE); result != VK_SUCCESS)
    {
        gfxLogErrorEx(result, "Failed to call vkQueueSubmit!");
        return false;
    }

    vkQueueWaitIdle(m_VkQueue); // TODO: manage this with a parameter

    return true;
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
