#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Plot/Drawer/dvDrawerPlotTimeline.hxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/Plot/ViewModel/dvVMPlot.h"
#include "EpiDataVisualization/Plot/Drawer/dvDrawerPlotDrawArea.h"

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
    void Draw(drwContext& ctx, const dvVMPlot& viewmodel, const epiRect2f& frame);
};

EPI_NAMESPACE_END()
