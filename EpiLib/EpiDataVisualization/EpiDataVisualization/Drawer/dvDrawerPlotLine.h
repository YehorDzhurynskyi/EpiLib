#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Drawer/dvDrawerPlotLine.hxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/Drawer/dvDrawerPlotBase.h"

EPI_NAMESPACE_BEGIN()

class dvDrawerPlotLine : public dvDrawerPlotBase
{
EPI_GENREGION_BEGIN(dvDrawerPlotLine)
public:
    EPI_GENHIDDEN_dvDrawerPlotLine()

    constexpr static MetaTypeID TypeID{0x96079c5d};

    enum dvDrawerPlotLine_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(dvDrawerPlotLine)
};

EPI_NAMESPACE_END()
