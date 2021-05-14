#include "EpiGraphicsDriverVK/gfxSwapChainImplVK.h"

#include "EpiGraphicsDriverVK/gfxDriverImplVK.h"
#include "EpiGraphicsDriverVK/gfxTextureImplVK.h"
#include "EpiGraphicsDriverVK/gfxSurfaceImplVK.h"
#include "EpiGraphicsDriverVK/gfxCommandPoolImplVK.h"
#include "EpiGraphicsDriverVK/gfxRenderPassImplVK.h"
#include "EpiGraphicsDriverVK/gfxFrameBufferImplVK.h"
#include "EpiGraphicsDriverVK/gfxPipelineImplVK.h"
#include "EpiGraphicsDriverVK/gfxEnumVK.h"

#include "EpiGraphicsDriverCommon/gfxTextureView.h"

#include <vulkan/vulkan.hpp>

namespace
{

constexpr epiU32 kMaxFramesInFlight = 2;

} // namespace

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxSwapChainImplVK::gfxSwapChainImplVK(const gfxDeviceImplVK& device)
    : m_Device{device}
{
}

gfxSwapChainImplVK::~gfxSwapChainImplVK()
{
    for (VkSemaphore semaphore : m_VkSemaphoreRenderFinished)
    {
        vkDestroySemaphore(m_Device.GetVkDevice(), semaphore, nullptr);
    }

    for (VkSemaphore semaphore : m_VkSemaphoreImageAvailable)
    {
        vkDestroySemaphore(m_Device.GetVkDevice(), semaphore, nullptr);
    }

    for (VkFence fence : m_VkFencesInFlight)
    {
        vkDestroyFence(m_Device.GetVkDevice(), fence, nullptr);
    }

    vkDestroySwapchainKHR(m_Device.GetVkDevice(), m_VkSwapChain, nullptr);
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

    if (VK_SUCCESS != vkCreateSwapchainKHR(m_Device.GetVkDevice(), &createInfo, nullptr, &m_VkSwapChain))
    {
        return false;
    }

    vkGetSwapchainImagesKHR(m_Device.GetVkDevice(), m_VkSwapChain, &imageCount, nullptr);

    std::vector<VkImage> swapChainImages(imageCount);
    vkGetSwapchainImagesKHR(m_Device.GetVkDevice(), m_VkSwapChain, &imageCount, swapChainImages.data());

    for (const VkImage& image : swapChainImages)
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

        std::shared_ptr<gfxTextureImplVK> textureImpl = std::make_shared<gfxTextureImplVK>(image);
        gfxTexture texture(textureImpl);

        gfxTextureViewCreateInfo textureViewCreateInfo;
        textureViewCreateInfo.SetFormat(info.GetFormat().GetFormat());
        textureViewCreateInfo.SetViewType(gfxTextureViewType::TextureView2D);
        textureViewCreateInfo.SetTexture(&texture);

        std::shared_ptr<gfxTextureViewImpl> textureViewImpl = m_Device.CreateTextureView(textureViewCreateInfo, *textureImpl);
        m_SwapChainImageViews.push_back(std::move(textureViewImpl));
    }

    for (const auto& textureViewImpl : m_SwapChainImageViews)
    {
        gfxFrameBufferCreateInfo frameBufferCreateInfo;
        frameBufferCreateInfo.SetSize(info.GetExtent());
        epiPtrArray<const gfxTextureViewImpl> textureViewImpls{textureViewImpl.get()};

        std::shared_ptr<gfxFrameBufferImpl> frameBufferImpl = m_Device.CreateFrameBuffer(frameBufferCreateInfo, renderPassImpl, textureViewImpls);
        m_SwapChainFrameBuffers.push_back(std::move(frameBufferImpl));
    }

    gfxCommandPoolCreateInfo commandPoolCreateInfo;
    commandPoolCreateInfo.SetPrimaryCommandBufferCount(m_SwapChainFrameBuffers.Size());

    m_CommandPool = m_Device.CreateCommandPool(commandPoolCreateInfo, queueFamilyImpl);

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    m_VkSemaphoreImageAvailable.resize(kMaxFramesInFlight);
    m_VkSemaphoreRenderFinished.resize(kMaxFramesInFlight);
    m_VkFencesInFlight.resize(kMaxFramesInFlight);
    m_VkFencesImagesInFlight.resize(m_SwapChainFrameBuffers.Size(), VK_NULL_HANDLE);

    for (epiU32 i = 0; i < kMaxFramesInFlight; ++i)
    {
        if (vkCreateSemaphore(m_Device.GetVkDevice(), &semaphoreInfo, nullptr, &m_VkSemaphoreImageAvailable[i]) != VK_SUCCESS ||
            vkCreateSemaphore(m_Device.GetVkDevice(), &semaphoreInfo, nullptr, &m_VkSemaphoreRenderFinished[i]) != VK_SUCCESS ||
            vkCreateFence(m_Device.GetVkDevice(), &fenceInfo, nullptr, &m_VkFencesInFlight[i]) != VK_SUCCESS)
        {
            return false;
        }
    }

    return true;
}

epiBool gfxSwapChainImplVK::AssignRenderPass(const gfxRenderPassImpl& renderPass, const gfxPipelineGraphicsImpl& pipeline)
{
    const epiArray<std::shared_ptr<gfxCommandBufferImpl>>& commandBuffers = m_CommandPool->GetPrimaryCommandBuffers();
    const gfxRenderPassImplVK& renderPassVk = static_cast<const gfxRenderPassImplVK&>(renderPass);
    const gfxPipelineGraphicsImplVK& pipelineVk = static_cast<const gfxPipelineGraphicsImplVK&>(pipeline);

    const VkExtent2D extent{GetExtent().x, GetExtent().y};

    for (epiU32 i = 0; i < commandBuffers.Size(); ++i)
    {
        const std::shared_ptr<gfxCommandBufferImpl>& commandBuffer = commandBuffers[i];

        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        VkCommandBuffer commandBufferVk = static_cast<const gfxCommandBufferImplVK*>(commandBuffer.get())->GetVkCommandBuffer();
        if (vkBeginCommandBuffer(commandBufferVk, &beginInfo) != VK_SUCCESS)
        {
            epiLogError("Failed to begin command buffer!");
            return false;
        }

        VkClearValue clearColor = {0.0f, 0.0f, 0.0f, 1.0f};

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = renderPassVk.GetVkRenderPass();
        renderPassInfo.framebuffer = static_cast<const gfxFrameBufferImplVK*>(m_SwapChainFrameBuffers[i].get())->GetVkFrameBuffer();
        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = extent;
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(commandBufferVk, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(commandBufferVk, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineVk.GetVkPipeline());

        vkCmdDraw(commandBufferVk, 3, 1, 0, 0);

        vkCmdEndRenderPass(commandBufferVk);

        if (vkEndCommandBuffer(commandBufferVk) != VK_SUCCESS)
        {
            epiLogError("Failed to end command buffer!");
            return false;
        }
    }

    return true;
}

epiBool gfxSwapChainImplVK::Present(const gfxQueueImpl& queue)
{
    const epiU32 frameIndex = m_CurrentFrame % kMaxFramesInFlight;

    vkWaitForFences(m_Device.GetVkDevice(), 1, &m_VkFencesInFlight[frameIndex], VK_TRUE, UINT64_MAX);

    epiU32 imageIndex;
    if (vkAcquireNextImageKHR(m_Device.GetVkDevice(),
                              m_VkSwapChain,
                              std::numeric_limits<epiU64>::max(),
                              m_VkSemaphoreImageAvailable[frameIndex],
                              VK_NULL_HANDLE,
                              &imageIndex) != VK_SUCCESS)
    {
        epiLogError("vkAcquireNextImageKHR"); // TODO: add message
        return false;
    }

    if (m_VkFencesImagesInFlight[imageIndex] != VK_NULL_HANDLE)
    {
        vkWaitForFences(m_Device.GetVkDevice(), 1, &m_VkFencesImagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
    }
    // Mark the image as now being in use by this frame
    m_VkFencesImagesInFlight[imageIndex] = m_VkFencesInFlight[frameIndex];


    VkSemaphore waitSemaphores[] = {m_VkSemaphoreImageAvailable[frameIndex]};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    VkCommandBuffer commandBuffers[] = {static_cast<gfxCommandBufferImplVK*>(m_CommandPool->GetPrimaryCommandBuffers()[imageIndex].get())->GetVkCommandBuffer()};
    VkSemaphore signalSemaphores[] = {m_VkSemaphoreRenderFinished[frameIndex]};

    static_assert(epiArrLen(waitSemaphores) == epiArrLen(waitStages));

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.waitSemaphoreCount = epiArrLen(waitSemaphores);
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.commandBufferCount = epiArrLen(commandBuffers);
    submitInfo.pCommandBuffers = commandBuffers;
    submitInfo.signalSemaphoreCount = epiArrLen(signalSemaphores);
    submitInfo.pSignalSemaphores = signalSemaphores;

    vkResetFences(m_Device.GetVkDevice(), 1, &m_VkFencesInFlight[frameIndex]);

    if (vkQueueSubmit(static_cast<const gfxQueueImplVK&>(queue).GetVkQueue(), 1, &submitInfo, m_VkFencesInFlight[frameIndex]) != VK_SUCCESS)
    {
        epiLogError("vkQueueSubmit"); // TODO: add message
        return false;
    }

    VkSwapchainKHR swapChains[] = {m_VkSwapChain};

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;
    presentInfo.swapchainCount = epiArrLen(swapChains);
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;
    presentInfo.pResults = nullptr;

    if (vkQueuePresentKHR(static_cast<const gfxQueueImplVK&>(queue).GetVkQueue(), &presentInfo) != VK_SUCCESS)
    {
        epiLogError("vkQueuePresentKHR"); // TODO: add message
        return false;
    }

#if 0 // TODO: figure out whether this sync point should be used
    if (vkQueueWaitIdle(static_cast<const gfxQueueImplVK&>(queueImpl).GetVkQueue()) != VK_SUCCESS)
    {
        epiLogError("vkQueueWaitIdle"); // TODO: add message
        return false;
    }
#endif

    ++m_CurrentFrame;

    return true;
}

epiSize2u gfxSwapChainImplVK::GetExtent() const
{
    return m_Extent;
}

} // namespace internalgfx

EPI_NAMESPACE_END()
