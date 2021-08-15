#include "EpiGraphicsImplVK/gfxSurfaceImplVK.h"

#include "EpiGraphicsImplVK/gfxEnumVK.h"
#include "EpiGraphicsImplVK/gfxErrorVK.h"
#include "EpiGraphicsImplVK/gfxSwapChainImplVK.h"
#include "EpiGraphicsImplVK/gfxDeviceImplVK.h"
#include "EpiGraphicsImplVK/gfxQueueFamilyImplVK.h"

#include "EpiGraphics/gfxWindow.h"

#include <vulkan/vulkan.h>

#ifdef EPI_PLATFORM_WINDOWS
#include <Windows.h>
#include <vulkan/vulkan_win32.h>
#endif // EPI_PLATFORM_WINDOWS

EPI_NAMESPACE_BEGIN()

gfxSurfaceImplVK::gfxSurfaceImplVK(VkInstance_T* instance)
    : m_VkInstance{instance}
{
}

gfxSurfaceImplVK::~gfxSurfaceImplVK()
{
    if (m_VkSurface != VK_NULL_HANDLE)
    {
        vkDestroySurfaceKHR(m_VkInstance, m_VkSurface, nullptr);
    }
}

epiBool gfxSurfaceImplVK::Init(const gfxWindow& window)
{
    VkWin32SurfaceCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    createInfo.hwnd = window.GetHWND();
    createInfo.hinstance = GetModuleHandle(nullptr);

    if (const VkResult result = vkCreateWin32SurfaceKHR(m_VkInstance, &createInfo, nullptr, &m_VkSurface); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vkCreateWin32SurfaceKHR!");
        return false;
    }

    return true;
}

epiBool gfxSurfaceImplVK::IsPresentSupportedFor(const gfxPhysicalDevice& device, const gfxQueueFamily& queueFamily) const
{
    if (!device.HasImpl())
    {
        epiLogError("Failed to query presentation support! The provided PhysicalDevice has no implementation!");
        return false;
    }

    if (!queueFamily.HasImpl())
    {
        epiLogError("Failed to query presentation support! The provided QueueFamily has no implementation!");
        return false;
    }

    const std::shared_ptr<gfxPhysicalDeviceImplVK> deviceVk = std::static_pointer_cast<gfxPhysicalDeviceImplVK>(gfxPhysicalDevice::Impl::ExtractImpl(device));
    epiAssert(deviceVk != nullptr);

    const gfxQueueFamilyImplVK* queueFamilyVk = static_cast<const gfxQueueFamilyImplVK*>(gfxQueueFamily::Impl::ExtractImpl(queueFamily));
    epiAssert(queueFamilyVk != nullptr);

    VkBool32 presentSupported = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(deviceVk->GetVkPhysicalDevice(), queueFamilyVk->GetIndex(), GetVkSurface(), &presentSupported);

    return presentSupported;
}

epiBool gfxSurfaceImplVK::IsPresentSupportedFor(const gfxPhysicalDevice& device, const gfxQueueFamilyDescriptor& queueFamilyDesc) const
{
    if (!device.HasImpl())
    {
        epiLogError("Failed to query presentation support! The provided PhysicalDevice has no implementation!");
        return false;
    }

    if (!queueFamilyDesc.HasImpl())
    {
        epiLogError("Failed to query presentation support! The provided QueueFamilyDescriptor has no implementation!");
        return false;
    }

    const std::shared_ptr<gfxPhysicalDeviceImplVK> deviceVk = std::static_pointer_cast<gfxPhysicalDeviceImplVK>(gfxPhysicalDevice::Impl::ExtractImpl(device));
    epiAssert(deviceVk != nullptr);

    const gfxQueueFamilyDescriptorImplVK* queueFamilyDescriptorVk = static_cast<const gfxQueueFamilyDescriptorImplVK*>(gfxQueueFamilyDescriptor::Impl::ExtractImpl(queueFamilyDesc));
    epiAssert(queueFamilyDescriptorVk != nullptr);

    VkBool32 presentSupported = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(deviceVk->GetVkPhysicalDevice(), queueFamilyDescriptorVk->GetIndex(), GetVkSurface(), &presentSupported);

    return presentSupported;
}

gfxSurfaceCapabilities gfxSurfaceImplVK::GetCapabilitiesFor(const gfxPhysicalDevice& device) const
{
    if (!device.HasImpl())
    {
        epiLogError("Failed to query supported SurfaceCapabilities! The provided PhysicalDevice has no implementation!");
        return {};
    }

    const std::shared_ptr<gfxPhysicalDeviceImplVK> deviceVk = std::static_pointer_cast<gfxPhysicalDeviceImplVK>(gfxPhysicalDevice::Impl::ExtractImpl(device));
    epiAssert(deviceVk != nullptr);

    gfxSurfaceCapabilities capabilities;

    VkSurfaceCapabilitiesKHR capabilitiesVk;
    if (const VkResult result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(deviceVk->GetVkPhysicalDevice(), GetVkSurface(), &capabilitiesVk); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vkGetPhysicalDeviceSurfaceCapabilitiesKHR!");
        return capabilities;
    }

    capabilities.SetMinImageCount(capabilitiesVk.minImageCount);
    capabilities.SetMaxImageCount(capabilitiesVk.maxImageCount);
    capabilities.SetMaxImageArrayLayers(capabilitiesVk.maxImageArrayLayers);
    capabilities.SetCurrentExtent(epiSize2u{capabilitiesVk.currentExtent.width, capabilitiesVk.currentExtent.height});
    capabilities.SetMinImageExtent(epiSize2u{capabilitiesVk.minImageExtent.width, capabilitiesVk.minImageExtent.height});
    capabilities.SetMaxImageExtent(epiSize2u{capabilitiesVk.maxImageExtent.width, capabilitiesVk.maxImageExtent.height});
    capabilities.SetSupportedSurfaceTransformMask(gfxSurfaceTransformMaskFrom(capabilitiesVk.supportedTransforms));
    capabilities.SetSupportedCompositeAlphaMask(gfxCompositeAlphaMaskFrom(capabilitiesVk.supportedCompositeAlpha));
    capabilities.SetSupportedUsage(gfxImageUsageFrom(capabilitiesVk.supportedUsageFlags));

    const gfxSurfaceTransformMask currentTransform = gfxSurfaceTransformMaskFrom(capabilitiesVk.currentTransform);
    epiAssert(epiBitCount(currentTransform) == 1);

    capabilities.SetCurrentSurfaceTransformMask(currentTransform);

    return capabilities;
}

epiArray<gfxSurfaceFormat> gfxSurfaceImplVK::GetSupportedFormatsFor(const gfxPhysicalDevice& device) const
{
    if (!device.HasImpl())
    {
        epiLogError("Failed to query supported SurfaceFormats! The provided PhysicalDevice has no implementation!");
        return {};
    }

    const std::shared_ptr<gfxPhysicalDeviceImplVK> deviceVk = std::static_pointer_cast<gfxPhysicalDeviceImplVK>(gfxPhysicalDevice::Impl::ExtractImpl(device));
    epiAssert(deviceVk != nullptr);

    epiU32 formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(deviceVk->GetVkPhysicalDevice(), GetVkSurface(), &formatCount, nullptr);

    std::vector<VkSurfaceFormatKHR> formatsVk;
    formatsVk.resize(formatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(deviceVk->GetVkPhysicalDevice(), GetVkSurface(), &formatCount, formatsVk.data());

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

epiArray<gfxSurfacePresentMode> gfxSurfaceImplVK::GetSupportedPresentModesFor(const gfxPhysicalDevice& device) const
{
    if (!device.HasImpl())
    {
        epiLogError("Failed to query supported SurfacePresentModes! The provided PhysicalDevice has no implementation!");
        return {};
    }

    const std::shared_ptr<gfxPhysicalDeviceImplVK> deviceVk = std::static_pointer_cast<gfxPhysicalDeviceImplVK>(gfxPhysicalDevice::Impl::ExtractImpl(device));
    epiAssert(deviceVk != nullptr);

    epiU32 presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(deviceVk->GetVkPhysicalDevice(), GetVkSurface(), &presentModeCount, nullptr);

    std::vector<VkPresentModeKHR> presentModesVk;
    presentModesVk.resize(presentModeCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(deviceVk->GetVkPhysicalDevice(), GetVkSurface(), &presentModeCount, presentModesVk.data());

    epiArray<gfxSurfacePresentMode> presentModes;
    for (const VkPresentModeKHR& presentModeVk : presentModesVk)
    {
        // TODO: replace with gfxSurfacePresentModeFrom
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

EPI_NAMESPACE_END()
