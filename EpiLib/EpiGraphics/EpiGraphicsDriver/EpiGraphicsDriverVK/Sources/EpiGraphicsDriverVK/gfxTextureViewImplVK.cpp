#include "EpiGraphicsDriverVK/gfxTextureViewImplVK.h"

#include "EpiGraphicsDriverVK/gfxErrorVK.h"
#include "EpiGraphicsDriverVK/gfxEnumVK.h"
#include "EpiGraphicsDriverVK/gfxTextureImplVK.h"

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

gfxTextureViewImplVK::gfxTextureViewImplVK(VkDevice device)
    : m_VkDevice{device}
{
}

epiBool gfxTextureViewImplVK::Init(const gfxTextureViewCreateInfo& info)
{
    const gfxTextureImplVK* imageVk = static_cast<const gfxTextureImplVK*>(gfxTexture::Impl::ExtractImpl(info.GetImage()));
    epiAssert(imageVk != nullptr);

    VkImageViewCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    createInfo.image = imageVk->GetVkImage();
    createInfo.viewType = gfxTextureViewTypeTo(info.GetViewType());
    createInfo.format = gfxFormatTo(info.GetFormat());
    createInfo.components.r = gfxComponentSwizzleTo(info.GetComponentSwizzleMappingR());
    createInfo.components.g = gfxComponentSwizzleTo(info.GetComponentSwizzleMappingG());
    createInfo.components.b = gfxComponentSwizzleTo(info.GetComponentSwizzleMappingB());
    createInfo.components.a = gfxComponentSwizzleTo(info.GetComponentSwizzleMappingA());
    createInfo.subresourceRange.aspectMask = gfxImageAspectTo(info.GetSubresourceRange().GetAspectMask());
    createInfo.subresourceRange.baseMipLevel = info.GetSubresourceRange().GetBaseMipLevel();
    createInfo.subresourceRange.levelCount = info.GetSubresourceRange().GetLevelCount();
    createInfo.subresourceRange.baseArrayLayer = info.GetSubresourceRange().GetBaseArrayLayer();
    createInfo.subresourceRange.layerCount = info.GetSubresourceRange().GetLayerCount();

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

EPI_NAMESPACE_END()
