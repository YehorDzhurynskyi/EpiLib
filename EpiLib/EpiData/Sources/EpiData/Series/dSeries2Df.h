#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeries2Df.hxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeriesf.h"

EPI_NAMESPACE_BEGIN()

class dSeries2Dc;
class dSeries2Df : public dSeriesf
{
EPI_GENREGION_BEGIN(dSeries2Df)

EPI_GENHIDDEN_dSeries2Df()

public:
    constexpr static epiMetaTypeID TypeID{0x832d085d};

    enum dSeries2Df_PIDs
    {
        PID_Height = 0xf2e1e039,
        PID_Width = 0x4ddb6a2b,
        PID_COUNT = 2
    };

protected:
    epiSize_t GetHeight_Callback() const;

protected:
    epiSize_t m_Width{0};

EPI_GENREGION_END(dSeries2Df)

public:
    dSeries2Df() = default;
    dSeries2Df(std::initializer_list<epiFloat> list, epiSize_t width);

    dSeries2Dc DFT_R2C() const;
    dSeries2Df DFT_Shift() const;
    dSeries2Df DFT_IShift() const;
    dSeries2Df DFT_RShift() const;
    dSeries2Df DFT_IRShift() const;

    epiFloat At(epiS32 index) const;
    epiFloat& At(epiS32 index);
    epiFloat At(epiS32 r, epiS32 c) const;
    epiFloat& At(epiS32 r, epiS32 c);

    friend epiBool operator==(const dSeries2Df& lhs, const dSeries2Df& rhs);
    friend epiBool operator!=(const dSeries2Df& lhs, const dSeries2Df& rhs);
};

EPI_NAMESPACE_END()
