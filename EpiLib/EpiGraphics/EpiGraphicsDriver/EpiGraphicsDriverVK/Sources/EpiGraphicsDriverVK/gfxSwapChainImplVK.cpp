#include "EpiGraphicsDriverVK/gfxSwapChainImplVK.h"

#include "EpiGraphicsDriverVK/gfxErrorVK.h"
#include "EpiGraphicsDriverVK/gfxEnumVK.h"
#include "EpiGraphicsDriverVK/gfxDriverImplVK.h"
#include "EpiGraphicsDriverVK/gfxDeviceImplVK.h"
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

gfxSwapChainImplVK::gfxSwapChainImplVK(const gfxDeviceImplVK& device)
    : m_Device{device}
{
}

gfxSwapChainImplVK::~gfxSwapChainImplVK()
{
    Reset();
}

epiBool gfxSwapChainImplVK::Init(const gfxSwapChainCreateInfo& info)
{
    const gfxSurfaceImplVK* surfaceImpl = static_cast<const gfxSurfaceImplVK*>(gfxSurface::Impl::ExtractImpl(info.GetSurface()));
    epiAssert(surfaceImpl != nullptr);

    std::vector<epiU32> queueFamilyIndices;
    queueFamilyIndices.reserve(info.GetQueueFamilies().Size());

    std::transform(info.GetQueueFamilies().begin(),
                   info.GetQueueFamilies().end(),
                   std::back_inserter(queueFamilyIndices),
                   [](const gfxQueueFamily& queueFamily)
    {
        const gfxQueueFamilyImplVK* queueFamilyImpl = static_cast<const gfxQueueFamilyImplVK*>(gfxQueueFamily::Impl::ExtractImpl(queueFamily));
        epiAssert(queueFamilyImpl != nullptr);

        return queueFamilyImpl->GetIndex();
    });

    epiAssert(info.GetImageSharingMode() == gfxSharingMode::Exclusive || !info.GetQueueFamilies().IsEmpty());

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = surfaceImpl->GetVkSurface();
    createInfo.minImageCount = info.GetImageMinCount();
    createInfo.imageFormat = gfxFormatTo(info.GetImageFormat());
    createInfo.imageColorSpace = gfxSurfaceColorSpaceTo(info.GetImageColorSpace());
    createInfo.imageExtent = VkExtent2D{info.GetImageExtent().x, info.GetImageExtent().y};
    createInfo.imageArrayLayers = info.GetImageArrayLayers();
    createInfo.imageUsage = gfxImageUsageTo(info.GetImageUsageMask());
    createInfo.imageSharingMode = gfxSharingModeTo(info.GetImageSharingMode());
    createInfo.queueFamilyIndexCount = queueFamilyIndices.size();
    createInfo.pQueueFamilyIndices = queueFamilyIndices.data();
    createInfo.preTransform = gfxSurfaceTransformMaskTo(info.GetSurfacePreTransformMask());
    createInfo.compositeAlpha = gfxCompositeAlphaMaskTo(info.GetCompositeAlphaMask());
    createInfo.presentMode = gfxSurfacePresentModeTo(info.GetPresentMode());
    createInfo.clipped = info.GetIsClipped();
    createInfo.oldSwapchain = VK_NULL_HANDLE;

#if 0 // TODO: set
    if (info.GetOldSwapChain().HasImpl())
    {
        const gfxSwapChainImplVK* oldSwapChainImpl = static_cast<const gfxSwapChainImplVK*>(gfxSwapChainImpl::ExtractImpl(info.GetOldSwapChain()));
        epiAssert(oldSwapChainImpl != nullptr);

        createInfo.oldSwapchain = oldSwapChainImpl->GetVkSwapChain();
    }
#endif

    if (const VkResult result = vkCreateSwapchainKHR(m_Device.GetVkDevice(), &createInfo, nullptr, &m_VkSwapChain); result != VK_SUCCESS)
    {
        gfxLogErrorEx(result, "Failed to call vkCreateSwapchainKHR!");
        return false;
    }

    epiU32 imageCount = 0;
    if (const VkResult result = vkGetSwapchainImagesKHR(m_Device.GetVkDevice(), m_VkSwapChain, &imageCount, nullptr); result != VK_SUCCESS)
    {
        gfxLogErrorEx(result, "Failed to call vkGetSwapchainImagesKHR!");
        return false;
    }

    std::vector<VkImage> swapChainImages(imageCount);
    if (const VkResult result = vkGetSwapchainImagesKHR(m_Device.GetVkDevice(), m_VkSwapChain, &imageCount, swapChainImages.data()); result != VK_SUCCESS)
    {
        gfxLogErrorEx(result, "Failed to call vkGetSwapchainImagesKHR!");
        return false;
    }

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
        textureViewCreateInfo.SetFormat(info.GetImageFormat());
        textureViewCreateInfo.SetSubresourceRange(subresourceRange);

        std::shared_ptr<gfxTextureView::Impl> textureViewImpl = m_Device.CreateTextureView(textureViewCreateInfo);
        m_ImageViews.push_back(std::move(textureViewImpl));
    }

    m_Extent = info.GetImageExtent();

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

epiBool gfxSwapChainImplVK::Recreate(const gfxSwapChainCreateInfo& info)
{
    if (!Reset())
    {
        epiLogError("SwapChain Recreation has been failed since Reset failed!");
        return false;
    }

    return Init(info);
}

epiS32 gfxSwapChainImplVK::AcquireNextImage(const gfxSemaphore* signalSemaphore, const gfxFence* signalFence, epiU64 timeout)
{
    VkSemaphore signalSemaphoreVk = VK_NULL_HANDLE;
    VkFence signalFenceVk = VK_NULL_HANDLE;

    if (signalSemaphore != nullptr)
    {
        const gfxSemaphoreImplVK* signalSemaphoreImpl = static_cast<const gfxSemaphoreImplVK*>(gfxSemaphore::Impl::ExtractImpl(*signalSemaphore));
        epiAssert(signalSemaphoreImpl != nullptr);

        signalSemaphoreVk = signalSemaphoreImpl->GetVkSemaphore();
    }

    if (signalFence != nullptr)
    {
        const gfxFenceImplVK* signalFenceImpl = static_cast<const gfxFenceImplVK*>(gfxFence::Impl::ExtractImpl(*signalFence));
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

EPI_NAMESPACE_END()
