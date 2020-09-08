#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeriesYComplex.hxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeriesBase.h"

EPI_NAMESPACE_BEGIN()

class dSeriesYComplex : public dSeriesBase
{
EPI_GENREGION_BEGIN(dSeriesYComplex)

EPI_GENHIDDEN_dSeriesYComplex()

public:
    constexpr static epiMetaTypeID TypeID{0x81035ed0};

    enum dSeriesYComplex_PIDs
    {
        PID_Y = 0xc0b506dd,
        PID_IsEmpty = 0xae6d7566,
        PID_Size = 0x57f28b54,
        PID_COUNT = 3
    };

protected:
    epiBool GetIsEmpty_Callback() const;
    epiSize_t GetSize_Callback() const;

protected:
    epiArray<epiComplexf> m_Y{};

EPI_GENREGION_END(dSeriesYComplex)

public:
    dSeriesYComplex() = default;
    dSeriesYComplex(std::initializer_list<epiComplexf> list);

    void Reserve(epiSize_t capacity);
    void Clear();

    epiComplexf& PushBack(epiComplexf&& value = epiComplexf());

    epiFloat AtAbs(epiS32 index) const;
    epiFloat AtTheta(epiS32 index) const;

    epiFloat AtX(epiS32 index) const;
    const epiComplexf& AtY(epiS32 index) const;
    epiComplexf& AtY(epiS32 index);

    const epiComplexf& operator[](epiS32 index) const;
    epiComplexf& operator[](epiS32 index);
};

EPI_NAMESPACE_END()
