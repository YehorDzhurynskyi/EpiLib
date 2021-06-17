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

epiBool gfxSwapChainImplVK::Init(const gfxSwapChainCreateInfo& info)
{
    // NOTE: queue families should provided with a concurrent SharingMode only
    epiAssert(info.GetImageSharingMode() == gfxSharingMode::Concurrent || info.GetQueueFamilies().IsEmpty());
    std::vector<epiU32> queueFamilyIndices;
    queueFamilyIndices.reserve(info.GetQueueFamilies().GetSize());

    std::transform(info.GetQueueFamilies().begin(),
                   info.GetQueueFamilies().end(),
                   std::back_inserter(queueFamilyIndices),
                   [](const gfxQueueFamily& family)
    {
        const gfxQueueFamilyImplVK* familyImpl = static_cast<const gfxQueueFamilyImplVK*>(gfxQueueFamilyImpl::ExtractImpl(family));
        epiAssert(familyImpl != nullptr);

        return familyImpl->GetIndex();
    });

    const gfxSurfaceImplVK* surfaceImpl = static_cast<const gfxSurfaceImplVK*>(gfxSurfaceImpl::ExtractImpl(info.GetSurface()));
    epiAssert(surfaceImpl != nullptr);

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
    createInfo.clipped = info.GetClipped();
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

    epiU32 imageCount;
    vkGetSwapchainImagesKHR(m_Device.GetVkDevice(), m_VkSwapChain, &imageCount, nullptr);

    std::vector<VkImage> swapChainImages(imageCount, VK_NULL_HANDLE);
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
        textureViewCreateInfo.SetFormat(info.GetImageFormat());
        textureViewCreateInfo.SetSubresourceRange(subresourceRange);

        std::shared_ptr<gfxTextureViewImpl> textureViewImpl = m_Device.CreateTextureView(textureViewCreateInfo, *textureImpl);
        m_ImageViews.push_back(std::move(textureViewImpl));
    }

    m_Extent = info.GetImageExtent();

#if 0
    for (const auto& textureViewImpl : m_SwapChainImageViews)
    {
        gfxFrameBufferCreateInfo frameBufferCreateInfo;
        frameBufferCreateInfo.SetSize(info.GetExtent());
        epiPtrArray<const gfxTextureViewImpl> imageViewImpls{textureViewImpl.get()};

        std::transform(info.GetAdditionalFrameBufferAttachments().begin(),
                       info.GetAdditionalFrameBufferAttachments().end(),
                       std::back_inserter(imageViewImpls),
                       [](const gfxTextureView& imageView)
        {
            const gfxTextureViewImpl* imageViewImpl = gfxTextureViewImpl::ExtractImpl(imageView);
            epiAssert(imageViewImpl != nullptr);

            return imageViewImpl;
        });

        std::shared_ptr<gfxFrameBufferImpl> frameBufferImpl = m_Device.CreateFrameBuffer(frameBufferCreateInfo, renderPassImpl, imageViewImpls);
        m_SwapChainFrameBuffers.push_back(std::move(frameBufferImpl));
    }

    gfxCommandPoolCreateInfo commandPoolCreateInfo;
    commandPoolCreateInfo.SetPrimaryCommandBufferCount(m_SwapChainFrameBuffers.size());

    m_CommandPool = m_Device.CreateCommandPool(commandPoolCreateInfo, queueFamilyImpl);
#endif

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

#if 0
gfxCommandBufferRecord gfxSwapChainImplVK::ForBufferRecordCommands(epiU32 bufferIndex, gfxCommandBufferUsage usageMask)
{
    gfxCommandBufferRecord record;

    if (bufferIndex >= GetBufferCount())
    {
        epiLogError("Failed to record command buffer! Provided buffer index=`{}` exceeds buffer count=`{}`", bufferIndex, GetBufferCount());
        return record;
    }

    gfxCommandBufferImpl* cmdImpl = m_CommandPool->GetPrimaryCommandBuffers()[bufferIndex].get();
    if (cmdImpl == nullptr)
    {
        epiLogError("Failed to record command buffer! Buffer at index=`{}` is nullptr!", bufferIndex);
        return record;
    }

    record.RecordBegin(cmdImpl, usageMask);

    return record;
}

gfxRenderPassBeginInfo gfxSwapChainImplVK::ForBufferCreateRenderPassBeginInfo(epiU32 bufferIndex)
{
    gfxRenderPassBeginInfo beginInfo;

    if (bufferIndex >= GetBufferCount())
    {
        epiLogError("Failed to create RenderPassBeginInfo! Provided buffer index=`{}` exceeds buffer count=`{}`", bufferIndex, GetBufferCount());
        return beginInfo;
    }

    beginInfo.SetFrameBuffer(gfxFrameBuffer(m_SwapChainFrameBuffers[bufferIndex]));
    beginInfo.SetRenderArea(epiRect2s{0, 0, static_cast<epiS32>(GetExtent().x), static_cast<epiS32>(GetExtent().y)});

    return beginInfo;
}

gfxQueueSubmitInfo gfxSwapChainImplVK::ForBufferCreateQueueSubmitInfo(epiU32 bufferIndex)
{
    gfxQueueSubmitInfo queueSubmitInfo;

    if (bufferIndex >= GetBufferCount())
    {
        epiLogError("Failed to create QueueSubmitInfo! Provided buffer index=`{}` exceeds buffer count=`{}`", bufferIndex, GetBufferCount());
        return queueSubmitInfo;
    }

    queueSubmitInfo.GetCommandBuffers().push_back(gfxCommandBuffer(m_CommandPool->GetPrimaryCommandBuffers()[bufferIndex]));

    return queueSubmitInfo;
}
#endif

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
