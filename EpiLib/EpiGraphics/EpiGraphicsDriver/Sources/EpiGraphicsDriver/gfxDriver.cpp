#include "EpiGraphicsDriver/gfxDriver.h"

#include "EpiGraphicsDriverVK/gfxDriverImplVK.h"

EPI_NAMESPACE_BEGIN()

gfxDriver& gfxDriver::GetInstance()
{
    static gfxDriver instance;
    return instance;
}

void gfxDriver::ChangeDriverBackend(gfxDriverBackend backend)
{
    // TODO: should be called only from the main thread, add check

    delete m_DriverImpl;

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
        m_DriverImpl = new internalgfx::gfxDriverImplVK(1u, 0u, 0u, "EpiLab", static_cast<gfxDriverExtension>(extensionMaskRequired));
    } break;
    case gfxDriverBackend::Software: epiLogFatal("Not implemeted!"); break;
    default: epiAssert(!"Unhandled case!");
    }

    m_Backend = backend;
}

gfxDriver::~gfxDriver()
{
    delete m_DriverImpl;
}

EPI_NAMESPACE_END()
