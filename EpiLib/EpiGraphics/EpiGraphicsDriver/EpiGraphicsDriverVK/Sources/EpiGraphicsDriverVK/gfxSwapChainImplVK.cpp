#include "EpiGraphicsDriverVK/gfxSwapChainImplVK.h"

#include "EpiGraphicsDriverVK/gfxDriverImplVK.h"
#include "EpiGraphicsDriverVK/gfxTextureImplVK.h"
#include "EpiGraphicsDriverVK/gfxSurfaceImplVK.h"
#include "EpiGraphicsDriverVK/gfxEnumVK.h"

#include <vulkan/vulkan.hpp>

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxSwapChainImplVK::gfxSwapChainImplVK(const gfxDeviceImplVK& device)
    : m_Device{device}
{
}

epiBool gfxSwapChainImplVK::Init(const gfxSwapChainCreateInfo& info, const gfxSurfaceImpl& surfaceImpl, const gfxRenderPassImpl& renderPassImpl)
{
    const gfxSurfaceCapabilities& capabilities = info.GetCapabilities();

    epiU32 imageCount = capabilities.GetMinImageCount() + 1;
    if (const epiU32 maxImageCount = capabilities.GetMaxImageCount(); maxImageCount > 0 && imageCount > maxImageCount)
    {
        imageCount = maxImageCount;
    }

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = static_cast<const gfxSurfaceImplVK&>(surfaceImpl).GetVkSurface();
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = gfxFormatTo(info.GetFormat().GetFormat());
    createInfo.imageColorSpace = gfxSurfaceColorSpaceTo(info.GetFormat().GetColorSpace());
    createInfo.imageExtent = VkExtent2D{info.GetExtent().x, info.GetExtent().y};
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    createInfo.queueFamilyIndexCount = 0;
    createInfo.pQueueFamilyIndices = nullptr;
    createInfo.preTransform = gfxSurfaceTransformTo(capabilities.GetCurrentTransform());
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = gfxSurfacePresentModeTo(info.GetPresentMode());
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;

    if (VK_SUCCESS != vkCreateSwapchainKHR(m_Device.GetVkDevice(), &createInfo, nullptr, &m_VkSwapChain))
    {
        return false;
    }

    vkGetSwapchainImagesKHR(m_Device.GetVkDevice(), m_VkSwapChain, &imageCount, nullptr);

    m_SwapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(m_Device.GetVkDevice(), m_VkSwapChain, &imageCount, m_SwapChainImages.data());

    for (const VkImage& image : m_SwapChainImages)
    {
        VkImageViewCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = image;
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = gfxFormatTo(info.GetFormat().GetFormat());
        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;

        std::unique_ptr<gfxTextureImplVK> textureImpl = std::make_unique<gfxTextureImplVK>(image);
        const gfxTextureImplVK* textureImplPtr = textureImpl.get();

        gfxTexture texture(textureImpl.release());

        gfxTextureViewCreateInfo textureViewCreateInfo;
        textureViewCreateInfo.SetFormat(info.GetFormat().GetFormat());
        textureViewCreateInfo.SetViewType(gfxTextureViewType::TextureView2D);
        textureViewCreateInfo.SetTexture(&texture);

        std::unique_ptr<gfxTextureViewImpl> textureViewImpl = m_Device.CreateTextureView(textureViewCreateInfo, textureImplPtr);
        m_SwapChainImageViews.push_back(std::move(textureViewImpl));
    }

    for (const auto& textureViewImpl : m_SwapChainImageViews)
    {
        gfxFrameBufferCreateInfo frameBufferCreateInfo;
        frameBufferCreateInfo.SetSize(info.GetExtent());
        frameBufferCreateInfo.SetRenderPass(const_cast<gfxRenderPass*>(info.GetRenderPass())); // TODO: add const setters to pointer (epigen)

        gfxFramebufferAttachmentImageInfo imageInfo;
        imageInfo.SetUsage(gfxImageUsage_COLOR_ATTACHMENT);
        imageInfo.SetSize(info.GetExtent());
        imageInfo.SetFormats({info.GetFormat().GetFormat()});
        imageInfo.SetLayerCount(1);

        frameBufferCreateInfo.AddAttachment(std::move(imageInfo));

        std::unique_ptr<gfxFrameBufferImpl> frameBufferImpl = m_Device.CreateFrameBuffer(frameBufferCreateInfo, &renderPassImpl);
        m_SwapChainFrameBuffers.push_back(std::move(frameBufferImpl));
    }


    return true;
}

gfxSwapChainImplVK::~gfxSwapChainImplVK()
{
    vkDestroySwapchainKHR(m_Device.GetVkDevice(), m_VkSwapChain, nullptr);
}

} // namespace internalgfx

EPI_NAMESPACE_END()
