#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/DrawerPlotBase.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class DrawerPlotBase : public Object
{
EPI_GENREGION_BEGIN(DrawerPlotBase)
public:
    EPI_GENHIDDEN_DrawerPlotBase()

    constexpr static MetaTypeID TypeID{0x73712b06};

    enum DrawerPlotBase_PIDs
    {
        PID_COUNT = 0
    };

protected:

EPI_GENREGION_END(DrawerPlotBase)
};

EPI_NAMESPACE_END()
