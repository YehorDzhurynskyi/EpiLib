#include "EpiGraphicsDriverVK/gfxSwapChainImplVK.h"

#include "EpiGraphicsDriverVK/gfxErrorVK.h"
#include "EpiGraphicsDriverVK/gfxEnumVK.h"
#include "EpiGraphicsDriverVK/gfxDriverImplVK.h"
#include "EpiGraphicsDriverVK/gfxTextureImplVK.h"
#include "EpiGraphicsDriverVK/gfxSurfaceImplVK.h"
#include "EpiGraphicsDriverVK/gfxCommandPoolImplVK.h"
#include "EpiGraphicsDriverVK/gfxCommandBufferImplVK.h"
#include "EpiGraphicsDriverVK/gfxRenderPassImplVK.h"
#include "EpiGraphicsDriverVK/gfxFrameBufferImplVK.h"
#include "EpiGraphicsDriverVK/gfxPipelineImplVK.h"
#include "EpiGraphicsDriverVK/gfxBufferImplVK.h"
#include "EpiGraphicsDriverVK/Synchronization/gfxSemaphoreImplVK.h"
#include "EpiGraphicsDriverVK/Synchronization/gfxFenceImplVK.h"

#include "EpiGraphicsDriverCommon/gfxTextureView.h"

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxSwapChainImplVK::gfxSwapChainImplVK(const gfxDeviceImplVK& device)
    : m_Device{device}
{
}

gfxSwapChainImplVK::~gfxSwapChainImplVK()
{
    Reset();
}

epiBool gfxSwapChainImplVK::Init(const gfxSwapChainCreateInfo& info,
                                 const gfxSurfaceImpl& surfaceImpl,
                                 const gfxQueueFamilyImpl& queueFamilyImpl,
                                 const gfxRenderPassImpl& renderPassImpl)
{
    m_Extent = info.GetExtent();

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

    if (const VkResult result = vkCreateSwapchainKHR(m_Device.GetVkDevice(), &createInfo, nullptr, &m_VkSwapChain); result != VK_SUCCESS)
    {
        gfxLogErrorEx(result, "Failed to call vkCreateSwapchainKHR!");
        return false;
    }

    vkGetSwapchainImagesKHR(m_Device.GetVkDevice(), m_VkSwapChain, &imageCount, nullptr);

    std::vector<VkImage> swapChainImages(imageCount);
    vkGetSwapchainImagesKHR(m_Device.GetVkDevice(), m_VkSwapChain, &imageCount, swapChainImages.data());

    for (const VkImage& image : swapChainImages)
    {
        std::shared_ptr<gfxTextureImplVK> textureImpl = std::make_shared<gfxTextureImplVK>(image);
        gfxTexture texture(textureImpl);

        gfxImageSubresourceRange subresourceRange{};
        subresourceRange.SetAspectMask(gfxImageAspect_Color);
        subresourceRange.SetBaseMipLevel(0);
        subresourceRange.SetLevelCount(1);
        subresourceRange.SetBaseArrayLayer(0);
        subresourceRange.SetLayerCount(1);

        gfxTextureViewCreateInfo textureViewCreateInfo;
        textureViewCreateInfo.SetImage(texture);
        textureViewCreateInfo.SetViewType(gfxTextureViewType::TextureView2D);
        textureViewCreateInfo.SetFormat(info.GetFormat().GetFormat());
        textureViewCreateInfo.SetSubresourceRange(subresourceRange);

        std::shared_ptr<gfxTextureViewImpl> textureViewImpl = m_Device.CreateTextureView(textureViewCreateInfo, *textureImpl);
        m_ImageViews.push_back(std::move(textureViewImpl));
    }

    return true;
}

epiBool gfxSwapChainImplVK::Reset()
{
    const VkResult result = vkDeviceWaitIdle(m_Device.GetVkDevice());
    if (result != VK_SUCCESS)
    {
        gfxLogErrorEx(result, "Failed to call vkDeviceWaitIdle!");
        return false;
    }

    m_ImageViews.Clear();

    vkDestroySwapchainKHR(m_Device.GetVkDevice(), m_VkSwapChain, nullptr);

    return true;
}

epiBool gfxSwapChainImplVK::Recreate(const gfxSwapChainCreateInfo& info,
                                     const gfxSurfaceImpl& surfaceImpl,
                                     const gfxQueueFamilyImpl& queueFamilyImpl,
                                     const gfxRenderPassImpl& renderPassImpl)
{
    if (!Reset())
    {
        epiLogError("SwapChain Recreation has been failed since Reset failed!");
        return false;
    }

    return Init(info, surfaceImpl, queueFamilyImpl, renderPassImpl);
}

epiS32 gfxSwapChainImplVK::AcquireNextImage(const gfxSemaphore* signalSemaphore, const gfxFence* signalFence, epiU64 timeout)
{
    VkSemaphore signalSemaphoreVk = VK_NULL_HANDLE;
    VkFence signalFenceVk = VK_NULL_HANDLE;

    if (signalSemaphore != nullptr)
    {
        const gfxSemaphoreImplVK* signalSemaphoreImpl = static_cast<const gfxSemaphoreImplVK*>(gfxSemaphoreImpl::ExtractImpl(*signalSemaphore));
        epiAssert(signalSemaphoreImpl != nullptr);

        signalSemaphoreVk = signalSemaphoreImpl->GetVkSemaphore();
    }

    if (signalFence != nullptr)
    {
        const gfxFenceImplVK* signalFenceImpl = static_cast<const gfxFenceImplVK*>(gfxFenceImpl::ExtractImpl(*signalFence));
        epiAssert(signalFenceImpl != nullptr);

        signalFenceVk = signalFenceImpl->GetVkFence();
    }

    epiU32 imageIndex = 0;
    if (const VkResult result = vkAcquireNextImageKHR(m_Device.GetVkDevice(),
                                                      m_VkSwapChain,
                                                      timeout,
                                                      signalSemaphoreVk,
                                                      signalFenceVk,
                                                      &imageIndex); result != VK_SUCCESS)
    {
        gfxLogErrorEx(result, "Failed to call vkAcquireNextImageKHR!");
        if (result != VK_SUBOPTIMAL_KHR)
        {
            return -1;
        }
    }

    return imageIndex;
}

epiSize2u gfxSwapChainImplVK::GetExtent() const
{
    return m_Extent;
}

VkSwapchainKHR gfxSwapChainImplVK::GetVkSwapChain() const
{
    return m_VkSwapChain;
}

} // namespace internalgfx

EPI_NAMESPACE_END()
