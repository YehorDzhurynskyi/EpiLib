#include "EpiGraphicsImplVK/gfxImageImplVK.h"

#include "EpiGraphicsImplVK/gfxErrorVK.h"
#include "EpiGraphicsImplVK/gfxEnumVK.h"

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

gfxImageImplVK::gfxImageImplVK(VkImage image)
    : m_VkImage{image}
{
}

VkImage gfxImageImplVK::GetVkImage() const
{
    return m_VkImage;
}

gfxImageImplVKOwner::gfxImageImplVKOwner(VkDevice device)
    : gfxImageImplVK{nullptr}
    , m_VkDevice{device}
{
}

epiBool gfxImageImplVKOwner::Init(const gfxImageCreateInfo& info)
{
    VkImageCreateInfo imageCreateInfo{};
    imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageCreateInfo.imageType = gfxImageTypeTo(info.GetType());
    imageCreateInfo.format = gfxFormatTo(info.GetFormat());
    imageCreateInfo.extent.width = info.GetExtent().x;
    imageCreateInfo.extent.height = info.GetExtent().y;
    imageCreateInfo.extent.depth = info.GetExtent().z;
    imageCreateInfo.mipLevels = info.GetMipLevels();
    imageCreateInfo.arrayLayers = info.GetArrayLayers();
    imageCreateInfo.samples = gfxSampleCountMaskTo(info.GetSampleCount());
    imageCreateInfo.tiling = gfxImageTilingTo(info.GetTiling());
    imageCreateInfo.usage = gfxImageUsageMaskTo(info.GetUsageMask());
    imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE; // TODO: configure
    imageCreateInfo.queueFamilyIndexCount = -1; // TBD
    imageCreateInfo.pQueueFamilyIndices = nullptr; // TBD
    imageCreateInfo.initialLayout = gfxImageLayoutTo(info.GetInitialLayout());

    if (const VkResult result = vkCreateImage(m_VkDevice, &imageCreateInfo, nullptr, &m_VkImage); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vkCreateImage!");
        return false;
    }

    return true;
}

gfxImageImplVKOwner::~gfxImageImplVKOwner()
{
    vkDestroyImage(m_VkDevice, m_VkImage, nullptr);
}

EPI_NAMESPACE_END()
