EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriver/gfxDriver.h"
#include "EpiGraphicsDriver/gfxDriver.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

#include "EpiGraphicsDriverVK/gfxDriverImplVK.h"
#include "EpiGraphicsDriverVK/gfxDeviceImplVK.h"

EPI_NAMESPACE_BEGIN()

gfxDriver& gfxDriver::GetInstance()
{
    static gfxDriver instance;
    return instance;
}

epiBool gfxDriver::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

void gfxDriver::Reset(const std::shared_ptr<internalgfx::gfxDriverImpl>& impl, gfxDriverBackend backend)
{
    m_Backend = backend;
    m_PhysicalDevices.Clear();
    m_GPUCrashTracker.Reset();
    m_Impl = impl;

    epiArray<gfxPhysicalDevice>& physicalDevices = GetPhysicalDevices();
    physicalDevices.Reserve(impl->GetPhysicalDevices().Size());

    // NOTE: filling gfxQueueFamily with their implementations (gfxDeviceImpl still owns these implementations)
    std::transform(impl->GetPhysicalDevices().begin(),
                   impl->GetPhysicalDevices().end(),
                   std::back_inserter(physicalDevices),
                   [](const std::shared_ptr<gfxPhysicalDevice::Impl>& physicalDeviceImpl)
    {
        return gfxPhysicalDevice(physicalDeviceImpl);
    });
}

void gfxDriver::SwitchBackend(gfxDriverBackend backend, const epiArray<gfxDriverExtension>& extensionsRequired)
{
    // TODO: should be called only from the main thread, add check

    gfxDriver& driver = gfxDriver::GetInstance();

    switch (backend)
    {
    case gfxDriverBackend::None: epiLogFatal("Can't use `gfxDriverBackend::None` as a gfx driver backend!"); break;
    case gfxDriverBackend::Vulkan:
    {
        // TODO: configure api version / app name properly
        std::shared_ptr<internalgfx::gfxDriverImplVK> impl = std::make_shared<internalgfx::gfxDriverImplVK>();
        if (impl->Init(1u, 2u, 162u, "EpiLab", extensionsRequired))
        {
            driver.Reset(std::move(impl), backend);
        }
    } break;
    default: epiLogFatal("Graphics Backend=`{}` isn't implemeted!", backend); break; // TODO: str repr
    }
}

std::optional<gfxSurface> gfxDriver::CreateSurface(const gfxWindow& window) const
{
    std::optional<gfxSurface> surface;

    if (std::shared_ptr<gfxSurface::Impl> surfaceImpl = m_Impl->CreateSurface(window))
    {
        surface = gfxSurface(surfaceImpl);
    }

    return surface;
}

std::optional<gfxDevice> gfxDriver::CreateDevice(const gfxDeviceCreateInfo& info) const
{
    std::optional<gfxDevice> device;

    if (std::shared_ptr<gfxDevice::Impl> impl = m_Impl->CreateDevice(info))
    {
        device = gfxDevice(std::move(impl));
    }

    return device;
}

epiBool gfxDriver::IsExtensionSupported(gfxDriverExtension extension) const
{
    return m_Impl->IsExtensionSupported(extension);
}

epiBool gfxDriver::IsExtensionEnabled(gfxDriverExtension extension) const
{
    return m_Impl->IsExtensionEnabled(extension);
}

EPI_NAMESPACE_END()
