#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Drawer/dvDrawerPlotRealtime.hxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/Drawer/dvDrawerPlot.h"

EPI_NAMESPACE_BEGIN()

class dvDrawerPlotRealtime : public dvDrawerPlot
{
EPI_GENREGION_BEGIN(dvDrawerPlotRealtime)
public:
    EPI_GENHIDDEN_dvDrawerPlotRealtime()

    constexpr static MetaTypeID TypeID{0xa60037d1};

    enum dvDrawerPlotRealtime_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(dvDrawerPlotRealtime)

protected:
    void Draw_Internal(uiContext& uiContext, const dvViewModelPlot& plot, const epiRect2f& frame) override;
};

EPI_NAMESPACE_END()
