#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeries1Dc.hxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeriesc.h"

EPI_NAMESPACE_BEGIN()

class dSeries1Df;
class dSeries1Dc : public dSeriesc
{
EPI_GENREGION_BEGIN(dSeries1Dc)

EPI_GENHIDDEN_dSeries1Dc()

public:
    constexpr static epiMetaTypeID TypeID{0xf101428b};

    enum dSeries1Dc_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(dSeries1Dc)

public:
    dSeries1Dc() = default;
    dSeries1Dc(std::initializer_list<epiComplexf> list);

    dSeries1Df DFT_C2R() const;
    dSeries1Df DFT_C2R(epiSize_t N) const;

    dSeries1Df ToSeries1Df_Magnitude() const;
    dSeries1Df ToSeries1Df_Phase() const;
};

EPI_NAMESPACE_END()
