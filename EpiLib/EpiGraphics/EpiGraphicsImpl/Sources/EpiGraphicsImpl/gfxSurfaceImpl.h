#pragma once

#include "EpiGraphics/gfxSurface.h"

EPI_NAMESPACE_BEGIN()

class gfxSurface::Impl
{
public:
    static const gfxSurface::Impl* ExtractImpl(const gfxSurface& surface) { return surface.m_Impl.get(); }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    virtual epiBool IsPresentSupportedFor(const gfxPhysicalDevice& device, const gfxQueueFamily& queueFamily) const = 0;
    virtual epiBool IsPresentSupportedFor(const gfxPhysicalDevice& device, const gfxQueueFamilyDescriptor& queueFamilyDesc) const = 0;
    virtual gfxSurfaceCapabilities GetCapabilitiesFor(const gfxPhysicalDevice& device) const = 0;
    virtual epiArray<gfxSurfaceFormat> GetSupportedFormatsFor(const gfxPhysicalDevice& device) const = 0;
    virtual epiArray<gfxSurfacePresentMode> GetSupportedPresentModesFor(const gfxPhysicalDevice& device) const = 0;
};

EPI_NAMESPACE_END()
