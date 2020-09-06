EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeriesY.h"
#include "EpiData/Series/dSeriesY.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

dSeriesY::dSeriesY(std::initializer_list<epiFloat> list)
    : m_Y{list}
{
}

epiBool dSeriesY::GetIsEmpty_Callback() const
{
    return GetY().IsEmpty();
}

epiSize_t dSeriesY::GetSize_Callback() const
{
    return GetY().GetSize();
}

void dSeriesY::Reserve(epiSize_t capacity)
{
    GetY().Reserve(capacity);
}

void dSeriesY::Clear()
{
    GetY().Clear();
}

epiFloat& dSeriesY::PushBack(epiFloat&& value)
{
    return GetY().PushBack(std::move(value));
}

epiFloat dSeriesY::AtX(epiS32 index) const
{
    epiAssert(index >= 0 && index < GetSize());
    return GetXStep() * index;
}

const epiFloat& dSeriesY::AtY(epiS32 index) const
{
    epiAssert(index >= 0 && index < GetSize());
    return GetY()[index];
}

epiFloat& dSeriesY::AtY(epiS32 index)
{
    epiAssert(index >= 0 && index < GetSize());
    return GetY()[index];
}

const epiFloat& dSeriesY::operator[](epiS32 index) const
{
    return AtY(index);
}

epiFloat& dSeriesY::operator[](epiS32 index)
{
    return AtY(index);
}

EPI_NAMESPACE_END()
