EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeries2Dc.h"
#include "EpiData/Series/dSeries2Dc.cxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeries2Df.h"

#include <fftw3.h>

EPI_NAMESPACE_BEGIN()

dSeries2Dc::dSeries2Dc(std::initializer_list<epiComplexf> list, epiSize_t width)
    : m_Data{list}
    , m_Width{width}
{
    if (GetWidth() == 0)
    {
        GetData().Clear();
        epiLogWarn("A zero `width` was passed to `dSeries2Dc` constructor: clearing data!");
    }
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

dSeries2Df dSeries2Dc::DFT_C2R() const
{
    const epiSize_t M = GetHeight();
    const epiSize_t N = GetWidth();

    return DFT_C2R((N - 1) * 2, M);
}

dSeries2Df dSeries2Dc::DFT_C2R(epiSize_t N, epiSize_t M) const
{
    dSeries2Df y;

    const epiSize_t MN = M * N;

    if (MN == 0)
    {
        return y;
    }

    const epiSize_t M2 = GetHeight();
    const epiSize_t N2 = GetWidth();

    epiAssert(M2 == M && N2 == N / 2 + 1);
    epiAssertStatic(sizeof(fftwf_complex) == sizeof(epiComplexf));

    y.Resize(MN);
    y.SetWidth(N);

    fftwf_complex* in = fftwf_alloc_complex(MN);

    epiFloat* out = y.GetData().data();
    fftwf_plan p = fftwf_plan_dft_c2r_2d(M, N, in, out, FFTW_EXHAUSTIVE | FFTW_WISDOM_ONLY);
    if (p == nullptr)
    {
        p = fftwf_plan_dft_c2r_2d(M, N, in, out, FFTW_EXHAUSTIVE);
    }

    if (p != nullptr)
    {
        memcpy(in, GetData().data(), GetSize() * sizeof(fftwf_complex));

        fftwf_execute(p);

        // TODO: optimize
        for (epiFloat& v : y)
        {
            v /= MN;
        }

        // TODO: figure out whether plan should be destroyed, so it can be reused via `wisdom` mechanism
        fftwf_destroy_plan(p);
    }

    fftwf_free(in);

    return y;
}

epiFloat dSeries2Dc::AtAbs(epiS32 index) const
{
    return std::abs(At(index));
}

epiFloat dSeries2Dc::AtTheta(epiS32 index) const
{
    epiComplexf com = At(index);
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

epiFloat dSeries2Dc::AtAbs(epiS32 r, epiS32 c) const
{
    return AtAbs(c + r * GetWidth());
}

epiFloat dSeries2Dc::AtTheta(epiS32 r, epiS32 c) const
{
    return AtTheta(c + r * GetWidth());
}

const epiComplexf& dSeries2Dc::At(epiS32 index) const
{
    epiAssert(index >= 0 && index < GetSize());

    return GetData()[index];
}

epiComplexf& dSeries2Dc::At(epiS32 index)
{
    epiAssert(index >= 0 && index < GetSize());

    return GetData()[index];
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

const epiComplexf& dSeries2Dc::operator[](epiS32 index) const
{
    return At(index);
}

epiComplexf& dSeries2Dc::operator[](epiS32 index)
{
    return At(index);
}

epiBool operator==(const dSeries2Dc& lhs, const dSeries2Dc& rhs)
{
    return lhs.GetWidth() == rhs.GetWidth() && lhs.GetData() == rhs.GetData();
}

epiBool operator!=(const dSeries2Dc& lhs, const dSeries2Dc& rhs)
{
    return !(operator==(lhs, rhs));
}

EPI_NAMESPACE_END()
