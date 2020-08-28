#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Plot/Series/dvSeriesXY.hxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/Plot/Series/dvSeriesBase.h"

EPI_NAMESPACE_BEGIN()

class dvSeriesXY : public dvSeriesBase
{
EPI_GENREGION_BEGIN(dvSeriesXY)

EPI_GENHIDDEN_dvSeriesXY()

public:
    constexpr static MetaTypeID TypeID{0x524ab786};

    enum dvSeriesXY_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(dvSeriesXY)
};

EPI_NAMESPACE_END()
