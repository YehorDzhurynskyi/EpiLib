#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/DrawerPlotLine.hxx"
EPI_GENREGION_END(include)

#include "DrawerPlotBase.h"

EPI_NAMESPACE_BEGIN()

class DrawerPlotLine : public DrawerPlotBase
{
EPI_GENREGION_BEGIN(DrawerPlotLine)
public:
    EPI_GENHIDDEN_DrawerPlotLine()

    constexpr static MetaTypeID TypeID{0x62d16191};

    enum DrawerPlotLine_PIDs
    {
        PID_COUNT = 0
    };

protected:

EPI_GENREGION_END(DrawerPlotLine)
};

EPI_NAMESPACE_END()
