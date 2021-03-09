#include "EpiGraphicsDriverVK/gfxSurfaceImplVK.h"

#include "EpiGraphicsDriverVK/gfxDriverImplVK.h"

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

VkSurfaceKHR gfxSurfaceImplVK::GetVkSurface() const
{
    return m_VkSurface;
}

} // namespace internalgfx

EPI_NAMESPACE_END()
