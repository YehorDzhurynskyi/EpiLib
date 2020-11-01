EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeriesc.h"
#include "EpiData/Series/dSeriesc.cxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeries1Df.h"

#include <fftw3.h>

EPI_NAMESPACE_BEGIN()

dSeriesc::dSeriesc(std::initializer_list<epiComplexf> list)
    : m_Data{list}
{
}

epiBool dSeriesc::GetIsEmpty_Callback() const
{
    return GetData().IsEmpty();
}

epiSize_t dSeriesc::GetSize_Callback() const
{
    return GetData().GetSize();
}

void dSeriesc::Reserve(epiSize_t capacity)
{
    GetData().Reserve(capacity);
}

void dSeriesc::Resize(epiSize_t size)
{
    GetData().Resize(size);
}

void dSeriesc::Clear()
{
    GetData().Clear();
}

epiComplexf& dSeriesc::PushBack(epiComplexf&& value)
{
    return GetData().PushBack(std::move(value));
}

epiFloat dSeriesc::AtAbs(epiS32 index) const
{
    return std::abs(At(index));
}

epiFloat dSeriesc::AtTheta(epiS32 index) const
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

const epiComplexf& dSeriesc::At(epiS32 index) const
{
    epiAssert(index >= 0 && index < GetSize());
    return GetData()[index];
}

epiComplexf& dSeriesc::At(epiS32 index)
{
    epiAssert(index >= 0 && index < GetSize());
    return GetData()[index];
}

const epiComplexf& dSeriesc::operator[](epiS32 index) const
{
    return At(index);
}

epiComplexf& dSeriesc::operator[](epiS32 index)
{
    return At(index);
}

epiBool operator==(const dSeriesc& lhs, const dSeriesc& rhs)
{
    return lhs.GetData() == rhs.GetData();
}

epiBool operator!=(const dSeriesc& lhs, const dSeriesc& rhs)
{
    return !(operator==(lhs, rhs));
}

EPI_NAMESPACE_END()
