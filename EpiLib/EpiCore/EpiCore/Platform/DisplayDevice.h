#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiCore/Platform/DisplayDevice.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class DisplayDevice : public Object
{
EPI_GENREGION_BEGIN(DisplayDevice)
public:
    EPI_GENHIDDEN_DisplayDevice()

    constexpr static MetaTypeID TypeID{0x36950f3a};

    enum DisplayDevice_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(DisplayDevice)

public:
    // TODO: refactor
    static epiVec2u DPI();
};

EPI_NAMESPACE_END()
