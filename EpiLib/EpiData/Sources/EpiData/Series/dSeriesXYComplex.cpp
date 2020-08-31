EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeriesXYComplex.h"
#include "EpiData/Series/dSeriesXYComplex.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

epiBool dSeriesXYComplex::GetIsEmpty_Callback() const
{
    return GetXY().IsEmpty();
}

epiSize_t dSeriesXYComplex::GetSize_Callback() const
{
    return GetXY().GetSize();
}

void dSeriesXYComplex::Reserve(epiSize_t capacity)
{
    GetXY().Reserve(capacity);
}

void dSeriesXYComplex::Clear()
{
    GetXY().Clear();
}

epiFloat dSeriesXYComplex::AtAbs(epiS32 index) const
{
    return std::abs(At(index));
}

epiFloat dSeriesXYComplex::AtTheta(epiS32 index) const
{
    const auto v = At(index);
    return std::atan(v.imag() / v.real());
}

const epiComplexf& dSeriesXYComplex::At(epiS32 index) const
{
    epiAssert(index >= 0 && index < GetSize());
    return GetXY()[index];
}

epiComplexf& dSeriesXYComplex::At(epiS32 index)
{
    epiAssert(index >= 0 && index < GetSize());
    return GetXY()[index];
}

const epiComplexf& dSeriesXYComplex::operator[](epiS32 index) const
{
    return At(index);
}

epiComplexf& dSeriesXYComplex::operator[](epiS32 index)
{
    return At(index);
}

EPI_NAMESPACE_END()
