#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Drawer/dvDrawerPlot.hxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/View/dvViewPlot.h"

#include "EpiUI/uiContext.h"

#include "EpiGraphics/gfxDrawer.h"

EPI_NAMESPACE_BEGIN()

class gfxDrawerPrimitive;
class gfxDrawerText;
class dvDrawerPlot : public gfxDrawer
{
EPI_GENREGION_BEGIN(dvDrawerPlot)
public:
    EPI_GENHIDDEN_dvDrawerPlot()

    constexpr static MetaTypeID TypeID{0xde7ad94c};

    enum dvDrawerPlot_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(dvDrawerPlot)

public:
    void Draw(uiContext& uiContext, const dvViewModelPlot& plot);

protected:
    virtual void Draw_Internal(uiContext& uiContext, const dvViewModelPlot& plot);
};

EPI_NAMESPACE_END()
