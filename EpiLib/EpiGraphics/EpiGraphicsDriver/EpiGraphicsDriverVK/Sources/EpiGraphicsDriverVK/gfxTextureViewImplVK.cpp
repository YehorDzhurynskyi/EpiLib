#include "EpiGraphicsDriverVK/gfxTextureViewImplVK.h"

#include "EpiGraphicsDriverVK/gfxErrorVK.h"
#include "EpiGraphicsDriverVK/gfxEnumVK.h"
#include "EpiGraphicsDriverVK/gfxTextureImplVK.h"

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxTextureViewImplVK::gfxTextureViewImplVK(VkDevice device)
    : m_VkDevice{device}
{
}

epiBool gfxTextureViewImplVK::Init(const gfxTextureViewCreateInfo& info, const gfxTextureImpl& textureImpl)
{
    VkImageViewCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    createInfo.image = static_cast<const gfxTextureImplVK&>(textureImpl).GetVkImage();
    createInfo.viewType = gfxTextureViewTypeTo(info.GetViewType());
    createInfo.format = gfxFormatTo(info.GetFormat());
    createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    createInfo.subresourceRange.baseMipLevel = 0;
    createInfo.subresourceRange.levelCount = 1;
    createInfo.subresourceRange.baseArrayLayer = 0;
    createInfo.subresourceRange.layerCount = 1;

    if (const VkResult result = vkCreateImageView(m_VkDevice, &createInfo, nullptr, &m_VkImageView); result != VK_SUCCESS)
    {
        gfxLogErrorEx(result, "Failed to call vkCreateImageView!");
        return false;
    }

    return true;
}

gfxTextureViewImplVK::~gfxTextureViewImplVK()
{
    vkDestroyImageView(m_VkDevice, m_VkImageView, nullptr);
}

VkImageView gfxTextureViewImplVK::GetVkImageView() const
{
    return m_VkImageView;
}

} // namespace internalgfx

EPI_NAMESPACE_END()
