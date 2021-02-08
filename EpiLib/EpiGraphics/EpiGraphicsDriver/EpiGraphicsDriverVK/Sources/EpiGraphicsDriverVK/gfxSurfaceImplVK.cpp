#include "EpiGraphicsDriverVK/gfxSurfaceImplVK.h"

#include "EpiGraphicsDriverVK/gfxDriverImplVK.h"

#ifdef EPI_PLATFORM_WINDOWS
#include <windows.h>
#include <vulkan/vulkan_win32.h>
#endif // EPI_PLATFORM_WINDOWS

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxSurfaceImplVK::gfxSurfaceImplVK(VkInstance intance)
    : m_VkInstance{intance}
{
    VkWin32SurfaceCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    createInfo.hwnd = GetActiveWindow(); // TODO: make possible to create surface for any Window even non-active
    createInfo.hinstance = GetModuleHandle(nullptr);

    VkResult resultCreateWin32SurfaceKHR = vkCreateWin32SurfaceKHR(m_VkInstance, &createInfo, nullptr, &m_VkSurface);
    epiAssert(resultCreateWin32SurfaceKHR == VK_SUCCESS);
}

gfxSurfaceImplVK::~gfxSurfaceImplVK()
{
    epiAssert(m_VkInstance != VK_NULL_HANDLE);

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
