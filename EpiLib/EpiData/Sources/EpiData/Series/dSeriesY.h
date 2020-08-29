#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeriesY.hxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeriesBase.h"

EPI_NAMESPACE_BEGIN()

class dSeriesY : public dSeriesBase
{
EPI_GENREGION_BEGIN(dSeriesY)

EPI_GENHIDDEN_dSeriesY()

public:
    constexpr static MetaTypeID TypeID{0xe602dd63};

    enum dSeriesY_PIDs
    {
        PID_XStep = 0xc8efd09,
        PID_Y = 0xc0b506dd,
        PID_COUNT = 2
    };

protected:
    epiFloat m_XStep{0.0f};
    epiArray<epiFloat> m_Y;

EPI_GENREGION_END(dSeriesY)
};

EPI_NAMESPACE_END()
