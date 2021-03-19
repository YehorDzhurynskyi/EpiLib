#include "EpiGraphicsDriverVK/gfxTextureImplVK.h"

#include "EpiGraphicsDriverVK/gfxEnumVK.h"

#include <vulkan/vulkan.hpp>

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxTextureImplVK::gfxTextureImplVK(VkDevice device, VkImage image)
    : m_VkImage{image}
    , m_VkDevice{device}
{
}

epiBool gfxTextureImplVK::Create2D(const epiByte* initData,
                                   epiU32 width,
                                   epiU32 height,
                                   gfxFormat format,
                                   gfxTexturePixelType pixelType)
{
    VkImageViewCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    createInfo.image = m_VkImage;
    createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    createInfo.format = gfxFormatTo(format);
    createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    createInfo.subresourceRange.baseMipLevel = 0;
    createInfo.subresourceRange.levelCount = 1;
    createInfo.subresourceRange.baseArrayLayer = 0;
    createInfo.subresourceRange.layerCount = 1;

    return VK_SUCCESS == vkCreateImageView(m_VkDevice, &createInfo, nullptr, &m_VkImageView);
}

void gfxTextureImplVK::Destroy()
{
    vkDestroyImageView(m_VkDevice, m_VkImageView, nullptr);
}

} // namespace internalgfx

EPI_NAMESPACE_END()
