#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeries2Dc.hxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeriesc.h"

EPI_NAMESPACE_BEGIN()

class dSeries2Df;
class dSeries2Dc : public dSeriesc
{
EPI_GENREGION_BEGIN(dSeries2Dc)

EPI_GENHIDDEN_dSeries2Dc()

public:
    constexpr static epiMetaTypeID TypeID{0xf347fcd2};

    enum dSeries2Dc_PIDs
    {
        PID_Height = 0xf2e1e039,
        PID_Width = 0x4ddb6a2b,
        PID_COUNT = 2
    };

protected:
    epiSize_t GetHeight_Callback() const;

protected:
    epiSize_t m_Width{0};

EPI_GENREGION_END(dSeries2Dc)

public:
    dSeries2Dc() = default;
    dSeries2Dc(std::initializer_list<epiComplexf> list, epiSize_t width);

    dSeries2Df DFT_C2R() const;
    dSeries2Df DFT_C2R(epiSize_t N, epiSize_t M) const;

    epiFloat AtAbs(epiS32 index) const;
    epiFloat AtTheta(epiS32 index) const;
    epiFloat AtAbs(epiS32 r, epiS32 c) const;
    epiFloat AtTheta(epiS32 r, epiS32 c) const;

    const epiComplexf& At(epiS32 index) const;
    epiComplexf& At(epiS32 index);
    const epiComplexf& At(epiS32 r, epiS32 c) const;
    epiComplexf& At(epiS32 r, epiS32 c);

    friend epiBool operator==(const dSeries2Dc& lhs, const dSeries2Dc& rhs);
    friend epiBool operator!=(const dSeries2Dc& lhs, const dSeries2Dc& rhs);
};

EPI_NAMESPACE_END()
