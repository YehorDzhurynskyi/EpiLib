#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiCore/Platform/DisplayDevice.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

enum class DPIAwareness : epiS32
{
EPI_GENREGION_BEGIN(DPIAwareness)
    UnAware = 0,
    SystemAware = 1,
    PerMonitorAware = 2
EPI_GENREGION_END(DPIAwareness)
};

class DisplayDevice : public Object
{
EPI_GENREGION_BEGIN(DisplayDevice)

EPI_GENHIDDEN_DisplayDevice()

public:
    constexpr static epiMetaTypeID TypeID{0x36950f3a};

    enum DisplayDevice_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(DisplayDevice)

public:
    // TODO: refactor
    static epiVec2u DPI();
    static void SetDPIAwareness(DPIAwareness awareness);
};

EPI_NAMESPACE_END()
