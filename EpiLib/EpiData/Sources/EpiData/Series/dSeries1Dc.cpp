EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeries1Dc.h"
#include "EpiData/Series/dSeries1Dc.cxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeries1Df.h"

#include <fftw3.h>

EPI_NAMESPACE_BEGIN()

dSeries1Dc::dSeries1Dc(std::initializer_list<epiComplexf> list)
    : super{list}
{
}

dSeries1Df dSeries1Dc::DFT_C2R() const
{
    const epiSize_t N = GetSize();

    return DFT_C2R((N - 1) * 2);
}

dSeries1Df dSeries1Dc::DFT_C2R(epiSize_t N) const
{
#if 0
    // TODO: rewrite in more optimal way
    dSeries1Df y;

    const epiSize_t N2 = GetSize();
    if (N2 == 0)
    {
        return y;
    }

    epiAssert(N2 == N / 2 + 1);

    y.Reserve(N);

    for (epiU32 n = 0; n < N; ++n)
    {
        epiFloat& sum = y.PushBack();
        for (epiU32 k = 0; k < N2; ++k)
        {
            const epiComplexf& x = At(k);
            const epiFloat phase = 2.0f * M_PI * k * n / N;

            epiFloat xRe = x.real() / (N / 2.0f);
            if (k == 0 || (N % 2 == 0 && k == N2 - 1))
            {
                xRe /= 2.0f;
            }

            const epiFloat xIm = x.imag() / (N / 2.0f);

            sum += xRe * cos(phase);
            sum += -xIm * sin(phase);
        }
    }

    return y;
#else
    dSeries1Df y;

    const epiSize_t N2 = GetSize();
    if (N2 == 0)
    {
        return y;
    }

    epiAssert(N2 == N / 2 + 1);
    epiAssertStatic(sizeof(fftwf_complex) == sizeof(epiComplexf));

    fftwf_complex* in = fftwf_alloc_complex(N2);
    y.GetData().Resize(N);

    epiFloat* out = y.GetData().data();
    fftwf_plan p = fftwf_plan_dft_c2r_1d(N, in, out, FFTW_EXHAUSTIVE | FFTW_WISDOM_ONLY);
    if (p == nullptr)
    {
        p = fftwf_plan_dft_c2r_1d(N, in, out, FFTW_EXHAUSTIVE);
    }

    if (p != nullptr)
    {
        memcpy(in, GetData().data(), GetSize() * sizeof(fftwf_complex));

        fftwf_execute(p);

        // TODO: optimize
        for (epiFloat& v : y)
        {
            v /= N;
        }

        // TODO: figure out whether plan should be destroyed, so it can be reused via `wisdom` mechanism
        fftwf_destroy_plan(p);
    }

    fftwf_free(in);

    return y;
#endif
}

EPI_NAMESPACE_END()
