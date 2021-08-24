#include "EpiGraphicsImplVK/gfxBufferImplVK.h"

#include "EpiGraphicsImplVK/gfxErrorVK.h"
#include "EpiGraphicsImplVK/gfxEnumVK.h"
#include "EpiGraphicsImplVK/gfxDeviceImplVK.h"
#include "EpiGraphicsImplVK/gfxQueueFamilyImplVK.h"

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

gfxBufferImplVK::gfxBufferImplVK(const gfxDevice& device)
    : gfxBuffer::Impl{device}
{
}

gfxBufferImplVK::~gfxBufferImplVK()
{
    const std::shared_ptr<gfxDeviceImplVK> deviceImpl = ImplOf<gfxDeviceImplVK>(m_Device);

    vkDestroyBuffer(deviceImpl->GetVkDevice(), m_VkBuffer, nullptr);
}

epiBool gfxBufferImplVK::Init(const gfxBufferCreateInfo& info)
{
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.flags = gfxBufferCreateMaskTo(info.GetCreateMask());
    bufferInfo.size = info.GetSize();
    bufferInfo.usage = gfxBufferUsageMaskTo(info.GetUsageMask());
    bufferInfo.sharingMode = gfxSharingModeTo(info.GetSharingMode());

    std::vector<epiU32> queueFamilyIndices;
    if (info.GetSharingMode() == gfxSharingMode::Concurrent)
    {
        queueFamilyIndices.reserve(info.GetQueueFamilies().Size());

        std::transform(info.GetQueueFamilies().begin(),
                       info.GetQueueFamilies().end(),
                       std::back_inserter(queueFamilyIndices),
                       [](const gfxQueueFamily& family)
        {
            const std::shared_ptr<gfxQueueFamilyImplVK> familyImpl = ImplOf<gfxQueueFamilyImplVK>(family);
            return familyImpl->GetIndex();
        });

        bufferInfo.queueFamilyIndexCount = queueFamilyIndices.size();
        bufferInfo.pQueueFamilyIndices = queueFamilyIndices.data();
    }

    const std::shared_ptr<gfxDeviceImplVK> deviceImpl = ImplOf<gfxDeviceImplVK>(m_Device);
    if (const VkResult result = vkCreateBuffer(deviceImpl->GetVkDevice(), &bufferInfo, nullptr, &m_VkBuffer); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vkCreateBuffer!");
        return false;
    }

    return true;
}

epiBool gfxBufferImplVK::Init(VkBuffer buffer)
{
    m_VkBuffer = buffer;

    return true;
}

VkBuffer gfxBufferImplVK::GetVkBuffer() const
{
    return m_VkBuffer;
}

EPI_NAMESPACE_END()
