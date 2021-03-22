#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

#include "EpiGraphicsDriverVK/gfxDeviceImplVK.h"

struct VkSwapchainKHR_T;
struct VkSurfaceKHR_T;
struct VkImage_T;
struct VkImageView_T;

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

    epiBool Init(const gfxSwapChainCreateInfo& info, const gfxSurfaceImpl& surfaceImpl, const gfxRenderPassImpl& renderPassImpl);

protected:
    const gfxDeviceImplVK& m_Device;
    VkSwapchainKHR_T* m_VkSwapChain{nullptr};
    std::vector<VkImage_T*> m_SwapChainImages;
    std::vector<std::unique_ptr<gfxTextureViewImpl>> m_SwapChainImageViews;
    std::vector<std::unique_ptr<gfxFrameBufferImpl>> m_SwapChainFrameBuffers;
};

} // namespace internalgfx

EPI_NAMESPACE_END()
