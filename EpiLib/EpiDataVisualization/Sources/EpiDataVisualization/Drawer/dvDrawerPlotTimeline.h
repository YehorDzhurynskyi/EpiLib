#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Drawer/dvDrawerPlotTimeline.hxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/ViewModel/dvViewModelPlot.h"
#include "EpiDataVisualization/Drawer/dvDrawerPlotDrawArea.h"

EPI_NAMESPACE_BEGIN()

class uiContext;
class dvDrawerPlotTimeline : public dvDrawerPlotDrawArea
{
EPI_GENREGION_BEGIN(dvDrawerPlotTimeline)

EPI_GENHIDDEN_dvDrawerPlotTimeline()

public:
    constexpr static epiMetaTypeID TypeID{0x639dda9b};

    enum dvDrawerPlotTimeline_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(dvDrawerPlotTimeline)

public:
    void Draw(gfxContext& ctx, const dvViewModelPlot& viewmodel, const epiRect2f& frame);
};

EPI_NAMESPACE_END()
