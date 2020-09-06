EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeriesYComplex.h"
#include "EpiData/Series/dSeriesYComplex.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

dSeriesYComplex::dSeriesYComplex(std::initializer_list<epiComplexf> list)
    : m_Y{list}
{
}

epiBool dSeriesYComplex::GetIsEmpty_Callback() const
{
    return GetY().IsEmpty();
}

epiSize_t dSeriesYComplex::GetSize_Callback() const
{
    return GetY().GetSize();
}

void dSeriesYComplex::Reserve(epiSize_t capacity)
{
    GetY().Reserve(capacity);
}

void dSeriesYComplex::Clear()
{
    GetY().Clear();
}

epiComplexf& dSeriesYComplex::PushBack(epiComplexf&& value)
{
    return GetY().PushBack(std::move(value));
}

epiFloat dSeriesYComplex::AtAbs(epiS32 index) const
{
    return std::abs(AtY(index));
}

epiFloat dSeriesYComplex::AtTheta(epiS32 index) const
{
    const auto c = AtY(index);
    if (epiFloatingEq(c.real(), 0.0f) && epiFloatingEq(c.imag(), 0.0f))
    {
        return 0.0f;
    }

    return std::arg(c);
}

epiFloat dSeriesYComplex::AtX(epiS32 index) const
{
    epiAssert(index >= 0 && index < GetSize());
    return index;
}

const epiComplexf& dSeriesYComplex::AtY(epiS32 index) const
{
    epiAssert(index >= 0 && index < GetSize());
    return GetY()[index];
}

epiComplexf& dSeriesYComplex::AtY(epiS32 index)
{
    epiAssert(index >= 0 && index < GetSize());
    return GetY()[index];
}

const epiComplexf& dSeriesYComplex::operator[](epiS32 index) const
{
    return AtY(index);
}

epiComplexf& dSeriesYComplex::operator[](epiS32 index)
{
    return AtY(index);
}

EPI_NAMESPACE_END()
