#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeriesY.hxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeriesBase.h"

EPI_NAMESPACE_BEGIN()

class dSeriesY : public dSeriesBase
{
EPI_GENREGION_BEGIN(dSeriesY)

EPI_GENHIDDEN_dSeriesY()

public:
    constexpr static epiMetaTypeID TypeID{0xe602dd63};

    enum dSeriesY_PIDs
    {
        PID_XStep = 0xc8efd09,
        PID_Y = 0xc0b506dd,
        PID_IsEmpty = 0xae6d7566,
        PID_Size = 0x57f28b54,
        PID_COUNT = 4
    };

protected:
    epiBool GetIsEmpty_Callback() const;
    epiSize_t GetSize_Callback() const;

protected:
    epiFloat m_XStep{1.0f};
    epiArray<epiFloat> m_Y;

EPI_GENREGION_END(dSeriesY)

public:
    dSeriesY() = default;
    dSeriesY(std::initializer_list<epiFloat> list);

    void Reserve(epiSize_t capacity);
    void Clear();

    epiFloat& PushBack(epiFloat&& value = epiFloat());

    epiFloat AtX(epiS32 index) const;
    const epiFloat& AtY(epiS32 index) const;
    epiFloat& AtY(epiS32 index);

    const epiFloat& operator[](epiS32 index) const;
    epiFloat& operator[](epiS32 index);

    friend epiBool operator==(const dSeriesY& lhs, const dSeriesY& rhs);
    friend epiBool operator!=(const dSeriesY& lhs, const dSeriesY& rhs);
};

EPI_NAMESPACE_END()
