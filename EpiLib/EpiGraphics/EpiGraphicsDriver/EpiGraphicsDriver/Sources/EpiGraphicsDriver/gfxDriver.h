#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriver/gfxDriver.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxPhysicalDevice.h"
#include "EpiGraphicsDriverCommon/gfxSurface.h"
#include "EpiGraphicsDriverCommon/gfxWindow.h"

#include "EpiGraphicsDriverCommon/gfxEnum.h"

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxDriverImpl;

} // namespace internalgfx

class gfxDriver : public Object, public epiPimpl<internalgfx::gfxDriverImpl>
{
EPI_GENREGION_BEGIN(gfxDriver)

EPI_GENHIDDEN_gfxDriver()

public:
    constexpr static epiMetaTypeID TypeID{0xb00017ff};

    enum gfxDriver_PIDs
    {
        PID_Backend = 0x4058f0ed,
        PID_PhysicalDevices = 0x16b8cc07,
        PID_COUNT = 2
    };

protected:
    gfxDriverBackend m_Backend{gfxDriverBackend::None};
    epiArray<gfxPhysicalDevice> m_PhysicalDevices{};

EPI_GENREGION_END(gfxDriver)

public:
    static gfxDriver& GetInstance();

    static void SwitchBackend(gfxDriverBackend backend, const epiArray<gfxDriverExtension>& extensionsRequired);

public:
    std::optional<gfxSurface> CreateSurface(const gfxWindow& window);

protected:
    gfxDriver() = default;
    gfxDriver(internalgfx::gfxDriverImpl* impl, gfxDriverBackend backend);

    void Reset();
};

EPI_NAMESPACE_END()
