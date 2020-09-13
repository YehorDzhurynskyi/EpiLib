EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeries1Dc.h"
#include "EpiData/Series/dSeries1Dc.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

dSeries1Dc::dSeries1Dc(std::initializer_list<epiComplexf> list)
    : m_Data{list}
{
}

epiBool dSeries1Dc::GetIsEmpty_Callback() const
{
    return GetData().IsEmpty();
}

epiSize_t dSeries1Dc::GetSize_Callback() const
{
    return GetData().GetSize();
}

void dSeries1Dc::Reserve(epiSize_t capacity)
{
    GetData().Reserve(capacity);
}

void dSeries1Dc::Clear()
{
    GetData().Clear();
}

epiComplexf& dSeries1Dc::PushBack(epiComplexf&& value)
{
    return GetData().PushBack(std::move(value));
}

epiFloat dSeries1Dc::AtAbs(epiS32 index) const
{
    return std::abs(At(index));
}

epiFloat dSeries1Dc::AtTheta(epiS32 index) const
{
    epiComplexf c = At(index);
    if (epiFloatingEq(c.real(), 0.0f))
    {
        c.real(0.0f);
    }

    if (epiFloatingEq(c.imag(), 0.0f))
    {
        c.imag(0.0f);
    }

    return std::arg(c);
}

const epiComplexf& dSeries1Dc::At(epiS32 index) const
{
    epiAssert(index >= 0 && index < GetSize());
    return GetData()[index];
}

epiComplexf& dSeries1Dc::At(epiS32 index)
{
    epiAssert(index >= 0 && index < GetSize());
    return GetData()[index];
}

const epiComplexf& dSeries1Dc::operator[](epiS32 index) const
{
    return At(index);
}

epiComplexf& dSeries1Dc::operator[](epiS32 index)
{
    return At(index);
}

EPI_NAMESPACE_END()
