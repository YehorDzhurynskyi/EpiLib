#include "EpiGraphicsImplVK/gfxBufferImplVK.h"

#include "EpiGraphicsImplVK/gfxErrorVK.h"
#include "EpiGraphicsImplVK/gfxEnumVK.h"

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

gfxBufferImplVK::gfxBufferImplVK(VkDevice device)
    : m_VkDevice{device}
{
}

gfxBufferImplVK::~gfxBufferImplVK()
{
    vkDestroyBuffer(m_VkDevice, m_VkBuffer, nullptr);
}

epiBool gfxBufferImplVK::Init(const gfxBufferCreateInfo& info)
{
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = info.GetCapacity();
    bufferInfo.usage = gfxBufferUsageTo(info.GetUsage());
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE; // TODO: set via gfxBufferCreateInfo

    if (const VkResult result = vkCreateBuffer(m_VkDevice, &bufferInfo, nullptr, &m_VkBuffer); result != VK_SUCCESS)
    {
        gfxLogErrorEx(result, "Failed to call vkCreateBuffer!");
        return false;
    }

    return true;
}

VkBuffer gfxBufferImplVK::GetVkBuffer() const
{
    return m_VkBuffer;
}

EPI_NAMESPACE_END()
