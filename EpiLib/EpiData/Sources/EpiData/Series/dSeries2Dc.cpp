EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeries2Dc.h"
#include "EpiData/Series/dSeries2Dc.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

dSeries2Dc::dSeries2Dc(std::initializer_list<epiComplexf> list, epiSize_t width)
    : m_Data{list}
    , m_Width{width}
{
}

epiBool dSeries2Dc::GetIsEmpty_Callback() const
{
    return GetData().IsEmpty();
}

epiSize_t dSeries2Dc::GetSize_Callback() const
{
    return GetData().GetSize();
}

epiSize_t dSeries2Dc::GetHeight_Callback() const
{
    if (GetIsEmpty())
    {
        return 0;
    }

    epiAssert(GetWidth() != 0);
    return GetSize() / GetWidth();
}

void dSeries2Dc::Reserve(epiSize_t capacity)
{
    GetData().Reserve(capacity);
}

void dSeries2Dc::Resize(epiSize_t size)
{
    GetData().Resize(size);
}

void dSeries2Dc::Clear()
{
    GetData().Clear();
}

epiComplexf& dSeries2Dc::PushBack(epiComplexf&& value)
{
    return GetData().PushBack(std::move(value));
}

epiFloat dSeries2Dc::AtAbs(epiS32 r, epiS32 c) const
{
    return std::abs(At(r, c));
}

epiFloat dSeries2Dc::AtTheta(epiS32 r, epiS32 c) const
{
    epiComplexf com = At(r, c);
    if (epiFloatingEqEx(com.real(), 0.0f, 5.0e-3f))
    {
        com.real(0.0f);
    }

    if (epiFloatingEqEx(com.imag(), 0.0f, 5.0e-3f))
    {
        com.imag(0.0f);
    }

    return std::arg(com);
}

const epiComplexf& dSeries2Dc::At(epiS32 r, epiS32 c) const
{
    epiAssert(r >= 0 && r < GetHeight());
    epiAssert(c >= 0 && c < GetWidth());

    return GetData()[c + r * GetWidth()];
}

epiComplexf& dSeries2Dc::At(epiS32 r, epiS32 c)
{
    epiAssert(r >= 0 && r < GetHeight());
    epiAssert(c >= 0 && c < GetWidth());

    return GetData()[c + r * GetWidth()];
}

EPI_NAMESPACE_END()
