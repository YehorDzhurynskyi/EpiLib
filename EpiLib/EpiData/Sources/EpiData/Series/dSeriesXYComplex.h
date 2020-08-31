#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeriesXYComplex.hxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeriesBase.h"

EPI_NAMESPACE_BEGIN()

class dSeriesXYComplex : public dSeriesBase
{
EPI_GENREGION_BEGIN(dSeriesXYComplex)

EPI_GENHIDDEN_dSeriesXYComplex()

public:
    constexpr static MetaTypeID TypeID{0xc759e0cd};

    enum dSeriesXYComplex_PIDs
    {
        PID_XY = 0x210c2cf3,
        PID_IsEmpty = 0xae6d7566,
        PID_Size = 0x57f28b54,
        PID_COUNT = 3
    };

protected:
    epiBool GetIsEmpty_Callback() const;
    epiSize_t GetSize_Callback() const;

protected:
    epiArray<epiComplexf> m_XY;

EPI_GENREGION_END(dSeriesXYComplex)

public:
    void Reserve(epiSize_t capacity);
    void Clear();

    epiFloat AtAbs(epiS32 index) const;
    epiFloat AtTheta(epiS32 index) const;

    const epiComplexf& At(epiS32 index) const;
    epiComplexf& At(epiS32 index);

    const epiComplexf& operator[](epiS32 index) const;
    epiComplexf& operator[](epiS32 index);
};

EPI_NAMESPACE_END()
