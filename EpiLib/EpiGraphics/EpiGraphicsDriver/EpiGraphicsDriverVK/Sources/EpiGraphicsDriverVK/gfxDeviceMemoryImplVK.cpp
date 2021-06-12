#include "EpiGraphicsDriverVK/gfxDeviceMemoryImplVK.h"

#include "EpiGraphicsDriverVK/gfxErrorVK.h"
#include "EpiGraphicsDriverVK/gfxEnumVK.h"
#include "EpiGraphicsDriverVK/gfxTextureImplVK.h"

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxDeviceMemoryImplVK::gfxDeviceMemoryImplVK(VkDevice device)
    : m_VkDevice{device}
{
}

gfxDeviceMemoryImplVK::~gfxDeviceMemoryImplVK()
{
    vkFreeMemory(m_VkDevice, m_VkDeviceMemory, nullptr);
}

epiBool gfxDeviceMemoryImplVK::Init(const gfxDeviceMemoryBufferCreateInfo& info,
                                    const gfxPhysicalDeviceImplVK& physicalDeviceImpl,
                                    const gfxBufferImplVK& bufferImpl)
{
    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(m_VkDevice, bufferImpl.GetVkBuffer(), &memRequirements);

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
        gfxLogErrorEx(result, "Failed to call vkAllocateMemory!");
        return false;
    }

    constexpr VkDeviceSize kOffset = 0;
    if (kOffset % memRequirements.alignment != 0)
    {
        epiLogError("Failed to call vkBindBufferMemory! offset=`{}` should be a multiple of required alignment=`{}`", kOffset, memRequirements.alignment);
        return false;
    }

    if (const VkResult result = vkBindBufferMemory(m_VkDevice, bufferImpl.GetVkBuffer(), m_VkDeviceMemory, kOffset); result != VK_SUCCESS)
    {
        gfxLogErrorEx(result, "Failed to call vkBindBufferMemory!");
        return false;
    }

    return true;
}

epiBool gfxDeviceMemoryImplVK::Init(const gfxDeviceMemoryImageCreateInfo& info, const gfxPhysicalDeviceImplVK& physicalDeviceImpl)
{
    // TODO: make common function for image and buffer
    const gfxTextureImplVK* imageImpl = static_cast<const gfxTextureImplVK*>(gfxTextureImpl::ExtractImpl(info.GetImage()));
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
        gfxLogErrorEx(result, "Failed to call vkAllocateMemory!");
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
        gfxLogErrorEx(result, "Failed to call vkBindBufferMemory!");
        return false;
    }

    return true;
}

epiByte* gfxDeviceMemoryImplVK::Map(epiSize_t size, epiSize_t offset)
{
    void* data;
    if (const VkResult result = vkMapMemory(m_VkDevice, m_VkDeviceMemory, offset, size, 0, &data); result != VK_SUCCESS)
    {
        gfxLogErrorEx(result, "Failed to call vkMapMemory!");
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

} // namespace internalgfx

EPI_NAMESPACE_END()
