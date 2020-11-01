#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeries1Df.hxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeriesf.h"

EPI_NAMESPACE_BEGIN()

class dSeries1Dc;
class dSeries1Df : public dSeriesf
{
EPI_GENREGION_BEGIN(dSeries1Df)

EPI_GENHIDDEN_dSeries1Df()

public:
    constexpr static epiMetaTypeID TypeID{0x816bb604};

    enum dSeries1Df_PIDs
    {
        PID_BoundLeft = 0x4ab5a59,
        PID_BoundRight = 0xe56ab993,
        PID_COUNT = 2
    };

protected:
    epiFloat GetBoundRight_Callback() const;

protected:
    epiFloat m_BoundLeft{0.0f};

EPI_GENREGION_END(dSeries1Df)

public:
    dSeries1Df() = default;
    dSeries1Df(std::initializer_list<epiFloat> list);

    dSeries1Dc DFT_R2C() const;
};

EPI_NAMESPACE_END()
