#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeriesXY.hxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeriesBase.h"

EPI_NAMESPACE_BEGIN()

class dSeriesXY : public dSeriesBase
{
EPI_GENREGION_BEGIN(dSeriesXY)

EPI_GENHIDDEN_dSeriesXY()

public:
    constexpr static MetaTypeID TypeID{0xdf305a3};

    enum dSeriesXY_PIDs
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
    epiArray<epiVec2f> m_XY;

EPI_GENREGION_END(dSeriesXY)

public:
    dSeriesXY() = default;
    dSeriesXY(std::initializer_list<epiVec2f> list);

    void Reserve(epiSize_t capacity);
    void Clear();

    epiVec2f& PushBack(epiVec2f&& value = epiVec2f());

    const epiVec2f& At(epiS32 index) const;
    epiVec2f& At(epiS32 index);

    const epiVec2f& operator[](epiS32 index) const;
    epiVec2f& operator[](epiS32 index);
};

EPI_NAMESPACE_END()
