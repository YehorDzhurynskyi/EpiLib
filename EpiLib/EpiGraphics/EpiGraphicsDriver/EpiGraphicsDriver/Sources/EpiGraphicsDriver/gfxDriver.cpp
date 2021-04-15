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

void gfxDriver::SetBackend_Callback(gfxDriverBackend backend)
{
    // TODO: should be called only from the main thread, add check

    delete m_Impl;

    switch (backend)
    {
    case gfxDriverBackend::None: epiLogFatal("Can't use `gfxDriverBackend::None` as a gfx driver backend!"); break;
    case gfxDriverBackend::Vulkan:
    {
        // TODO: move required extensions as a parameter
        epiArray<gfxDriverExtension> extensionsRequired;
        extensionsRequired.push_back(gfxDriverExtension::Surface);

#ifdef EPI_PLATFORM_WINDOWS
        extensionsRequired.push_back(gfxDriverExtension::SurfaceWin32);
#endif // EPI_PLATFORM_WINDOWS

        // TODO: configure api version / app name properly
        internalgfx::gfxDriverImplVK* impl = new internalgfx::gfxDriverImplVK();
        if (impl->Init(1u, 2u, 162u, "EpiLab", extensionsRequired))
        {
            m_Impl = impl;
            m_Backend = backend;
        }
    } break;
    default: epiLogFatal("Graphics Backend=`{}` isn't implemeted!", backend); break; // TODO: str repr
    }
}

gfxDriver::~gfxDriver()
{
    delete m_Impl;
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

std::optional<gfxPhysicalDevice> gfxDriver::FindAppropriatePhysicalDevice(std::function<epiBool(const gfxPhysicalDevice&)> isAppropiateCallback) const
{
    std::optional<gfxPhysicalDevice> device;

    if (m_Impl == nullptr)
    {
        epiLogError("Failed to create Surface! Driver has no assigned backend!");
        return device;
    }

    if (std::unique_ptr<internalgfx::gfxPhysicalDeviceImpl> impl = m_Impl->FindAppropriatePhysicalDevice(isAppropiateCallback))
    {
        device = gfxPhysicalDevice(impl.release());
    }

    return device;
}

EPI_NAMESPACE_END()
