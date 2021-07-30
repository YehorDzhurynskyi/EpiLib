#include "EpiGraphicsImplVK/Synchronization/gfxFenceImplVK.h"

#include "EpiGraphicsImplVK/gfxErrorVK.h"
#include "EpiGraphicsImplVK/gfxEnumVK.h"

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

gfxFenceImplVK::gfxFenceImplVK(VkDevice device)
    : m_VkDevice{device}
{
}

gfxFenceImplVK::~gfxFenceImplVK()
{
    vkDestroyFence(m_VkDevice, m_VkFence, nullptr);
}

epiBool gfxFenceImplVK::Init(const gfxFenceCreateInfo& info)
{
    VkFenceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    createInfo.flags = gfxFenceCreateMaskTo(info.GetCreateMask());

    if (const VkResult result = vkCreateFence(m_VkDevice, &createInfo, nullptr, &m_VkFence); result != VK_SUCCESS)
    {
        gfxLogErrorEx(result, "Failed to call vkCreateFence!");
        return false;
    }

    return true;
}

epiBool gfxFenceImplVK::Reset()
{
    if (const VkResult result = vkResetFences(m_VkDevice, 1, &m_VkFence); result != VK_SUCCESS)
    {
        gfxLogErrorEx(result, "Failed to call vkResetFences!");
        return false;
    }

    return true;
}

epiBool gfxFenceImplVK::Wait(epiU64 timeout)
{
    if (const VkResult result = vkWaitForFences(m_VkDevice, 1, &m_VkFence, VK_TRUE, timeout); result != VK_SUCCESS)
    {
        gfxLogErrorEx(result, "Failed to call vkWaitForFences!");
        return false;
    }

    return true;
}

VkFence gfxFenceImplVK::GetVkFence() const
{
    return m_VkFence;
}

EPI_NAMESPACE_END()
