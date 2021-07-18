#include "EpiGraphicsDriverVK/gfxQueueImplVK.h"

#include "EpiGraphicsDriverVK/gfxErrorVK.h"
#include "EpiGraphicsDriverVK/gfxEnumVK.h"
#include "EpiGraphicsDriverVK/gfxDeviceImplVK.h"
#include "EpiGraphicsDriverVK/gfxQueueFamilyImplVK.h"
#include "EpiGraphicsDriverVK/gfxCommandBufferImplVK.h"
#include "EpiGraphicsDriverVK/gfxSwapChainImplVK.h"
#include "EpiGraphicsDriverVK/Synchronization/gfxSemaphoreImplVK.h"
#include "EpiGraphicsDriverVK/Synchronization/gfxFenceImplVK.h"

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

gfxQueueImplVK::gfxQueueImplVK(const gfxDeviceImplVK& device, const gfxQueueFamilyImplVK& queueFamily, epiU32 queueIndex, epiFloat priority)
    : m_Type{queueFamily.GetQueueTypeMask()}
    , m_Priority{priority}
{
    vkGetDeviceQueue(device.GetVkDevice(), queueFamily.GetIndex(), queueIndex, &m_VkQueue);
}

gfxQueueImplVK::gfxQueueImplVK(gfxQueueImplVK&& rhs)
{
    m_VkQueue = rhs.m_VkQueue;
    m_Type = rhs.m_Type;

    rhs.m_VkQueue = nullptr;
    rhs.m_Type = static_cast<gfxQueueType>(0);
}

gfxQueueImplVK& gfxQueueImplVK::operator=(gfxQueueImplVK&& rhs)
{
    m_VkQueue = rhs.m_VkQueue;
    m_Type = rhs.m_Type;

    rhs.m_VkQueue = nullptr;
    rhs.m_Type = static_cast<gfxQueueType>(0);

    return *this;
}

epiBool gfxQueueImplVK::Submit(const epiArray<gfxQueueSubmitInfo>& infos)
{
    return Submit(infos, VK_NULL_HANDLE);
}

epiBool gfxQueueImplVK::Submit(const epiArray<gfxQueueSubmitInfo>& infos, const gfxFence& signalFence)
{
    const gfxFenceImplVK* signalFenceImpl = static_cast<const gfxFenceImplVK*>(gfxFence::Impl::ExtractImpl(signalFence));
    epiAssert(signalFenceImpl != nullptr);

    return Submit(infos, signalFenceImpl->GetVkFence());
}

epiBool gfxQueueImplVK::Submit(const epiArray<gfxQueueSubmitInfo>& infos, VkFence signalFence)
{
    std::vector<VkSubmitInfo> submitInfosVk;
    submitInfosVk.reserve(infos.GetSize());

    std::vector<std::vector<VkCommandBuffer>> commandBuffersVk;
    commandBuffersVk.reserve(infos.GetSize());

    std::vector<std::vector<VkSemaphore>> waitSemaphoresVk;
    waitSemaphoresVk.reserve(infos.GetSize());

    std::vector<std::vector<VkPipelineStageFlags>> waitDstStageMaskVk;
    waitDstStageMaskVk.reserve(infos.GetSize());

    std::vector<std::vector<VkSemaphore>> signalSemaphoresVk;
    signalSemaphoresVk.reserve(infos.GetSize());

    std::transform(infos.begin(),
                   infos.end(),
                   std::back_inserter(submitInfosVk),
                   [&commandBuffersVk, &waitSemaphoresVk, &waitDstStageMaskVk, &signalSemaphoresVk](const gfxQueueSubmitInfo& info)
    {
        std::vector<VkCommandBuffer>& commandBuffersInfoVk = commandBuffersVk.emplace_back();
        commandBuffersInfoVk.reserve(info.GetCommandBuffers().Size());

        std::transform(info.GetCommandBuffers().begin(),
                       info.GetCommandBuffers().end(),
                       std::back_inserter(commandBuffersInfoVk),
                       [](const gfxCommandBuffer& commandBuffer)
        {
            const internalgfx::gfxCommandBufferImplVK* commandBufferImpl = static_cast<const internalgfx::gfxCommandBufferImplVK*>(internalgfx::gfxCommandBufferImpl::ExtractImpl(commandBuffer));
            epiAssert(commandBufferImpl != nullptr);

            return commandBufferImpl->GetVkCommandBuffer();
        });

        std::vector<VkSemaphore>& waitSemaphoresInfoVk = waitSemaphoresVk.emplace_back();
        waitSemaphoresInfoVk.reserve(info.GetWaitSemaphores().Size());

        std::transform(info.GetWaitSemaphores().begin(),
                       info.GetWaitSemaphores().end(),
                       std::back_inserter(waitSemaphoresInfoVk),
                       [](const gfxSemaphore& semaphore)
        {
            const gfxSemaphoreImplVK* semaphoreImpl = static_cast<const gfxSemaphoreImplVK*>(gfxSemaphore::Impl::ExtractImpl(semaphore));
            epiAssert(semaphoreImpl != nullptr);

            return semaphoreImpl->GetVkSemaphore();
        });

        std::vector<VkPipelineStageFlags>& waitDstStageMaskInfoVk = waitDstStageMaskVk.emplace_back();
        waitDstStageMaskInfoVk.reserve(info.GetWaitDstStageMasks().Size());

        std::transform(info.GetWaitDstStageMasks().begin(),
                       info.GetWaitDstStageMasks().end(),
                       std::back_inserter(waitDstStageMaskInfoVk),
                       [](const gfxPipelineStage& stage)
        {
            return gfxPipelineStageTo(stage);
        });

        std::vector<VkSemaphore>& signalSemaphoresInfoVk = signalSemaphoresVk.emplace_back();
        signalSemaphoresInfoVk.reserve(info.GetSignalSemaphores().Size());

        std::transform(info.GetSignalSemaphores().begin(),
                       info.GetSignalSemaphores().end(),
                       std::back_inserter(signalSemaphoresInfoVk),
                       [](const gfxSemaphore& semaphore)
        {
            const gfxSemaphoreImplVK* semaphoreImpl = static_cast<const gfxSemaphoreImplVK*>(gfxSemaphore::Impl::ExtractImpl(semaphore));
            epiAssert(semaphoreImpl != nullptr);

            return semaphoreImpl->GetVkSemaphore();
        });

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = commandBuffersInfoVk.size();
        submitInfo.pCommandBuffers = commandBuffersInfoVk.data();
        submitInfo.waitSemaphoreCount = waitSemaphoresInfoVk.size();
        submitInfo.pWaitSemaphores = waitSemaphoresInfoVk.data();
        submitInfo.pWaitDstStageMask = waitDstStageMaskInfoVk.data();
        submitInfo.signalSemaphoreCount = signalSemaphoresInfoVk.size();
        submitInfo.pSignalSemaphores = signalSemaphoresInfoVk.data();

        return submitInfo;
    });

    if (const VkResult result = vkQueueSubmit(m_VkQueue, submitInfosVk.size(), submitInfosVk.data(), signalFence); result != VK_SUCCESS)
    {
        gfxLogErrorEx(result, "Failed to call vkQueueSubmit!");
        return false;
    }

    return true;
}

epiBool gfxQueueImplVK::Present(const gfxQueuePresentInfo& info)
{
    std::vector<VkSwapchainKHR> swapChainsVk;
    swapChainsVk.reserve(info.GetSwapChains().Size());

    std::vector<VkSemaphore> waitSemaphoresVk;
    waitSemaphoresVk.reserve(info.GetWaitSemaphores().Size());

    std::transform(info.GetSwapChains().begin(), info.GetSwapChains().end(), std::back_inserter(swapChainsVk), [](const gfxSwapChain& swapChain)
    {
        const gfxSwapChainImplVK* swapChainImpl = static_cast<const gfxSwapChainImplVK*>(gfxSwapChain::Impl::ExtractImpl(swapChain));
        epiAssert(swapChainImpl != nullptr);

        return swapChainImpl->GetVkSwapChain();
    });

    std::transform(info.GetWaitSemaphores().begin(), info.GetWaitSemaphores().end(), std::back_inserter(waitSemaphoresVk), [](const gfxSemaphore& semaphore)
    {
        const gfxSemaphoreImplVK* semaphorempl = static_cast<const gfxSemaphoreImplVK*>(gfxSemaphore::Impl::ExtractImpl(semaphore));
        epiAssert(semaphorempl != nullptr);

        return semaphorempl->GetVkSemaphore();
    });

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.swapchainCount = swapChainsVk.size();
    presentInfo.pSwapchains = swapChainsVk.data();
    presentInfo.waitSemaphoreCount = waitSemaphoresVk.size();
    presentInfo.pWaitSemaphores = waitSemaphoresVk.data();
    presentInfo.pImageIndices = info.GetSwapChainImageIndices().data();
    presentInfo.pResults = nullptr; // TODO: set

    if (const VkResult result = vkQueuePresentKHR(m_VkQueue, &presentInfo); result != VK_SUCCESS)
    {
        gfxLogErrorEx(result, "Failed to call vkQueuePresentKHR!");
        return false;
    }

    return true;
}

epiBool gfxQueueImplVK::Wait()
{
    if (const VkResult result = vkQueueWaitIdle(m_VkQueue); result != VK_SUCCESS)
    {
        gfxLogErrorEx(result, "Failed to call vkQueueWaitIdle!");
        return false;
    }

    return true;
}

gfxQueueType gfxQueueImplVK::GetType() const
{
    return m_Type;
}

epiFloat gfxQueueImplVK::GetPriority() const
{
    return m_Priority;
}

epiBool gfxQueueImplVK::IsQueueTypeSupported(gfxQueueType mask) const
{
    return (m_Type & mask) == mask;
}

VkQueue gfxQueueImplVK::GetVkQueue() const
{
    return m_VkQueue;
}

EPI_NAMESPACE_END()
