#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeriesXY.hxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeriesBase.h"

EPI_NAMESPACE_BEGIN()

class dSeriesXY : public dSeriesBase
{
EPI_GENREGION_BEGIN(dSeriesXY)

EPI_GENHIDDEN_dSeriesXY()

public:
    constexpr static MetaTypeID TypeID{0xdf305a3};

    enum dSeriesXY_PIDs
    {
        PID_X = 0xb7b2364b,
        PID_Y = 0xc0b506dd,
        PID_COUNT = 2
    };

protected:
    epiArray<epiFloat> m_X;
    epiArray<epiFloat> m_Y;

EPI_GENREGION_END(dSeriesXY)
};

EPI_NAMESPACE_END()
