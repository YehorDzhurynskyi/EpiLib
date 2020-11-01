EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeries2Df.h"
#include "EpiData/Series/dSeries2Df.cxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeries2Dc.h"

#include <fftw3.h>

EPI_NAMESPACE_BEGIN()

dSeries2Df::dSeries2Df(std::initializer_list<epiFloat> list, epiSize_t width)
    : super{list}
    , m_Width{width}
{
    if (GetWidth() == 0)
    {
        GetData().Clear();
        epiLogWarn("A zero `width` was passed to `dSeries2Df` constructor: clearing data!");
    }
}

epiSize_t dSeries2Df::GetHeight_Callback() const
{
    if (GetIsEmpty())
    {
        return 0;
    }

    epiAssert(GetWidth() != 0);
    return GetSize() / GetWidth();
}

dSeries2Dc dSeries2Df::DFT_R2C() const
{
#if 0
    using namespace std::complex_literals;

    dSeries2Dc X;

    const epiSize_t M = GetHeight();
    const epiSize_t N = GetWidth();

    if (M == 0 || N == 0)
    {
        return X;
    }

    const epiSize_t M2 = M;
    const epiSize_t N2 = N / 2 + 1;
    X.Resize(M2 * N2);
    X.SetWidth(N2);

    for (epiS32 k = 0; k < M2; ++k)
    {
        for (epiS32 l = 0; l < N2; ++l)
        {
            epiComplexf& sum = (X.At(k, l) = {});
            for (epiS32 r = 0; r < M; ++r)
            {
                const epiFloat kM = (k * r) / static_cast<epiFloat>(M);
                for (epiS32 c = 0; c < N; ++c)
                {
                    const epiFloat lN = (l * c) / static_cast<epiFloat>(N);
                    const epiFloat y = At(r, c, 0, mmImageEdgeHandling::Error);
                    const epiComplexf s = std::exp(2.0f * M_PI * (kM + lN) * 1i);

                    sum += y * std::conj(s);
                }
            }
        }
    }

    return X;
#else
    dSeries2Dc X;

    const epiSize_t M = GetHeight();
    const epiSize_t N = GetWidth();

    if (M == 0 || N == 0)
    {
        return X;
    }

    const epiSize_t M2 = M;
    const epiSize_t N2 = N / 2 + 1;
    X.Resize(M2 * N2);
    X.SetWidth(N2);

    epiFloat* in = fftwf_alloc_real(M * N);

    // TODO: use SIMD
    fftwf_complex* out = reinterpret_cast<fftwf_complex*>(X.GetData().data());

    fftwf_plan p = fftwf_plan_dft_r2c_2d(M, N, in, out, FFTW_EXHAUSTIVE | FFTW_WISDOM_ONLY);
    if (p == nullptr)
    {
        p = fftwf_plan_dft_r2c_2d(M, N, in, out, FFTW_EXHAUSTIVE);
    }

    if (p != nullptr)
    {
        memcpy(in, GetData().data(), M * N * sizeof(epiFloat));

        fftwf_execute(p);
        fftwf_destroy_plan(p);
    }

    fftwf_free(in);

    return X;
#endif
}

epiFloat dSeries2Df::At(epiS32 index) const
{
    return dSeriesf::At(index);
}

epiFloat& dSeries2Df::At(epiS32 index)
{
    return dSeriesf::At(index);
}

epiFloat dSeries2Df::At(epiS32 r, epiS32 c) const
{
    return At(c + r * GetWidth());
}

epiFloat& dSeries2Df::At(epiS32 r, epiS32 c)
{
    return At(c + r * GetWidth());
}

epiBool operator==(const dSeries2Df& lhs, const dSeries2Df& rhs)
{
    return lhs.GetWidth() == rhs.GetWidth() && lhs.GetData() == rhs.GetData();
}

epiBool operator!=(const dSeries2Df& lhs, const dSeries2Df& rhs)
{
    return !(operator==(lhs, rhs));
}

EPI_NAMESPACE_END()
