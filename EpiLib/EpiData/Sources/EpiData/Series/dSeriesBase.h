#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeriesBase.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class dSeriesBase : public Object
{
EPI_GENREGION_BEGIN(dSeriesBase)

EPI_GENHIDDEN_dSeriesBase()

public:
    constexpr static MetaTypeID TypeID{0x988fb898};

    enum dSeriesBase_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(dSeriesBase)
};

EPI_NAMESPACE_END()
