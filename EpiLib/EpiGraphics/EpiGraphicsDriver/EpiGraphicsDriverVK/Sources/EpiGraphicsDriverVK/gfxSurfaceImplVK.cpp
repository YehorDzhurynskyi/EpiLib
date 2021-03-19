#include "EpiGraphicsDriverVK/gfxSurfaceImplVK.h"

#include "EpiGraphicsDriverVK/gfxDriverImplVK.h"
#include "EpiGraphicsDriverVK/gfxSwapChainImplVK.h"
#include "EpiGraphicsDriverVK/gfxDeviceImplVK.h"
#include "EpiGraphicsDriverVK/gfxEnumVK.h"

#include <vulkan/vulkan.hpp>

#ifdef EPI_PLATFORM_WINDOWS
#include <Windows.h>
#include <vulkan/vulkan_win32.h>
#endif // EPI_PLATFORM_WINDOWS

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxSurfaceImplVK::gfxSurfaceImplVK(VkInstance_T* instance, const gfxWindow& window)
    : m_VkInstance{instance}
{
    VkWin32SurfaceCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    createInfo.hwnd = window.GetHWND();
    createInfo.hinstance = GetModuleHandle(nullptr);

    VkResult resultCreateWin32SurfaceKHR = vkCreateWin32SurfaceKHR(m_VkInstance, &createInfo, nullptr, &m_VkSurface);
    epiAssert(resultCreateWin32SurfaceKHR == VK_SUCCESS);
}

gfxSurfaceImplVK::~gfxSurfaceImplVK()
{
    if (m_VkSurface != VK_NULL_HANDLE)
    {
        vkDestroySurfaceKHR(m_VkInstance, m_VkSurface, nullptr);
    }
}

std::unique_ptr<gfxSwapChainImpl> gfxSurfaceImplVK::CreateSwapChain(const gfxDeviceImpl& device,
                                                                    const gfxSurfaceCapabilities& capabilities,
                                                                    const gfxSurfaceFormat& format,
                                                                    gfxSurfacePresentMode presentMode,
                                                                    const epiSize2u& extent)
{
    const gfxDeviceImplVK& deviceVk = static_cast<const gfxDeviceImplVK&>(device);

    std::unique_ptr<gfxSwapChainImplVK> impl = std::make_unique<gfxSwapChainImplVK>();
    if (!impl->Init(deviceVk.GetVkDevice(), GetVkSurface(), capabilities, format, presentMode, extent))
    {
        impl.reset();
    }

    return impl;
}

epiBool gfxSurfaceImplVK::IsPresentSupportedFor(const gfxPhysicalDeviceImpl& device) const
{
    const gfxPhysicalDeviceImplVK& deviceVk = static_cast<const gfxPhysicalDeviceImplVK&>(device);

    return std::any_of(deviceVk.GetQueueFamilies().begin(), deviceVk.GetQueueFamilies().end(), [this, &deviceVk](const gfxQueueFamilyImpl& queueFamily)
    {
        return IsPresentSupportedFor(deviceVk, queueFamily);
    });
}

epiBool gfxSurfaceImplVK::IsPresentSupportedFor(const gfxPhysicalDeviceImpl& device, const gfxQueueFamilyImpl& queueFamily) const
{
    const gfxPhysicalDeviceImplVK& deviceVk = static_cast<const gfxPhysicalDeviceImplVK&>(device);
    const gfxQueueFamilyImplVK& queueFamilyVk = static_cast<const gfxQueueFamilyImplVK&>(queueFamily);

    VkBool32 presentSupported = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(deviceVk.GetVkPhysicalDevice(), queueFamilyVk.GetIndex(), GetVkSurface(), &presentSupported);

    return presentSupported;
}

gfxSurfaceCapabilities gfxSurfaceImplVK::GetCapabilitiesFor(const gfxPhysicalDeviceImpl& device) const
{
    gfxSurfaceCapabilities capabilities;

    const gfxPhysicalDeviceImplVK& deviceVk = static_cast<const gfxPhysicalDeviceImplVK&>(device);

    VkSurfaceCapabilitiesKHR capabilitiesVk;
    const VkResult result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(deviceVk.GetVkPhysicalDevice(), GetVkSurface(), &capabilitiesVk);
    epiAssert(result == VK_SUCCESS);

    capabilities.SetMinImageCount(capabilitiesVk.minImageCount);
    capabilities.SetMaxImageCount(capabilitiesVk.maxImageCount);
    capabilities.SetMaxImageArrayLayers(capabilitiesVk.maxImageArrayLayers);
    capabilities.SetCurrentExtent(epiSize2u{capabilitiesVk.currentExtent.width, capabilitiesVk.currentExtent.height});
    capabilities.SetMinImageExtent(epiSize2u{capabilitiesVk.minImageExtent.width, capabilitiesVk.minImageExtent.height});
    capabilities.SetMaxImageExtent(epiSize2u{capabilitiesVk.maxImageExtent.width, capabilitiesVk.maxImageExtent.height});
    capabilities.SetSupportedTransforms(gfxSurfaceTransformFrom(capabilitiesVk.supportedTransforms));
    capabilities.SetSupportedCompositeAlpha(gfxCompositeAlphaFrom(capabilitiesVk.supportedCompositeAlpha));
    capabilities.SetSupportedUsage(gfxImageUsageFrom(capabilitiesVk.supportedUsageFlags));

    const gfxSurfaceTransform currentTransform = gfxSurfaceTransformFrom(capabilitiesVk.currentTransform);
    epiAssert(epiBitCount(currentTransform) == 1);

    capabilities.SetCurrentTransform(currentTransform);

    return capabilities;
}

epiArray<gfxSurfaceFormat> gfxSurfaceImplVK::GetSupportedFormatsFor(const gfxPhysicalDeviceImpl& device) const
{
    const gfxPhysicalDeviceImplVK& deviceVk = static_cast<const gfxPhysicalDeviceImplVK&>(device);

    epiU32 formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(deviceVk.GetVkPhysicalDevice(), GetVkSurface(), &formatCount, nullptr);

    std::vector<VkSurfaceFormatKHR> formatsVk;
    formatsVk.resize(formatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(deviceVk.GetVkPhysicalDevice(), GetVkSurface(), &formatCount, formatsVk.data());

    epiArray<gfxSurfaceFormat> formats;
    for (const VkSurfaceFormatKHR& format : formatsVk)
    {
        gfxSurfaceFormat surfaceFormat{};
        surfaceFormat.SetFormat(gfxFormatFrom(format.format));
        surfaceFormat.SetColorSpace(gfxSurfaceColorSpaceFrom(format.colorSpace));

        formats.push_back(surfaceFormat);
    }

    return formats;
}

epiArray<gfxSurfacePresentMode> gfxSurfaceImplVK::GetSupportedPresentModesFor(const gfxPhysicalDeviceImpl& device) const
{
    const gfxPhysicalDeviceImplVK& deviceVk = static_cast<const gfxPhysicalDeviceImplVK&>(device);

    epiU32 presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(deviceVk.GetVkPhysicalDevice(), GetVkSurface(), &presentModeCount, nullptr);

    std::vector<VkPresentModeKHR> presentModesVk;
    presentModesVk.resize(presentModeCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(deviceVk.GetVkPhysicalDevice(), GetVkSurface(), &presentModeCount, presentModesVk.data());

    epiArray<gfxSurfacePresentMode> presentModes;
    for (const VkPresentModeKHR& presentModeVk : presentModesVk)
    {
        gfxSurfacePresentMode presentMode;
        switch (presentModeVk)
        {
            case VK_PRESENT_MODE_IMMEDIATE_KHR: presentMode = gfxSurfacePresentMode::IMMEDIATE; break;
            case VK_PRESENT_MODE_MAILBOX_KHR: presentMode = gfxSurfacePresentMode::MAILBOX; break;
            case VK_PRESENT_MODE_FIFO_KHR: presentMode = gfxSurfacePresentMode::FIFO; break;
            case VK_PRESENT_MODE_FIFO_RELAXED_KHR: presentMode = gfxSurfacePresentMode::FIFO_RELAXED; break;
            case VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR: presentMode = gfxSurfacePresentMode::SHARED_DEMAND_REFRESH; break;
            case VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR: presentMode = gfxSurfacePresentMode::SHARED_CONTINUOUS_REFRESH; break;
        }

        presentModes.push_back(presentMode);
    }

    return presentModes;
}

VkSurfaceKHR gfxSurfaceImplVK::GetVkSurface() const
{
    return m_VkSurface;
}

} // namespace internalgfx

EPI_NAMESPACE_END()
