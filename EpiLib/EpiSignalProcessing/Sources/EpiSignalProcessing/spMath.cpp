EPI_GENREGION_BEGIN(include)
#include "EpiSignalProcessing/spMath.h"
#include "EpiSignalProcessing/spMath.cxx"
EPI_GENREGION_END(include)

#include <cmath>
#include <complex>

EPI_NAMESPACE_BEGIN()

using namespace std::complex_literals;

dSeriesXYComplex spMath::DFT(const dSeriesY& series)
{
    dSeriesXYComplex X;

    const epiSize_t size = series.GetSize();
    X.Reserve(size);

    for (epiU32 k = 0; k < size; ++k)
    {
        std::complex<epiFloat> sum = 0.0f;
        for (epiU32 x = 0; x < size; ++x)
        {
            const epiFloat y = series[x];
            const std::complex<epiFloat> s = std::exp(M_PI * x * k * 2.0f / size * 1i);

            sum += y * std::conj(s);
        }
    }

    return X;
}

dSeriesXYComplex spMath::DFT(const dSeriesXY& series)
{
    dSeriesXYComplex X;

    const epiSize_t size = series.GetSize();
    X.Reserve(size);

    for (epiU32 k = 0; k < size; ++k)
    {
        std::complex<epiFloat> sum = 0.0f;
        for (epiU32 x = 0; x < size; ++x)
        {
            const epiFloat y = series[x].y;
            const std::complex<epiFloat> s = std::exp(M_PI * x * k * 2.0f / size * 1i);

            sum += y * std::conj(s);
        }
    }

    return X;
}

dSeriesXYComplex spMath::IDFT(const dSeriesXY& series)
{
    return dSeriesXYComplex{};
}

EPI_NAMESPACE_END()
