#pragma once

#include "EpiGraphics/gfxDriverInternal.h"

struct VkInstance_T;
struct VkSurfaceKHR_T;

EPI_NAMESPACE_BEGIN()

class gfxSurfaceImplVK : public gfxSurface::Impl
{
public:
    gfxSurfaceImplVK(VkInstance_T* instance, const gfxWindow& window);
    gfxSurfaceImplVK(const gfxSurfaceImplVK& rhs) = delete;
    gfxSurfaceImplVK& operator=(const gfxSurfaceImplVK& rhs) = delete;
    gfxSurfaceImplVK(gfxSurfaceImplVK&& rhs) = default;
    gfxSurfaceImplVK& operator=(gfxSurfaceImplVK&& rhs) = default;
    ~gfxSurfaceImplVK() override;

    epiBool IsPresentSupportedFor(const gfxPhysicalDevice& device, const gfxQueueFamily& queueFamily) const override;
    epiBool IsPresentSupportedFor(const gfxPhysicalDevice& device, const gfxQueueFamilyDescriptor& queueFamilyDesc) const override;
    gfxSurfaceCapabilities GetCapabilitiesFor(const gfxPhysicalDevice& device) const override;
    epiArray<gfxSurfaceFormat> GetSupportedFormatsFor(const gfxPhysicalDevice& device) const override;
    epiArray<gfxSurfacePresentMode> GetSupportedPresentModesFor(const gfxPhysicalDevice& device) const override;

    VkSurfaceKHR_T* GetVkSurface() const;

protected:
    VkInstance_T* m_VkInstance{nullptr};
    VkSurfaceKHR_T* m_VkSurface{nullptr};
};

EPI_NAMESPACE_END()
