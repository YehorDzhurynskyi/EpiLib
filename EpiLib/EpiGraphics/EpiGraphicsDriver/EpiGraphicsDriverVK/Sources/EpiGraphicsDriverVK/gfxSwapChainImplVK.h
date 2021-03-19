#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

struct VkDevice_T;
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
    gfxSwapChainImplVK() = default;
    gfxSwapChainImplVK(const gfxSwapChainImplVK& rhs) = delete;
    gfxSwapChainImplVK& operator=(const gfxSwapChainImplVK& rhs) = delete;
    gfxSwapChainImplVK(gfxSwapChainImplVK&& rhs) = default;
    gfxSwapChainImplVK& operator=(gfxSwapChainImplVK&& rhs) = default;
    ~gfxSwapChainImplVK() override;

    epiBool Init(VkDevice_T* device,
                 VkSurfaceKHR_T* surface,
                 const gfxSurfaceCapabilities& capabilities,
                 const gfxSurfaceFormat& format,
                 gfxSurfacePresentMode presentMode,
                 const epiSize2u& extent);

protected:
    VkSwapchainKHR_T* m_VkSwapChain{nullptr};
    VkDevice_T* m_VkDevice{nullptr};
    std::vector<VkImage_T*> m_SwapChainImages;
    std::vector<VkImageView_T*> m_SwapChainImageViews;
};

} // namespace internalgfx

EPI_NAMESPACE_END()
