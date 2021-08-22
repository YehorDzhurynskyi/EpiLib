EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxInstance.h"
#include "EpiGraphics/gfxInstance.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsImpl/gfxInstanceImpl.h"

EPI_NAMESPACE_BEGIN()

gfxInstance::gfxInstance(const std::shared_ptr<Impl>& impl)
    : m_Impl{impl}
{
    epiArray<gfxPhysicalDevice>& physicalDevices = GetPhysicalDevices();
    physicalDevices.Reserve(m_Impl->GetPhysicalDevices().Size());

    // NOTE: filling gfxQueueFamily with their implementations (gfxDeviceImpl still owns these implementations)
    std::transform(m_Impl->GetPhysicalDevices().begin(),
                   m_Impl->GetPhysicalDevices().end(),
                   std::back_inserter(physicalDevices),
                   [](const std::shared_ptr<gfxPhysicalDevice::Impl>& physicalDeviceImpl)
    {
        return gfxPhysicalDevice(physicalDeviceImpl);
    });
}

epiBool gfxInstance::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

std::optional<gfxSurface> gfxInstance::CreateSurface(const gfxWindow& window) const
{
    std::optional<gfxSurface> surface;

    if (std::shared_ptr<gfxSurface::Impl> surfaceImpl = m_Impl->CreateSurface(window))
    {
        surface = gfxSurface(surfaceImpl);
    }

    return surface;
}

epiBool gfxInstance::IsExtensionSupported(gfxInstanceExtension extension) const
{
    return m_Impl->IsExtensionSupported(extension);
}

epiBool gfxInstance::IsExtensionEnabled(gfxInstanceExtension extension) const
{
    return m_Impl->IsExtensionEnabled(extension);
}

EPI_NAMESPACE_END()
