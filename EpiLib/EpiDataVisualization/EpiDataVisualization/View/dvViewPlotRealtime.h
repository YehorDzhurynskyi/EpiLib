#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/View/dvViewPlotRealtime.hxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/View/dvViewPlot.h"

EPI_NAMESPACE_BEGIN()

class dvViewPlotRealtime : public dvViewPlot
{
EPI_GENREGION_BEGIN(dvViewPlotRealtime)
public:
    EPI_GENHIDDEN_dvViewPlotRealtime()

    constexpr static MetaTypeID TypeID{0xdca4c430};

    enum dvViewPlotRealtime_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(dvViewPlotRealtime)
};

EPI_NAMESPACE_END()
