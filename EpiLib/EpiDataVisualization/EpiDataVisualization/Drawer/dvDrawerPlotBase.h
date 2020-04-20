#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Drawer/dvDrawerPlotBase.hxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/Plot/dvPlotBase.h"
#include "EpiGraphics/gfxDrawer.h"

EPI_NAMESPACE_BEGIN()

class gfxDrawerPrimitive;
class dvDrawerPlotBase : public gfxDrawer
{
EPI_GENREGION_BEGIN(dvDrawerPlotBase)
public:
    EPI_GENHIDDEN_dvDrawerPlotBase()

    constexpr static MetaTypeID TypeID{0x87a7d6ca};

    enum dvDrawerPlotBase_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(dvDrawerPlotBase)

public:
    void Draw(const dvPlotBase& plot, gfxDrawerPrimitive& drawerPrimitive);

protected:
    virtual void Draw_Internal(const dvPlotBase& plot, gfxDrawerPrimitive& drawerPrimitive);
};

EPI_NAMESPACE_END()
