#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

#include "EpiGraphicsDriverVK/gfxDeviceImplVK.h"

struct VkSwapchainKHR_T;
struct VkSurfaceKHR_T;
struct VkImage_T;
struct VkImageView_T;
struct VkSemaphore_T;
struct VkFence_T;

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxSwapChainImplVK : public gfxSwapChainImpl
{
public:
    explicit gfxSwapChainImplVK(const gfxDeviceImplVK& device);
    gfxSwapChainImplVK(const gfxSwapChainImplVK& rhs) = delete;
    gfxSwapChainImplVK& operator=(const gfxSwapChainImplVK& rhs) = delete;
    gfxSwapChainImplVK(gfxSwapChainImplVK&& rhs) = default;
    gfxSwapChainImplVK& operator=(gfxSwapChainImplVK&& rhs) = default;
    ~gfxSwapChainImplVK() override;

    epiBool Init(const gfxSwapChainCreateInfo& info,
                 const gfxSurfaceImpl& surfaceImpl,
                 const gfxQueueFamilyImpl& queueFamilyImpl,
                 const gfxRenderPassImpl& renderPassImpl);

    epiBool Recreate(const gfxSwapChainCreateInfo& info,
                     const gfxSurfaceImpl& surfaceImpl,
                     const gfxQueueFamilyImpl& queueFamilyImpl,
                     const gfxRenderPassImpl& renderPassImpl) override;

    epiS32 AcquireNextImage(const gfxSemaphore* signalSemaphore, const gfxFence* signalFence, epiU64 timeout) override;

    gfxCommandBufferRecord ForBufferRecordCommands(epiU32 bufferIndex, gfxCommandBufferUsage usageMask = gfxCommandBufferUsage{0}) override;
    gfxRenderPassBeginInfo ForBufferCreateRenderPassBeginInfo(epiU32 bufferIndex) override;
    gfxQueueSubmitInfo ForBufferCreateQueueSubmitInfo(epiU32 bufferIndex) override;

    epiU32 GetBufferCount() const override;
    epiSize2u GetExtent() const override;

    VkSwapchainKHR_T* GetVkSwapChain() const;

protected:
    epiBool Reset();

protected:
    const gfxDeviceImplVK& m_Device;
    VkSwapchainKHR_T* m_VkSwapChain{nullptr};

    std::vector<std::shared_ptr<gfxTextureViewImpl>> m_SwapChainImageViews;
    std::vector<std::shared_ptr<gfxFrameBufferImpl>> m_SwapChainFrameBuffers;
    std::shared_ptr<gfxCommandPoolImpl> m_CommandPool;

    epiSize2u m_Extent{};
};

} // namespace internalgfx

EPI_NAMESPACE_END()
