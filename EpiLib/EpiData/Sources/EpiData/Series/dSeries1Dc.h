#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeries1Dc.hxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeriesBase.h"

EPI_NAMESPACE_BEGIN()

class dSeries1Dc : public dSeriesBase
{
EPI_GENREGION_BEGIN(dSeries1Dc)

EPI_GENHIDDEN_dSeries1Dc()

public:
    constexpr static epiMetaTypeID TypeID{0xf101428b};

    enum dSeries1Dc_PIDs
    {
        PID_Data = 0xdc15c5d,
        PID_IsEmpty = 0xae6d7566,
        PID_Size = 0x57f28b54,
        PID_COUNT = 3
    };

protected:
    epiBool GetIsEmpty_Callback() const;
    epiSize_t GetSize_Callback() const;

protected:
    epiArray<epiComplexf> m_Data{};

EPI_GENREGION_END(dSeries1Dc)

public:
    dSeries1Dc() = default;
    dSeries1Dc(std::initializer_list<epiComplexf> list);

    void Reserve(epiSize_t capacity);
    void Clear();

    epiComplexf& PushBack(epiComplexf&& value = epiComplexf());

    epiFloat AtAbs(epiS32 index) const;
    epiFloat AtTheta(epiS32 index) const;

    const epiComplexf& At(epiS32 index) const;
    epiComplexf& At(epiS32 index);

    const epiComplexf& operator[](epiS32 index) const;
    epiComplexf& operator[](epiS32 index);
};

EPI_NAMESPACE_END()
