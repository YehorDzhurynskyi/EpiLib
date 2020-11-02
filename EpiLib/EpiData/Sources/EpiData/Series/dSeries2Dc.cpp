EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeries2Dc.h"
#include "EpiData/Series/dSeries2Dc.cxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeries2Df.h"

#include <fftw3.h>

EPI_NAMESPACE_BEGIN()

dSeries2Dc::dSeries2Dc(std::initializer_list<epiComplexf> list, epiSize_t width)
    : super{list}
    , m_Width{width}
{
    if (GetWidth() == 0)
    {
        GetData().Clear();
        epiLogWarn("A zero `width` was passed to `dSeries2Dc` constructor: clearing data!");
    }
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

dSeries2Df dSeries2Dc::ToSeries2Df_Magnitude() const
{
    dSeries2Df series;
    series.SetWidth(GetWidth());
    series.GetData().Resize(GetSize());

    epiU32 i = 0;
    for (epiFloat& v : series.GetData())
    {
        v = AtAbs(i++);
    }

    return series;
}

dSeries2Df dSeries2Dc::ToSeries2Df_Phase() const
{
    dSeries2Df series;
    series.SetWidth(GetWidth());
    series.GetData().Resize(GetSize());

    epiU32 i = 0;
    for (epiFloat& v : series.GetData())
    {
        v = AtTheta(i++);
    }

    return series;
}

epiFloat dSeries2Dc::AtAbs(epiS32 index) const
{
    return dSeriesc::AtAbs(index);
}

epiFloat dSeries2Dc::AtTheta(epiS32 index) const
{
    return dSeriesc::AtTheta(index);
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
    return dSeriesc::At(index);
}

epiComplexf& dSeries2Dc::At(epiS32 index)
{
    return dSeriesc::At(index);
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

epiBool operator==(const dSeries2Dc& lhs, const dSeries2Dc& rhs)
{
    return lhs.GetWidth() == rhs.GetWidth() && lhs.GetData() == rhs.GetData();
}

epiBool operator!=(const dSeries2Dc& lhs, const dSeries2Dc& rhs)
{
    return !(operator==(lhs, rhs));
}

EPI_NAMESPACE_END()
