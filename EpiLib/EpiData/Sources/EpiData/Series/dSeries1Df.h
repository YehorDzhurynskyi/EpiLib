#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeries1Df.hxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeriesBase.h"

EPI_NAMESPACE_BEGIN()

class dSeries1Df : public dSeriesBase
{
EPI_GENREGION_BEGIN(dSeries1Df)

EPI_GENHIDDEN_dSeries1Df()

public:
    constexpr static epiMetaTypeID TypeID{0x816bb604};

    enum dSeries1Df_PIDs
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
    epiArray<epiFloat> m_Data{};

EPI_GENREGION_END(dSeries1Df)

public:
    dSeries1Df() = default;
    dSeries1Df(std::initializer_list<epiFloat> list);

    void Reserve(epiSize_t capacity);
    void Clear();

    epiFloat& PushBack(epiFloat && value = epiFloat());

    epiFloat At(epiS32 index) const;
    epiFloat& At(epiS32 index);

    epiFloat operator[](epiS32 index) const;
    epiFloat& operator[](epiS32 index);

    friend epiBool operator==(const dSeries1Df& lhs, const dSeries1Df& rhs);
    friend epiBool operator!=(const dSeries1Df& lhs, const dSeries1Df& rhs);
};

EPI_NAMESPACE_END()
