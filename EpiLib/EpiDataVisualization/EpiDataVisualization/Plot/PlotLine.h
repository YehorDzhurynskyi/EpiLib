#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Plot/PlotLine.hxx"
EPI_GENREGION_END(include)

#include "PlotBase.h"

EPI_NAMESPACE_BEGIN()

class PlotLine : public PlotBase
{
EPI_GENREGION_BEGIN(PlotLine)
public:
    EPI_GENHIDDEN_PlotLine()

    constexpr static MetaTypeID TypeID{0xd980356a};

    enum PlotLine_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(PlotLine)
};

EPI_NAMESPACE_END()
