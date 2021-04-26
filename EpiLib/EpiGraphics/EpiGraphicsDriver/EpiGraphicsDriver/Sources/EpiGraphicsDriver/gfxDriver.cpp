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

gfxDriver::gfxDriver(internalgfx::gfxDriverImpl* impl, gfxDriverBackend backend)
    : epiPimpl<internalgfx::gfxDriverImpl>{impl}
    , m_Backend{backend}
{
    epiArray<gfxPhysicalDevice>& physicalDevices = GetPhysicalDevices();
    physicalDevices.Reserve(impl->GetPhysicalDevices().Size());

    // NOTE: filling gfxQueueFamily with their implementations (gfxDeviceImpl still owns these implementations)
    std::transform(impl->GetPhysicalDevices().begin(),
                   impl->GetPhysicalDevices().end(),
                   std::back_inserter(physicalDevices),
                   [](std::unique_ptr<internalgfx::gfxPhysicalDeviceImpl>& physicalDeviceImpl)
    {
        return gfxPhysicalDevice(physicalDeviceImpl.get());
    });

}

void gfxDriver::Reset()
{
    m_PhysicalDevices.Clear();
    m_Backend = gfxDriverBackend::None;
    delete m_Impl;
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
        driver.Reset();

        // TODO: configure api version / app name properly
        std::unique_ptr<internalgfx::gfxDriverImplVK> impl = std::make_unique<internalgfx::gfxDriverImplVK>();
        if (impl->Init(1u, 2u, 162u, "EpiLab", extensionsRequired))
        {
            driver = gfxDriver(impl.release(), backend);
        }
    } break;
    default: epiLogFatal("Graphics Backend=`{}` isn't implemeted!", backend); break; // TODO: str repr
    }
}

std::optional<gfxSurface> gfxDriver::CreateSurface(const gfxWindow& window)
{
    std::optional<gfxSurface> surface;

    if (m_Impl == nullptr)
    {
        epiLogError("Failed to create Surface! Driver has no assigned backend!");
        return surface;
    }

    if (std::unique_ptr<internalgfx::gfxSurfaceImpl> surfaceImpl = m_Impl->CreateSurface(window))
    {
        surface = gfxSurface(surfaceImpl.release());
    }

    return surface;
}

EPI_NAMESPACE_END()
