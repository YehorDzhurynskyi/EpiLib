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
    case gfxDriverBackend::OpenGL:
    {

    } break;
    case gfxDriverBackend::Vulkan:
    {
        const epiS32 extensionMaskRequired = gfxDriverExtension_Surface | gfxDriverExtension_SurfaceWin32;
        // TODO: configure api version / app name properly
        internalgfx::gfxDriverImplVK* impl = new internalgfx::gfxDriverImplVK();
        impl->Init(1u, 0u, 0u, "EpiLab", static_cast<gfxDriverExtension>(extensionMaskRequired));

        m_Impl = impl;
    } break;
    case gfxDriverBackend::Software: epiLogFatal("Not implemeted!"); break;
    default: epiAssert(!"Unhandled case!");
    }

    m_Backend = backend;
}

gfxDriver::~gfxDriver()
{
    delete m_Impl;
}

std::unique_ptr<gfxSurface> gfxDriver::CreateSurface(const gfxWindow& window)
{
    std::unique_ptr<gfxSurface> surface;

    if (std::unique_ptr<internalgfx::gfxSurfaceImpl> surfaceImpl = m_Impl->CreateSurface(window))
    {
        surface = std::make_unique<gfxSurface>(surfaceImpl.release());
    }

    return surface;
}

std::optional<gfxPhysicalDevice> gfxDriver::FindAppropriatePhysicalDevice(std::function<epiBool(const gfxPhysicalDevice&)> isAppropiateCallback) const
{
    std::optional<gfxPhysicalDevice> device;

    if (std::unique_ptr<internalgfx::gfxPhysicalDeviceImpl> impl = m_Impl->FindAppropriatePhysicalDevice(isAppropiateCallback))
    {
        device = gfxPhysicalDevice(impl.release());
    }

    return device;
}

EPI_NAMESPACE_END()
