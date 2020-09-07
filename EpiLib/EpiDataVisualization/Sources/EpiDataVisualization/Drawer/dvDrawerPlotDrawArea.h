#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Drawer/dvDrawerPlotDrawArea.hxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/ViewModel/dvViewModelPlot.h"

#include "EpiGraphics/gfxContext.h"
#include "EpiGraphics/gfxDrawer.h"

EPI_NAMESPACE_BEGIN()

class dvDrawerPlotDrawArea : public gfxDrawer
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
    void Draw(gfxContext& ctx, const dvViewModelPlot& plot, const epiRect2f& frame);

protected:
    void GridMarkup(epiFloat domain, epiFloat& outStep, epiU32& outNLines);
};

EPI_NAMESPACE_END()
