#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Plot/Drawer/dvDrawerPlotDrawArea.hxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/Plot/ViewModel/dvVMPlot.h"

#include "EpiDrawer/drwContext.h"
#include "EpiDrawer/drwDrawer.h"

EPI_NAMESPACE_BEGIN()

class dvDrawerPlotDrawArea : public drwDrawer
{
EPI_GENREGION_BEGIN(dvDrawerPlotDrawArea)

EPI_GENHIDDEN_dvDrawerPlotDrawArea()

public:
    constexpr static epiMetaTypeID TypeID{0xb1af01bd};

    enum dvDrawerPlotDrawArea_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(dvDrawerPlotDrawArea)

public:
    void Draw(drwContext& ctx, const dvVMPlot& plot, const epiRect2f& frame);

protected:
    void GridMarkup(epiFloat domain, epiFloat& outStep, epiU32& outNLines);
};

EPI_NAMESPACE_END()
