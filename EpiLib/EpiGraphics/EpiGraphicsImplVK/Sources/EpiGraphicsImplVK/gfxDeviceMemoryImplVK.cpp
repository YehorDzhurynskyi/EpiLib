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

epiBool gfxDeviceMemoryImplVK::Init(const gfxDeviceMemoryBufferCreateInfo& info,
                                    const gfxPhysicalDeviceImplVK& physicalDeviceImpl)
{
    if (!info.GetBuffer().HasImpl())
    {
        epiLogError("Failed to allocate memory for the Buffer! The provided Buffer has no implementation!");
        return false;
    }

    const std::shared_ptr<gfxBufferImplVK> bufferImpl = ImplOf<gfxBufferImplVK>(info.GetBuffer());
    epiAssert(bufferImpl != nullptr);

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(m_VkDevice, bufferImpl->GetVkBuffer(), &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = std::numeric_limits<epiU32>::max();

    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(physicalDeviceImpl.GetVkPhysicalDevice(), &memProperties);

    const VkMemoryPropertyFlagBits memoryPropertyMask = gfxDeviceMemoryPropertyTo(info.GetPropertyMask());
    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
    {
        if ((memRequirements.memoryTypeBits & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & memoryPropertyMask) == memoryPropertyMask)
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

    constexpr VkDeviceSize kOffset = 0;
    if (kOffset % memRequirements.alignment != 0)
    {
        epiLogError("Failed to call vkBindBufferMemory! offset=`{}` should be a multiple of required alignment=`{}`", kOffset, memRequirements.alignment);
        return false;
    }

    if (const VkResult result = vkBindBufferMemory(m_VkDevice, bufferImpl->GetVkBuffer(), m_VkDeviceMemory, kOffset); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vkBindBufferMemory!");
        return false;
    }

    return true;
}

epiBool gfxDeviceMemoryImplVK::Init(const gfxDeviceMemoryImageCreateInfo& info, const gfxPhysicalDeviceImplVK& physicalDeviceImpl)
{
    // TODO: make common function for image and buffer
    const std::shared_ptr<gfxImageImplVK> imageImpl = ImplOf<gfxImageImplVK>(info.GetImage());
    epiAssert(imageImpl != nullptr);

    VkMemoryRequirements memRequirements;
    vkGetImageMemoryRequirements(m_VkDevice, imageImpl->GetVkImage(), &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = std::numeric_limits<epiU32>::max();

    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(physicalDeviceImpl.GetVkPhysicalDevice(), &memProperties);

    const VkMemoryPropertyFlagBits memoryPropertyMask = gfxDeviceMemoryPropertyTo(info.GetPropertyMask());
    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
    {
        if ((memRequirements.memoryTypeBits & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & memoryPropertyMask) == memoryPropertyMask)
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

    constexpr VkDeviceSize kOffset = 0;
    if (kOffset % memRequirements.alignment != 0)
    {
        epiLogError("Failed to call vkBindBufferMemory! offset=`{}` should be a multiple of required alignment=`{}`", kOffset, memRequirements.alignment);
        return false;
    }

    if (const VkResult result = vkBindImageMemory(m_VkDevice, imageImpl->GetVkImage(), m_VkDeviceMemory, kOffset); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vkBindBufferMemory!");
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

EPI_NAMESPACE_END()
