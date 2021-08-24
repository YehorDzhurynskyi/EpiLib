#include "EpiGraphicsImplVK/gfxDeviceMemoryImplVK.h"

#include "EpiGraphicsImplVK/gfxErrorVK.h"
#include "EpiGraphicsImplVK/gfxEnumVK.h"
#include "EpiGraphicsImplVK/gfxImageImplVK.h"
#include "EpiGraphicsImplVK/gfxPhysicalDeviceImplVK.h"
#include "EpiGraphicsImplVK/gfxBufferImplVK.h"

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

gfxDeviceMemoryImplVK::gfxDeviceMemoryImplVK(VkDevice device)
    : m_VkDevice{device}
{
}

gfxDeviceMemoryImplVK::~gfxDeviceMemoryImplVK()
{
    vkFreeMemory(m_VkDevice, m_VkDeviceMemory, nullptr);
}

epiBool gfxDeviceMemoryImplVK::Init(const gfxDeviceMemoryCreateInfo& info,
                                    const gfxPhysicalDeviceImplVK& physicalDeviceImpl)
{
    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = info.GetSize();
    allocInfo.memoryTypeIndex = std::numeric_limits<epiU32>::max();

    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(physicalDeviceImpl.GetVkPhysicalDevice(), &memProperties);

    const VkMemoryPropertyFlagBits memoryPropertyMask = gfxDeviceMemoryPropertyMaskTo(info.GetPropertyMask());
    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
    {
        if ((memProperties.memoryTypes[i].propertyFlags & memoryPropertyMask) == memoryPropertyMask)
        {
            allocInfo.memoryTypeIndex = i;
            break;
        }
    }

    if (allocInfo.memoryTypeIndex >= memProperties.memoryTypeCount)
    {
        epiLogError("Failed to find suitable memory type!");
        return false;
    }

    if (const VkResult result = vkAllocateMemory(m_VkDevice, &allocInfo, nullptr, &m_VkDeviceMemory); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vkAllocateMemory!");
        return false;
    }

    m_AllocatedSize = allocInfo.allocationSize;
    m_MemoryTypeIndex = allocInfo.memoryTypeIndex;
    m_EnabledPropertyMask = info.GetPropertyMask();

    return true;
}

epiBool gfxDeviceMemoryImplVK::IsPropertyEnabled(gfxDeviceMemoryPropertyMask mask) const
{
    return (mask & m_EnabledPropertyMask) == mask;
}

epiBool gfxDeviceMemoryImplVK::BindBuffer(const gfxBindBufferMemoryInfo& info)
{
    const std::shared_ptr<gfxBufferImplVK> bufferImpl = ImplOf<gfxBufferImplVK>(info.GetBuffer());
    epiAssert(bufferImpl != nullptr);

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(m_VkDevice, bufferImpl->GetVkBuffer(), &memRequirements);

    if (!ValidateMemoryRequirements(memRequirements.size, memRequirements.alignment, memRequirements.memoryTypeBits, info.GetOffset()))
    {
        epiLogError("Failed to bind Buffer! A memory requirements validation has failed!");
        return false;
    }

    if (const VkResult result = vkBindBufferMemory(m_VkDevice, bufferImpl->GetVkBuffer(), m_VkDeviceMemory, info.GetOffset()); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vkBindBufferMemory!");
        return false;
    }

    return true;
}

epiBool gfxDeviceMemoryImplVK::BindImage(const gfxBindImageMemoryInfo& info)
{
    const std::shared_ptr<gfxImageImplVK> imageImpl = ImplOf<gfxImageImplVK>(info.GetImage());
    epiAssert(imageImpl != nullptr);

    VkMemoryRequirements memRequirements;
    vkGetImageMemoryRequirements(m_VkDevice, imageImpl->GetVkImage(), &memRequirements);

    if (!ValidateMemoryRequirements(memRequirements.size, memRequirements.alignment, memRequirements.memoryTypeBits, info.GetOffset()))
    {
        epiLogError("Failed to bind Image! A memory requirements validation has failed!");
        return false;
    }

    if (const VkResult result = vkBindImageMemory(m_VkDevice, imageImpl->GetVkImage(), m_VkDeviceMemory, info.GetOffset()); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vkBindImageMemory!");
        return false;
    }

    return true;
}

epiByte* gfxDeviceMemoryImplVK::Map(epiSize_t size, epiSize_t offset)
{
    void* data = nullptr;
    if (const VkResult result = vkMapMemory(m_VkDevice, m_VkDeviceMemory, offset, size, 0, &data); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vkMapMemory!");
        return nullptr;
    }

    return reinterpret_cast<epiByte*>(data);
}

void gfxDeviceMemoryImplVK::Unmap()
{
    vkUnmapMemory(m_VkDevice, m_VkDeviceMemory);
}

VkDeviceMemory gfxDeviceMemoryImplVK::GetVkDeviceMemory() const
{
    return m_VkDeviceMemory;
}

epiBool gfxDeviceMemoryImplVK::ValidateMemoryRequirements(epiSize_t requiredSize,
                                                          epiSize_t requiredAlignment,
                                                          uint32_t requiredMemoryTypeBits,
                                                          epiSize_t actualOffset) const
{
    if (requiredSize > m_AllocatedSize)
    {
        epiLogError("Failed to bind Buffer! The required size=`{}` is greater than AllocatedSize=`{}`",
                    requiredSize,
                    m_AllocatedSize);
        return false;
    }

    if (actualOffset % requiredAlignment != 0)
    {
        epiLogError("Failed to bind Buffer! Offset=`{}` should be a multiple of the required alignment=`{}`",
                    actualOffset,
                    requiredAlignment);
        return false;
    }

    if (!(requiredMemoryTypeBits & (1 << m_MemoryTypeIndex)))
    {
        epiLogError("Failed to bind Buffer! Required MemoryTypeBits=`{}` doesn't match used MemoryTypeIndex=`{}`",
                    requiredMemoryTypeBits,
                    m_MemoryTypeIndex);
        return false;
    }

    return true;
}

EPI_NAMESPACE_END()
