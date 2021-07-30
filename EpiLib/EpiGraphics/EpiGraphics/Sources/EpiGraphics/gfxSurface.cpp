EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxSurface.h"
#include "EpiGraphics/gfxSurface.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

epiSize2u gfxSurfaceCapabilities::ClampExtent(const epiSize2u& extent) const
{
    epiSize2u extentClamped{};
    if (GetCurrentExtent().x != std::numeric_limits<epiU32>::max())
    {
        extentClamped = GetCurrentExtent();
    }
    else
    {
        extentClamped.x = std::clamp(extent.x, GetMinImageExtent().x, GetMaxImageExtent().x);
        extentClamped.y = std::clamp(extent.y, GetMinImageExtent().y, GetMaxImageExtent().y);
    }

    return extentClamped;
}

epiU32 gfxSurfaceCapabilities::RecommendedImageMinCount() const
{
    epiU32 imageCount = GetMinImageCount() + 1;
    if (const epiU32 maxImageCount = GetMaxImageCount(); maxImageCount > 0 && imageCount > maxImageCount)
    {
        imageCount = maxImageCount;
    }

    return imageCount;
}

epiBool operator==(const gfxSurfaceFormat& lhs, const gfxSurfaceFormat& rhs)
{
    return lhs.GetFormat() == rhs.GetFormat() && lhs.GetColorSpace() == rhs.GetColorSpace();
}

epiBool operator!=(const gfxSurfaceFormat& lhs, const gfxSurfaceFormat& rhs)
{
    return !(operator==(lhs, rhs));
}

gfxSurface::gfxSurface(const std::shared_ptr<Impl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxSurface::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

epiBool gfxSurface::IsCompatibleWith(const gfxPhysicalDevice& device, const gfxSurfaceFormat& format, gfxSurfacePresentMode presentMode) const
{
    if (!IsPresentSupportedFor(device))
    {
        epiLogWarn("PhysicalDevice=`{}` doesn't support desired surface!", device.ToString());
        return false;
    }

    const epiArray<gfxSurfaceFormat> supportedFormats = GetSupportedFormatsFor(device);
    if (supportedFormats.end() == std::find(supportedFormats.begin(), supportedFormats.end(), format))
    {
        epiLogWarn("PhysicalDevice=`{}` doesn't support desired SurfaceFormat=`{}`!", device.ToString(), format.ToString());
        return false;
    }

    const epiArray<gfxSurfacePresentMode> supportedPresentModes = GetSupportedPresentModesFor(device);
    if (supportedPresentModes.end() == std::find(supportedPresentModes.begin(), supportedPresentModes.end(), presentMode))
    {
        epiLogWarn("PhysicalDevice=`{}` doesn't support desired PresentMode=`{}`!", device.ToString(), presentMode); // TODO: str repr
        return false;
    }

    return true;
}

epiBool gfxSurface::IsPresentSupportedFor(const gfxPhysicalDevice& device) const
{
    if (!device.HasImpl())
    {
        epiLogError("Failed to query presentation support! The provided PhysicalDevice has no implementation!");
        return false;
    }

    return std::any_of(device.GetQueueFamilyDescriptors().begin(),
                       device.GetQueueFamilyDescriptors().end(),
                       [this, &device](const gfxQueueFamilyDescriptor& queueFamilyDesc)
    {
        return IsPresentSupportedFor(device, queueFamilyDesc);
    });
}

epiBool gfxSurface::IsPresentSupportedFor(const gfxPhysicalDevice& device, const gfxQueueFamily& queueFamily) const
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

    return m_Impl->IsPresentSupportedFor(device, queueFamily);
}

epiBool gfxSurface::IsPresentSupportedFor(const gfxPhysicalDevice& device, const gfxQueueFamilyDescriptor& queueFamilyDesc) const
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

    return m_Impl->IsPresentSupportedFor(device, queueFamilyDesc);
}

gfxSurfaceCapabilities gfxSurface::GetCapabilitiesFor(const gfxPhysicalDevice& device) const
{
    if (!device.HasImpl())
    {
        epiLogError("Failed to query SurfaceCapabilities! The provided PhysicalDevice has no implementation!");
        return {};
    }

    return m_Impl->GetCapabilitiesFor(device);
}

epiArray<gfxSurfaceFormat> gfxSurface::GetSupportedFormatsFor(const gfxPhysicalDevice& device) const
{
    if (!device.HasImpl())
    {
        epiLogError("Failed to query supported SurfaceFormats! The provided PhysicalDevice has no implementation!");
        return {};
    }

    return m_Impl->GetSupportedFormatsFor(device);
}

epiArray<gfxSurfacePresentMode> gfxSurface::GetSupportedPresentModesFor(const gfxPhysicalDevice& device) const
{
    if (!device.HasImpl())
    {
        epiLogError("Failed to query supported SurfacePresentModes! The provided PhysicalDevice has no implementation!");
        return {};
    }

    return m_Impl->GetSupportedPresentModesFor(device);
}

EPI_NAMESPACE_END()
