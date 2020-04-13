#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/PlotBase.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class PlotBase : public Object
{
EPI_GENREGION_BEGIN(PlotBase)
public:
    EPI_GENHIDDEN_PlotBase()

    constexpr static MetaTypeID TypeID{0xc8207ffd};

    enum PlotBase_PIDs
    {
        PID_COUNT = 0
    };

protected:

EPI_GENREGION_END(PlotBase)
};

EPI_NAMESPACE_END()
