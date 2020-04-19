#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Drawer/dvDrawerPlotBase.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxDrawer.h"

EPI_NAMESPACE_BEGIN()

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
};

EPI_NAMESPACE_END()
