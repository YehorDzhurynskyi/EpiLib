#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Drawer/dvDrawerPlotBase.hxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/ViewModel/dvViewModelPlotBase.h"
#include "EpiGraphics/gfxDrawer.h"

EPI_NAMESPACE_BEGIN()

class gfxDrawerPrimitive;
class gfxDrawerText;
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
    dvDrawerPlotBase(const gfxCamera& camera);

public:
    void Draw(const dvViewModelPlotBase& plot, gfxDrawerPrimitive& drawerPrimitive, gfxDrawerText& drawerText);

protected:
    virtual void Draw_Internal(const dvViewModelPlotBase& plot, gfxDrawerPrimitive& drawerPrimitive, gfxDrawerText& drawerText);
};

EPI_NAMESPACE_END()
