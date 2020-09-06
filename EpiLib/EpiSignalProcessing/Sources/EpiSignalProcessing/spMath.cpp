#include "EpiSignalProcessing/spMath.h"

#include <cmath>
#include <complex>

EPI_NAMESPACE_BEGIN()

using namespace std::complex_literals;

dSeriesYComplex spMath::DFT_Real(const dSeriesY& series)
{
    dSeriesYComplex X;

    const epiSize_t N = series.GetSize();
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
            const epiFloat y = series[n];
            const epiComplexf s = std::exp(2.0f * M_PI * k * n / N * 1i);

            sum += y * std::conj(s);
        }
    }

    return X;
}

dSeriesY spMath::IDFT_Real(const dSeriesYComplex& series)
{
    const epiSize_t N = series.GetSize();
    if (N == 0)
    {
        return dSeriesY{};
    }

    return IDFT_Real(series, (N - 1) * 2);
}

dSeriesY spMath::IDFT_Real(const dSeriesYComplex& series, epiSize_t N)
{
    dSeriesY y;

    const epiSize_t N2 = series.GetSize();
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
            const epiComplexf x = series[k];
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
}

EPI_NAMESPACE_END()
