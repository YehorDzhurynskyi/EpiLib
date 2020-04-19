#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Plot/dvPlotBase.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class dvPlotBase : public Object
{
EPI_GENREGION_BEGIN(dvPlotBase)
public:
    EPI_GENHIDDEN_dvPlotBase()

    constexpr static MetaTypeID TypeID{0x153dd6b7};

    enum dvPlotBase_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(dvPlotBase)
};

EPI_NAMESPACE_END()
