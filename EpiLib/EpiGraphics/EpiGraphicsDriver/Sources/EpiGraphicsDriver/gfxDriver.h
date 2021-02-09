#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriver/gfxDriver.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriver/gfxPhysicalDevice.h"

#include "EpiGraphicsEnum/EpiGraphicsEnum.h"

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
        PID_COUNT = 2
    };

protected:
    void SetBackend_Callback(gfxDriverBackend value);

protected:
    gfxDriverBackend m_Backend{};
    epiArray<gfxPhysicalDevice> m_PhysicalDevices{};

EPI_GENREGION_END(gfxDriver)

public:
    static gfxDriver& GetInstance();

public:
    gfxDriver(const gfxDriver& rhs) = delete;
    gfxDriver& operator=(const gfxDriver& rhs) = delete;
    gfxDriver(gfxDriver&& rhs) = delete;
    gfxDriver& operator=(gfxDriver&& rhs) = delete;
    ~gfxDriver();

protected:
    gfxDriver() = default;

protected:
    internalgfx::gfxDriverImpl* m_Impl{nullptr};
};

EPI_NAMESPACE_END()
