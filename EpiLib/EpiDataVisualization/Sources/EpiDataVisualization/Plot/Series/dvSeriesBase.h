#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Plot/Series/dvSeriesBase.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class dvSeriesBase : public Object
{
EPI_GENREGION_BEGIN(dvSeriesBase)

EPI_GENHIDDEN_dvSeriesBase()

public:
    constexpr static MetaTypeID TypeID{0x5513e566};

    enum dvSeriesBase_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(dvSeriesBase)
};

EPI_NAMESPACE_END()
