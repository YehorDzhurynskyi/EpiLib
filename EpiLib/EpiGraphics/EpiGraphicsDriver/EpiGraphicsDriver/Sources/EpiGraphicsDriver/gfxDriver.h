#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriver/gfxDriver.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriver/gfxGPUCrashTracker.h"

#include "EpiGraphicsDriverCommon/gfxEnum.h"
#include "EpiGraphicsDriverCommon/gfxInstance.h"

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

enum class gfxDriverBackend : epiS32
{
EPI_GENREGION_BEGIN(gfxDriverBackend)
    None = -1,
    Null = 0,
    OpenGL = 1,
    Vulkan = 2,
    Software = 3,
    COUNT = 4
EPI_GENREGION_END(gfxDriverBackend)
};

class gfxDriver : public Object
{
EPI_GENREGION_BEGIN(gfxDriver)

EPI_GENHIDDEN_gfxDriver()

public:
    constexpr static epiMetaTypeID TypeID{0xb00017ff};

    enum gfxDriver_PIDs
    {
        PID_Backend = 0x4058f0ed,
        PID_GPUCrashTracker = 0x5e835150,
        PID_Instance = 0xbb46d388,
        PID_COUNT = 3
    };

protected:
    gfxDriverBackend m_Backend{gfxDriverBackend::None};
    gfxGPUCrashTracker m_GPUCrashTracker{};
    gfxInstance m_Instance{};

EPI_GENREGION_END(gfxDriver)

public:
    static gfxDriver& Get();

    static void SwitchBackend(gfxDriverBackend backend, const epiArray<gfxInstanceExtension>& extensionsRequired);

protected:
    gfxDriver() = default;
    gfxDriver(const gfxDriver& rhs) = delete;
    gfxDriver& operator=(const gfxDriver& rhs) = delete;
    gfxDriver(gfxDriver&& rhs) = delete;
    gfxDriver& operator=(gfxDriver&& rhs) = delete;

    void Reset(gfxInstance&& instance, gfxDriverBackend backend);
};

EPI_NAMESPACE_END()
