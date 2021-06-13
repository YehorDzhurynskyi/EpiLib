#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeriesBase.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

enum class dSeriesAddressMode : epiS32
{
EPI_GENREGION_BEGIN(dSeriesAddressMode)
    Error = 0,
    Zero = 1,
    One = 2,
    FF = 3,
    Nearest = 4,
    Wrap = 5,
    Reflect = 6,
    Mirror = 7
EPI_GENREGION_END(dSeriesAddressMode)
};

class dSeriesBase : public Object
{
EPI_GENREGION_BEGIN(dSeriesBase)

EPI_GENHIDDEN_dSeriesBase()

public:
    constexpr static epiMetaTypeID TypeID{0x988fb898};

    enum dSeriesBase_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(dSeriesBase)
};

EPI_NAMESPACE_END()
