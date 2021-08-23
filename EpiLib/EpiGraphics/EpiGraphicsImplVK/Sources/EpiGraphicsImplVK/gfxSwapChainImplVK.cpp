#include "EpiGraphicsImplVK/gfxSwapChainImplVK.h"

#include "EpiGraphicsImplVK/gfxErrorVK.h"
#include "EpiGraphicsImplVK/gfxEnumVK.h"
#include "EpiGraphicsImplVK/gfxDeviceImplVK.h"
#include "EpiGraphicsImplVK/gfxImageImplVK.h"
#include "EpiGraphicsImplVK/gfxSurfaceImplVK.h"
#include "EpiGraphicsImplVK/gfxCommandPoolImplVK.h"
#include "EpiGraphicsImplVK/gfxCommandBufferImplVK.h"
#include "EpiGraphicsImplVK/gfxRenderPassImplVK.h"
#include "EpiGraphicsImplVK/gfxFrameBufferImplVK.h"
#include "EpiGraphicsImplVK/gfxPipelineImplVK.h"
#include "EpiGraphicsImplVK/gfxBufferImplVK.h"
#include "EpiGraphicsImplVK/gfxQueueFamilyImplVK.h"
#include "EpiGraphicsImplVK/Synchronization/gfxSemaphoreImplVK.h"
#include "EpiGraphicsImplVK/Synchronization/gfxFenceImplVK.h"

#include "EpiGraphics/gfxImageView.h"

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

gfxSwapChainImplVK::gfxSwapChainImplVK(const gfxDevice& device)
    : gfxSwapChain::Impl{device}
{
}

gfxSwapChainImplVK::~gfxSwapChainImplVK()
{
    Reset();
}

epiBool gfxSwapChainImplVK::Init(const gfxSwapChainCreateInfo& info)
{
    const std::shared_ptr<gfxSurfaceImplVK> surfaceImpl = ImplOf<gfxSurfaceImplVK>(info.GetSurface());
    epiAssert(surfaceImpl != nullptr);

    std::vector<epiU32> queueFamilyIndices;
    queueFamilyIndices.reserve(info.GetQueueFamilies().Size());

    std::transform(info.GetQueueFamilies().begin(),
                   info.GetQueueFamilies().end(),
                   std::back_inserter(queueFamilyIndices),
                   [](const gfxQueueFamily& queueFamily)
    {
        const std::shared_ptr<gfxQueueFamilyImplVK> queueFamilyImpl = ImplOf<gfxQueueFamilyImplVK>(queueFamily);
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
    createInfo.imageUsage = gfxImageUsageMaskTo(info.GetImageUsageMask());
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
        const std::shared_ptr<gfxSwapChainImplVK> oldSwapChainImpl = ImplOf<gfxSwapChainImplVK>(info.GetOldSwapChain());
        epiAssert(oldSwapChainImpl != nullptr);

        createInfo.oldSwapchain = oldSwapChainImpl->GetVkSwapChain();
    }
#endif

    const std::shared_ptr<gfxDeviceImplVK> device = ImplOf<gfxDeviceImplVK>(m_Device);
    epiAssert(device != nullptr);

    if (const VkResult result = vkCreateSwapchainKHR(device->GetVkDevice(), &createInfo, nullptr, &m_VkSwapChain); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vkCreateSwapchainKHR!");
        return false;
    }

    epiU32 imageCount = 0;
    if (const VkResult result = vkGetSwapchainImagesKHR(device->GetVkDevice(), m_VkSwapChain, &imageCount, nullptr); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vkGetSwapchainImagesKHR!");
        return false;
    }

    std::vector<VkImage> swapChainImages(imageCount);
    if (const VkResult result = vkGetSwapchainImagesKHR(device->GetVkDevice(), m_VkSwapChain, &imageCount, swapChainImages.data()); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vkGetSwapchainImagesKHR!");
        return false;
    }

    for (const VkImage& imageVk : swapChainImages)
    {
        gfxImage image(std::make_shared<gfxImageImplVK>(imageVk));

        gfxImageSubresourceRange subresourceRange{};
        subresourceRange.SetAspectMask(gfxImageAspect_Color);
        subresourceRange.SetBaseMipLevel(0);
        subresourceRange.SetLevelCount(1);
        subresourceRange.SetBaseArrayLayer(0);
        subresourceRange.SetLayerCount(1);

        gfxImageViewCreateInfo imageViewCreateInfo;
        imageViewCreateInfo.SetImage(image);
        imageViewCreateInfo.SetViewType(gfxImageViewType::ImageView2D);
        imageViewCreateInfo.SetFormat(info.GetImageFormat());
        imageViewCreateInfo.SetSubresourceRange(subresourceRange);

        std::shared_ptr<gfxImageView::Impl> imageViewImpl = device->CreateImageView(imageViewCreateInfo);
        m_ImageViews.push_back(std::move(imageViewImpl));
    }

    m_Extent = info.GetImageExtent();

    return true;
}

epiBool gfxSwapChainImplVK::Reset()
{
    const std::shared_ptr<gfxDeviceImplVK> device = ImplOf<gfxDeviceImplVK>(m_Device);
    epiAssert(device != nullptr);

    const VkResult result = vkDeviceWaitIdle(device->GetVkDevice());
    if (result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vkDeviceWaitIdle!");
        return false;
    }

    m_ImageViews.Clear();

    vkDestroySwapchainKHR(device->GetVkDevice(), m_VkSwapChain, nullptr);

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
        const std::shared_ptr<gfxSemaphoreImplVK> signalSemaphoreImpl = ImplOf<gfxSemaphoreImplVK>(*signalSemaphore);
        epiAssert(signalSemaphoreImpl != nullptr);

        signalSemaphoreVk = signalSemaphoreImpl->GetVkSemaphore();
    }

    if (signalFence != nullptr)
    {
        const std::shared_ptr<gfxFenceImplVK> signalFenceImpl = ImplOf<gfxFenceImplVK>(*signalFence);
        epiAssert(signalFenceImpl != nullptr);

        signalFenceVk = signalFenceImpl->GetVkFence();
    }

    epiU32 imageIndex = 0;
    if (const VkResult result = vkAcquireNextImageKHR(ImplOf<gfxDeviceImplVK>(m_Device)->GetVkDevice(),
                                                      m_VkSwapChain,
                                                      timeout,
                                                      signalSemaphoreVk,
                                                      signalFenceVk,
                                                      &imageIndex); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vkAcquireNextImageKHR!");
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
