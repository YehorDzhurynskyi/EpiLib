EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeries1Df.h"
#include "EpiData/Series/dSeries1Df.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

dSeries1Df::dSeries1Df(std::initializer_list<epiFloat> list)
    : m_Data{list}
{
}

epiBool dSeries1Df::GetIsEmpty_Callback() const
{
    return GetData().IsEmpty();
}

epiSize_t dSeries1Df::GetSize_Callback() const
{
    return GetData().GetSize();
}

void dSeries1Df::Reserve(epiSize_t capacity)
{
    GetData().Reserve(capacity);
}

void dSeries1Df::Clear()
{
    GetData().Clear();
}

epiFloat& dSeries1Df::PushBack(epiFloat&& value)
{
    return GetData().PushBack(std::move(value));
}

epiFloat dSeries1Df::At(epiS32 index) const
{
    epiAssert(index >= 0 && index < GetSize());
    return GetData()[index];
}

epiFloat& dSeries1Df::At(epiS32 index)
{
    epiAssert(index >= 0 && index < GetSize());
    return GetData()[index];
}

epiFloat dSeries1Df::operator[](epiS32 index) const
{
    return At(index);
}

epiFloat& dSeries1Df::operator[](epiS32 index)
{
    return At(index);
}

epiBool operator==(const dSeries1Df& lhs, const dSeries1Df& rhs)
{
    return lhs.GetData() == rhs.GetData();
}

epiBool operator!=(const dSeries1Df& lhs, const dSeries1Df& rhs)
{
    return !(operator==(lhs, rhs));
}

EPI_NAMESPACE_END()
