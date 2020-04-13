#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/SeriesXY.hxx"
EPI_GENREGION_END(include)

#include "SeriesY.h"

EPI_NAMESPACE_BEGIN()

class SeriesXY : public SeriesY
{
EPI_GENREGION_BEGIN(SeriesXY)
public:
    EPI_GENHIDDEN_SeriesXY()

    constexpr static MetaTypeID TypeID{0x8f571ecc};

    enum SeriesXY_PIDs
    {
        PID_COUNT = 0
    };

protected:

EPI_GENREGION_END(SeriesXY)
};

EPI_NAMESPACE_END()
