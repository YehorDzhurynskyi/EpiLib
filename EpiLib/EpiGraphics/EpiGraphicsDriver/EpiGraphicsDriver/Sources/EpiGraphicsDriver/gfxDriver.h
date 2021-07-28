#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriver/gfxDriver.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxPhysicalDevice.h"
#include "EpiGraphicsDriverCommon/gfxDevice.h"
#include "EpiGraphicsDriverCommon/gfxSurface.h"
#include "EpiGraphicsDriverCommon/gfxWindow.h"

#include "EpiGraphicsDriverCommon/gfxEnum.h"

#include "EpiGraphicsDriverCommon/Debug/gfxGPUCrashTracker.h"

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxDriverImpl;

} // namespace internalgfx

class gfxDriver : public Object
{
EPI_GENREGION_BEGIN(gfxDriver)

EPI_GENHIDDEN_gfxDriver()

public:
    constexpr static epiMetaTypeID TypeID{0xb00017ff};

    enum gfxDriver_PIDs
    {
        PID_Backend = 0x4058f0ed,
        PID_PhysicalDevices = 0x16b8cc07,
        PID_GPUCrashTracker = 0x5e835150,
        PID_COUNT = 3
    };

protected:
    gfxDriverBackend m_Backend{gfxDriverBackend::None};
    epiArray<gfxPhysicalDevice> m_PhysicalDevices{};
    gfxGPUCrashTracker m_GPUCrashTracker{};

EPI_GENREGION_END(gfxDriver)

public:
    static gfxDriver& GetInstance();

    static void SwitchBackend(gfxDriverBackend backend, const epiArray<gfxDriverExtension>& extensionsRequired);

public:
    std::optional<gfxSurface> CreateSurface(const gfxWindow& window) const;
    std::optional<gfxDevice> CreateDevice(const gfxDeviceCreateInfo& info) const;

    epiBool IsExtensionSupported(gfxDriverExtension extension) const;
    epiBool IsExtensionEnabled(gfxDriverExtension extension) const;

protected:
    gfxDriver() = default;
    gfxDriver(const gfxDriver& rhs) = delete;
    gfxDriver& operator=(const gfxDriver& rhs) = delete;
    gfxDriver(gfxDriver&& rhs) = delete;
    gfxDriver& operator=(gfxDriver&& rhs) = delete;

    epiBool HasImpl() const;

    void Reset(const std::shared_ptr<internalgfx::gfxDriverImpl>& impl, gfxDriverBackend backend);

protected:
    std::shared_ptr<internalgfx::gfxDriverImpl> m_Impl;
};

EPI_NAMESPACE_END()
