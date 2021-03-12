#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

struct VkSurfaceKHR_T;
struct VkInstance_T;

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxSurfaceImplVK : public gfxSurfaceImpl
{
public:
    gfxSurfaceImplVK(VkInstance_T* instance, const gfxWindow& window);
    gfxSurfaceImplVK(const gfxSurfaceImplVK& rhs) = delete;
    gfxSurfaceImplVK& operator=(const gfxSurfaceImplVK& rhs) = delete;
    gfxSurfaceImplVK(gfxSurfaceImplVK&& rhs) = default;
    gfxSurfaceImplVK& operator=(gfxSurfaceImplVK&& rhs) = default;
    ~gfxSurfaceImplVK() override;

    epiBool IsPresentSupportedFor(const gfxPhysicalDeviceImpl& device) const;
    epiBool IsPresentSupportedFor(const gfxPhysicalDeviceImpl& device, const gfxQueueFamilyImpl& queueFamily) const;
    gfxSurfaceCapabilities GetCapabilitiesFor(const gfxPhysicalDeviceImpl& device) const;
    epiArray<gfxSurfaceFormat> GetSupportedFormatsFor(const gfxPhysicalDeviceImpl& device) const;
    epiArray<gfxSurfacePresentMode> GetSupportedPresentModesFor(const gfxPhysicalDeviceImpl& device) const;

    VkSurfaceKHR_T* GetVkSurface() const;

protected:
    VkInstance_T* m_VkInstance{nullptr};
    VkSurfaceKHR_T* m_VkSurface{nullptr};
};

} // namespace internalgfx

EPI_NAMESPACE_END()
