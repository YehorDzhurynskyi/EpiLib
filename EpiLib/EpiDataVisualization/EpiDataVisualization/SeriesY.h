#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/SeriesY.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class SeriesY : public Object
{
EPI_GENREGION_BEGIN(SeriesY)
public:
    EPI_GENHIDDEN_SeriesY()

    constexpr static MetaTypeID TypeID{0x4aed7335};

    enum SeriesY_PIDs
    {
        PID_COUNT = 0
    };

protected:

EPI_GENREGION_END(SeriesY)
};

EPI_NAMESPACE_END()
