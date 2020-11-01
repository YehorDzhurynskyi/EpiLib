EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeries1Df.h"
#include "EpiData/Series/dSeries1Df.cxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeries1Dc.h"

#include <fftw3.h>

EPI_NAMESPACE_BEGIN()

dSeries1Df::dSeries1Df(std::initializer_list<epiFloat> list)
    : super{list}
{
}

dSeries1Dc dSeries1Df::DFT_R2C() const
{
#if 0
    using namespace std::complex_literals;

    dSeries1Dc X;

    const epiSize_t N = GetSize();
    if (N == 0)
    {
        return X;
    }

    const epiSize_t N2 = N / 2 + 1;
    X.Reserve(N2);

    for (epiS32 k = 0; k < N2; ++k)
    {
        epiComplexf& sum = X.PushBack();
        for (epiS32 n = 0; n < N; ++n)
        {
            const epiFloat kN = (k * n) / static_cast<epiFloat>(N);
            const epiFloat y = At(n);
            const epiComplexf s = std::exp(2.0f * M_PI * kN * 1i);

            sum += y * std::conj(s);
        }
    }

    return X;
#else
    dSeries1Dc X;

    const epiSize_t N = GetSize();
    if (N == 0)
    {
        return X;
    }

    epiFloat* in = fftwf_alloc_real(N);
    X.Resize(N / 2 + 1);

    // TODO: use SIMD
    fftwf_complex* out = reinterpret_cast<fftwf_complex*>(X.GetData().data());

    fftwf_plan p = fftwf_plan_dft_r2c_1d(N, in, out, FFTW_EXHAUSTIVE | FFTW_WISDOM_ONLY);
    if (p == nullptr)
    {
        p = fftwf_plan_dft_r2c_1d(N, in, out, FFTW_EXHAUSTIVE);
    }

    if (p != nullptr)
    {
        memcpy(in, GetData().data(), GetSize() * sizeof(epiFloat));

        fftwf_execute(p);
        fftwf_destroy_plan(p);
    }

    fftwf_free(in);

    return X;
#endif
}

epiFloat dSeries1Df::GetBoundRight_Callback() const
{
    return GetBoundLeft() + GetSize();
}

EPI_NAMESPACE_END()
