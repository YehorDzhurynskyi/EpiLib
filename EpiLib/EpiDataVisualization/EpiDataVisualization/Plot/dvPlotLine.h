#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Plot/dvPlotLine.hxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/Plot/dvPlotBase.h"

EPI_NAMESPACE_BEGIN()

class dvPlotLine : public dvPlotBase
{
EPI_GENREGION_BEGIN(dvPlotLine)
public:
    EPI_GENHIDDEN_dvPlotLine()

    constexpr static MetaTypeID TypeID{0x49d9c20};

    enum dvPlotLine_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(dvPlotLine)
};

EPI_NAMESPACE_END()
