#include "EpiGraphicsDriverVK/gfxTextureImplVK.h"

#include "EpiGraphicsDriverVK/gfxErrorVK.h"
#include "EpiGraphicsDriverVK/gfxEnumVK.h"

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

gfxTextureImplVK::gfxTextureImplVK(VkImage image)
    : m_VkImage{image}
{
}

VkImage gfxTextureImplVK::GetVkImage() const
{
    return m_VkImage;
}

gfxTextureImplVKOwner::gfxTextureImplVKOwner(VkDevice device)
    : gfxTextureImplVK{nullptr}
    , m_VkDevice{device}
{
}

epiBool gfxTextureImplVKOwner::Init(const gfxTextureCreateInfo& info)
{
    VkImageCreateInfo imageCreateInfo{};
    imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageCreateInfo.imageType = gfxTextureTypeTo(info.GetType());
    imageCreateInfo.format = gfxFormatTo(info.GetFormat());
    imageCreateInfo.extent.width = info.GetExtent().x;
    imageCreateInfo.extent.height = info.GetExtent().y;
    imageCreateInfo.extent.depth = info.GetExtent().z;
    imageCreateInfo.mipLevels = info.GetMipLevels();
    imageCreateInfo.arrayLayers = info.GetArrayLayers();
    imageCreateInfo.samples = gfxSampleCountTo(info.GetSampleCount());
    imageCreateInfo.tiling = gfxImageTilingTo(info.GetTiling());
    imageCreateInfo.usage = gfxImageUsageTo(info.GetUsage());
    imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE; // TODO: configure
    imageCreateInfo.queueFamilyIndexCount = -1; // TBD
    imageCreateInfo.pQueueFamilyIndices = nullptr; // TBD
    imageCreateInfo.initialLayout = gfxImageLayoutTo(info.GetInitialLayout());

    if (const VkResult result = vkCreateImage(m_VkDevice, &imageCreateInfo, nullptr, &m_VkImage); result != VK_SUCCESS)
    {
        gfxLogErrorEx(result, "Failed to call vkCreateImage!");
        return false;
    }

    return true;
}

gfxTextureImplVKOwner::~gfxTextureImplVKOwner()
{
    vkDestroyImage(m_VkDevice, m_VkImage, nullptr);
}

EPI_NAMESPACE_END()
