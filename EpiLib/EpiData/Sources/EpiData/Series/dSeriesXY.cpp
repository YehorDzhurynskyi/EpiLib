EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeriesXY.h"
#include "EpiData/Series/dSeriesXY.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

dSeriesXY::dSeriesXY(std::initializer_list<epiVec2f> list)
    : m_XY{list}
{
}

epiBool dSeriesXY::GetIsEmpty_Callback() const
{
    return GetXY().IsEmpty();
}

epiSize_t dSeriesXY::GetSize_Callback() const
{
    return GetXY().GetSize();
}

void dSeriesXY::Reserve(epiSize_t capacity)
{
    GetXY().Reserve(capacity);
}

void dSeriesXY::Clear()
{
    GetXY().Clear();
}

epiVec2f& dSeriesXY::PushBack(epiVec2f&& value)
{
    return GetXY().PushBack(std::move(value));
}

const epiVec2f& dSeriesXY::At(epiS32 index) const
{
    epiAssert(index >= 0 && index < GetSize());
    return GetXY()[index];
}

epiVec2f& dSeriesXY::At(epiS32 index)
{
    epiAssert(index >= 0 && index < GetSize());
    return GetXY()[index];
}

const epiVec2f& dSeriesXY::operator[](epiS32 index) const
{
    return At(index);
}

epiVec2f& dSeriesXY::operator[](epiS32 index)
{
    return At(index);
}

EPI_NAMESPACE_END()
