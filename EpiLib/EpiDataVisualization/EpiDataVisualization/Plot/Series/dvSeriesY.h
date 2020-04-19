#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Plot/Series/dvSeriesY.hxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/Plot/Series/dvSeriesBase.h"

EPI_NAMESPACE_BEGIN()

class dvSeriesY : public dvSeriesBase
{
EPI_GENREGION_BEGIN(dvSeriesY)
public:
    EPI_GENHIDDEN_dvSeriesY()

    constexpr static MetaTypeID TypeID{0x5a38f05a};

    enum dvSeriesY_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(dvSeriesY)
};

EPI_NAMESPACE_END()
