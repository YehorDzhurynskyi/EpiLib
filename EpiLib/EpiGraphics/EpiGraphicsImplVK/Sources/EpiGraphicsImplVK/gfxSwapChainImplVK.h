#pragma once

#include "EpiGraphics/gfxDriverInternal.h"

struct VkSwapchainKHR_T;
struct VkImageView_T;

EPI_NAMESPACE_BEGIN()

class gfxDeviceImplVK;
class gfxSwapChainImplVK : public gfxSwapChain::Impl
{
public:
    explicit gfxSwapChainImplVK(const gfxDeviceImplVK& device);
    gfxSwapChainImplVK(const gfxSwapChainImplVK& rhs) = delete;
    gfxSwapChainImplVK& operator=(const gfxSwapChainImplVK& rhs) = delete;
    gfxSwapChainImplVK(gfxSwapChainImplVK&& rhs) = default;
    gfxSwapChainImplVK& operator=(gfxSwapChainImplVK&& rhs) = default;
    ~gfxSwapChainImplVK() override;

    epiBool Init(const gfxSwapChainCreateInfo& info);

    epiBool Recreate(const gfxSwapChainCreateInfo& info) override;

    epiS32 AcquireNextImage(const gfxSemaphore* signalSemaphore, const gfxFence* signalFence, epiU64 timeout) override;

    epiSize2u GetExtent() const override;

    VkSwapchainKHR_T* GetVkSwapChain() const;

protected:
    epiBool Reset();

protected:
    const gfxDeviceImplVK& m_Device;
    VkSwapchainKHR_T* m_VkSwapChain{nullptr};

    epiSize2u m_Extent{};
};

EPI_NAMESPACE_END()
