#include "EpiGraphicsDriverVK/gfxSwapChainImplVK.h"

#include "EpiGraphicsDriverVK/gfxDriverImplVK.h"
#include "EpiGraphicsDriverVK/gfxEnumVK.h"

#include <vulkan/vulkan.hpp>

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

epiBool gfxSwapChainImplVK::Init(VkDevice device,
                                 VkSurfaceKHR surface,
                                 const gfxSurfaceCapabilities& capabilities,
                                 const gfxSurfaceFormat& format,
                                 gfxSurfacePresentMode presentMode,
                                 const epiSize2u& extent)
{
    m_VkDevice = device;

    epiU32 imageCount = capabilities.GetMinImageCount() + 1;
    if (const epiU32 maxImageCount = capabilities.GetMaxImageCount(); maxImageCount > 0 && imageCount > maxImageCount)
    {
        imageCount = maxImageCount;
    }

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = surface;
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = gfxFormatTo(format.GetFormat());
    createInfo.imageColorSpace = gfxSurfaceColorSpaceTo(format.GetColorSpace());
    createInfo.imageExtent = VkExtent2D{extent.x, extent.y};
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    createInfo.queueFamilyIndexCount = 0;
    createInfo.pQueueFamilyIndices = nullptr;
    createInfo.preTransform = gfxSurfaceTransformTo(capabilities.GetCurrentTransform());
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = gfxSurfacePresentModeTo(presentMode);
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;

    if (VK_SUCCESS != vkCreateSwapchainKHR(device, &createInfo, nullptr, &m_VkSwapChain))
    {
        return false;
    }

    vkGetSwapchainImagesKHR(device, m_VkSwapChain, &imageCount, nullptr);

    m_SwapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(device, m_VkSwapChain, &imageCount, m_SwapChainImages.data());

    return true;
}

gfxSwapChainImplVK::~gfxSwapChainImplVK()
{
    if (m_VkDevice != nullptr && m_VkSwapChain != nullptr)
    {
        vkDestroySwapchainKHR(m_VkDevice, m_VkSwapChain, nullptr);
    }
}

} // namespace internalgfx

EPI_NAMESPACE_END()
