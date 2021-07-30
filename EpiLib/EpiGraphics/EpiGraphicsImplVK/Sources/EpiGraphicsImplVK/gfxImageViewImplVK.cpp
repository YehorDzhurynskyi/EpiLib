#include "EpiGraphicsImplVK/gfxImageViewImplVK.h"

#include "EpiGraphicsImplVK/gfxErrorVK.h"
#include "EpiGraphicsImplVK/gfxEnumVK.h"
#include "EpiGraphicsImplVK/gfxImageImplVK.h"

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

gfxImageViewImplVK::gfxImageViewImplVK(VkDevice device)
    : m_VkDevice{device}
{
}

epiBool gfxImageViewImplVK::Init(const gfxImageViewCreateInfo& info)
{
    const gfxImageImplVK* imageVk = static_cast<const gfxImageImplVK*>(gfxImage::Impl::ExtractImpl(info.GetImage()));
    epiAssert(imageVk != nullptr);

    VkImageViewCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    createInfo.image = imageVk->GetVkImage();
    createInfo.viewType = gfxImageViewTypeTo(info.GetViewType());
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

gfxImageViewImplVK::~gfxImageViewImplVK()
{
    vkDestroyImageView(m_VkDevice, m_VkImageView, nullptr);
}

VkImageView gfxImageViewImplVK::GetVkImageView() const
{
    return m_VkImageView;
}

EPI_NAMESPACE_END()
