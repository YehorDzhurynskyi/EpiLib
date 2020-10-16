#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeries2Dc.hxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeriesBase.h"

EPI_NAMESPACE_BEGIN()

class dSeries2Dc : public dSeriesBase
{
EPI_GENREGION_BEGIN(dSeries2Dc)

EPI_GENHIDDEN_dSeries2Dc()

public:
    constexpr static epiMetaTypeID TypeID{0xf347fcd2};

    enum dSeries2Dc_PIDs
    {
        PID_Data = 0xdc15c5d,
        PID_IsEmpty = 0xae6d7566,
        PID_Size = 0x57f28b54,
        PID_Height = 0xf2e1e039,
        PID_Width = 0x4ddb6a2b,
        PID_COUNT = 5
    };

protected:
    epiBool GetIsEmpty_Callback() const;
    epiSize_t GetSize_Callback() const;
    epiSize_t GetHeight_Callback() const;

protected:
    epiArray<epiComplexf> m_Data{};
    epiSize_t m_Width{0};

EPI_GENREGION_END(dSeries2Dc)

public:
    dSeries2Dc() = default;
    dSeries2Dc(std::initializer_list<epiComplexf> list, epiSize_t width);

    void Reserve(epiSize_t capacity);
    void Resize(epiSize_t size);
    void Clear();

    epiComplexf& PushBack(epiComplexf&& value = epiComplexf());

    epiFloat AtAbs(epiS32 r, epiS32 c) const;
    epiFloat AtTheta(epiS32 r, epiS32 c) const;

    const epiComplexf& At(epiS32 r, epiS32 c) const;
    epiComplexf& At(epiS32 r, epiS32 c);
};

EPI_NAMESPACE_END()
