EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriver/gfxDriver.h"
#include "EpiGraphicsDriver/gfxDriver.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsImplVK/gfxInstanceImplVK.h"

EPI_NAMESPACE_BEGIN()

gfxDriver& gfxDriver::Get()
{
    static gfxDriver instance;
    return instance;
}

void gfxDriver::SwitchBackend(gfxDriverBackend backend, const epiArray<gfxInstanceExtension>& extensionsRequired)
{
    // TODO: should be called only from the main thread, add check

    gfxDriver& driver = gfxDriver::Get();

    switch (backend)
    {
    case gfxDriverBackend::None: epiLogFatal("Can't use `gfxDriverBackend::None` as a gfx driver backend!"); break;
    case gfxDriverBackend::Vulkan:
    {
        // TODO: configure api version / app name properly
        std::shared_ptr<gfxInstanceImplVK> impl = std::make_shared<gfxInstanceImplVK>();
        if (impl->Init(1u, 2u, 162u, "EpiLab", extensionsRequired))
        {
            driver.Reset(std::move(gfxInstance(impl)), backend);
        }
    } break;
    default: epiLogFatal("Graphics Backend=`{}` isn't implemeted!", backend); break; // TODO: str repr
    }
}

void gfxDriver::Reset(gfxInstance&& instance, gfxDriverBackend backend)
{
    m_Backend = backend;
    m_GPUCrashTracker.Reset();
    m_Instance = std::move(instance);
}

EPI_NAMESPACE_END()
