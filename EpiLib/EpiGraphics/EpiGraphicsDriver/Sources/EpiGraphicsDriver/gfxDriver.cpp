EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriver/gfxDriver.h"
#include "EpiGraphicsDriver/gfxDriver.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverImpl/EpiGraphicsDriverImpl.h"

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
        m_Impl = new internalgfx::gfxDriverImplVK(1u, 0u, 0u, "EpiLab", static_cast<gfxDriverExtension>(extensionMaskRequired));
    } break;
    case gfxDriverBackend::Software: epiLogFatal("Not implemeted!"); break;
    default: epiAssert(!"Unhandled case!");
    }

    m_Backend = backend;

    m_PhysicalDevices.Clear();
    const epiPtrArray<internalgfx::gfxPhysicalDeviceImpl>& physicalDevicesImpl = m_Impl->GetPhysicalDevices();
    m_PhysicalDevices.Reserve(physicalDevicesImpl.Size());

    for (const auto& devImpl : physicalDevicesImpl)
    {
        gfxPhysicalDevice dev(devImpl);
        m_PhysicalDevices.push_back(std::move(dev));
    }
}

gfxDriver::~gfxDriver()
{
    delete m_Impl;
}

EPI_NAMESPACE_END()
