EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxSurface.h"
#include "EpiGraphicsDriverCommon/gfxSurface.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

epiBool operator==(const gfxSurfaceFormat& lhs, const gfxSurfaceFormat& rhs)
{
    return lhs.GetFormat() == rhs.GetFormat() && lhs.GetColorSpace() == rhs.GetColorSpace();
}

epiBool operator!=(const gfxSurfaceFormat& lhs, const gfxSurfaceFormat& rhs)
{
    return !(operator==(lhs, rhs));
}

gfxSurface::gfxSurface(const std::shared_ptr<internalgfx::gfxSurfaceImpl>& impl)
    : m_Impl{impl}
{
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
    return m_Impl->IsPresentSupportedFor(*device.m_Impl);
}

epiBool gfxSurface::IsPresentSupportedFor(const gfxPhysicalDevice& device, const gfxQueueFamily& queueFamily) const
{
    return m_Impl->IsPresentSupportedFor(*device.m_Impl, *queueFamily.m_Impl);
}

epiBool gfxSurface::IsPresentSupportedFor(const gfxPhysicalDevice& device, const gfxQueueFamilyDescriptor& queueFamilyDesc) const
{
    return m_Impl->IsPresentSupportedFor(*device.m_Impl, *queueFamilyDesc.m_Impl);
}

gfxSurfaceCapabilities gfxSurface::GetCapabilitiesFor(const gfxPhysicalDevice& device) const
{
    return m_Impl->GetCapabilitiesFor(*device.m_Impl);
}

epiArray<gfxSurfaceFormat> gfxSurface::GetSupportedFormatsFor(const gfxPhysicalDevice& device) const
{
    return m_Impl->GetSupportedFormatsFor(*device.m_Impl);
}

epiArray<gfxSurfacePresentMode> gfxSurface::GetSupportedPresentModesFor(const gfxPhysicalDevice& device) const
{
    return m_Impl->GetSupportedPresentModesFor(*device.m_Impl);
}

EPI_NAMESPACE_END()
