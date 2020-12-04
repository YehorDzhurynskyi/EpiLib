EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeries2Df.h"
#include "EpiData/Series/dSeries2Df.cxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeries2Dc.h"

#include <fftw3.h>

EPI_NAMESPACE_BEGIN()

dSeries2Df dSeries2Df::Identity(epiSize_t w)
{
    epiAssert(w % 2 != 0);

    dSeries2Df series = dSeries2Df::Full(w * w, w, 0.0f);
    series.At(w / 2, w / 2) = 1.0f;

    return series;
}

dSeries2Df dSeries2Df::Arange(epiSize_t size, epiSize_t w, epiFloat start, epiFloat step)
{
    dSeries2Df series;
    series.SetWidth(w);
    series.Arange_Internal(size, start, step);

    return series;

}

dSeries2Df dSeries2Df::Rand(epiSize_t size, epiSize_t w, epiFloat min, epiFloat max)
{
    dSeries2Df series;
    series.SetWidth(w);
    series.Rand_Internal(size, min, max);

    return series;
}

dSeries2Df dSeries2Df::Full(epiSize_t size, epiSize_t w, epiFloat value)
{
    dSeries2Df series;
    series.SetWidth(w);
    series.Full_Internal(size, value);

    return series;
}

dSeries2Df dSeries2Df::Gaussian(epiSize_t size, epiSize_t w, epiFloat g)
{
    dSeries2Df series;
    series.SetWidth(w);
    series.Resize(size);

    epiU32 i = 0;
    for (epiFloat& v : series.GetData())
    {
        const epiU32 x = i % w;
        const epiU32 y = i / w;

        v = std::exp(-(((x * x) + (y * y)) / (2.0f * g * g))) / (2.0f * M_PI * g * g);

        ++i;
    }

    return series;
}

dSeries2Df dSeries2Df::RandomNormal(epiSize_t size, epiSize_t w, epiFloat mean, epiFloat stddev, epiFloat scale)
{
    dSeries2Df series;
    series.SetWidth(w);
    series.RandomNormal_Internal(size, mean, stddev, scale);

    return series;
}

dSeries2Df dSeries2Df::RandomSaltAndPepper(epiSize_t size, epiSize_t w, epiFloat amount, epiFloat s_vs_p, epiFloat saltValue, epiFloat pepperValue)
{
    dSeries2Df series = dSeries2Df::Full(size, w, 0.0f);
    series.SetWidth(w);
    series.RandomSaltAndPepper_Internal(size, amount, s_vs_p, saltValue, pepperValue);

    return series;
}

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

dSeries2Df dSeries2Df::Duplicate() const
{
    dSeries2Df series;
    series.Resize(GetSize());
    series.SetWidth(GetWidth());

    std::copy(begin(), end(), series.begin());

    return series;
}

epiBool dSeries2Df::GetIsEmpty_Internal() const
{
    return super::GetIsEmpty_Internal() || GetWidth() == 0;
}

dSeries2Df dSeries2Df::Add(epiFloat scalar) const
{
    dSeries2Df result = Duplicate();
    result.dSeriesf::Add(scalar);

    return result;
}

dSeries2Df dSeries2Df::Add(const dSeries2Df& series, dSeriesEdgeHandling edge) const
{
    dSeries2Df result;
    result.Resize(GetSize());
    result.SetWidth(GetWidth());

    if (GetIsEmpty() || series.GetIsEmpty())
    {
        return result;
    }

    for (epiS32 r = 0; r < GetHeight(); ++r)
    {
        for (epiS32 c = 0; c < GetWidth(); ++c)
        {
            result.At(r, c) = At(r, c) + series.At(r, c, edge);
        }
    }

    return result;
}

dSeries2Df dSeries2Df::Mult(epiFloat scalar) const
{
    dSeries2Df result = Duplicate();
    result.dSeriesf::Mult(scalar);

    return result;
}

dSeries2Df dSeries2Df::Mult(const dSeries2Df& series, dSeriesEdgeHandling edge) const
{
    dSeries2Df result;
    result.Resize(GetSize());
    result.SetWidth(GetWidth());

    if (GetIsEmpty() || series.GetIsEmpty())
    {
        return result;
    }

    for (epiS32 r = 0; r < GetHeight(); ++r)
    {
        for (epiS32 c = 0; c < GetWidth(); ++c)
        {
            result.At(r, c) = At(r, c) * series.At(r, c, edge);
        }
    }

    return result;
}

dSeries2Df dSeries2Df::Log(epiFloat base) const
{
    dSeries2Df result = Duplicate();
    result.dSeriesf::Log(base);

    return result;
}

dSeries2Df dSeries2Df::Exp(epiFloat base) const
{
    dSeries2Df result = Duplicate();
    result.dSeriesf::Exp(base);

    return result;
}

dSeries2Df dSeries2Df::Threshold(epiFloat low, epiFloat high) const
{
    dSeries2Df result = Duplicate();
    result.dSeriesf::Threshold(low, high);

    return result;
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

dSeries2Df dSeries2Df::Correlate(const dSeries2Df& kernel, dSeriesEdgeHandling edge, KernelPPCallback callback) const
{
    dSeries2Df series;
    series.Resize(GetSize());
    series.SetWidth(GetWidth());

    const epiSize_t w = series.GetWidth();

    epiS32 i = 0;
    for (epiFloat& v : series.GetData())
    {
        const epiS32 r = i / w;
        const epiS32 c = i % w;

        series.At(r, c) = CorrelateElement(r, c, kernel, edge, callback);

        ++i;
    }

    return series;
}

epiFloat dSeries2Df::CorrelateElement(epiS32 r, epiS32 c, const dSeries2Df& kernel, dSeriesEdgeHandling edge, KernelPPCallback callback) const
{
    epiFloat sum = 0.0f;
    for (epiS32 kR = 0; kR < kernel.GetHeight(); ++kR)
    {
        for (epiS32 kC = 0; kC < kernel.GetWidth(); ++kC)
        {
            const epiFloat v = At(r + kR - kernel.GetHeight() / 2, c + kC - kernel.GetWidth() / 2, edge);
            const epiFloat vKernel = kernel.At(kR, kC);

            sum += v * vKernel;
        }
    }

    return callback != nullptr ? callback(*this, sum, r, c) : sum;
}

dSeries2Df dSeries2Df::Convolve(const dSeries2Df& kernel, dSeriesEdgeHandling edge, KernelPPCallback callback) const
{
    dSeries2Df series;
    series.Resize(GetSize());
    series.SetWidth(GetWidth());

    const epiSize_t w = series.GetWidth();

    epiS32 i = 0;
    for (epiFloat& v : series.GetData())
    {
        const epiS32 r = i / w;
        const epiS32 c = i % w;

        series.At(r, c) = ConvolveElement(r, c, kernel, edge, callback);

        ++i;
    }

    return series;
}

epiFloat dSeries2Df::ConvolveElement(epiS32 r, epiS32 c, const dSeries2Df& kernel, dSeriesEdgeHandling edge, KernelPPCallback callback) const
{
    epiFloat sum = 0.0f;
    for (epiS32 kR = 0; kR < kernel.GetHeight(); ++kR)
    {
        for (epiS32 kC = 0; kC < kernel.GetWidth(); ++kC)
        {
            const epiFloat v = At(r - (kR - kernel.GetHeight() / 2), c - (kC - kernel.GetWidth() / 2), edge);
            const epiFloat vKernel = kernel.At(kR, kC);

            sum += v * vKernel;
        }
    }

    return callback != nullptr ? callback(*this, sum, r, c) : sum;
}

dSeries2Df dSeries2Df::MeanArithmetic(epiSize_t windowSize, dSeriesEdgeHandling edge, epiFloat trim) const
{
    if (windowSize == 0)
    {
        return Duplicate();
    }

    const dSeries2Df kernel = dSeries2Df::Full(windowSize * windowSize, windowSize, 1.0f / (windowSize * windowSize - trim));
    return Convolve(kernel, edge);
}

dSeries2Df dSeries2Df::MeanGeometric(epiSize_t windowSize, dSeriesEdgeHandling edge) const
{
    if (windowSize == 0)
    {
        return Duplicate();
    }

    dSeries2Df series;
    series.Resize(GetSize());
    series.SetWidth(GetWidth());

    const epiSize_t w = series.GetWidth();

    epiS32 i = 0;
    for (epiFloat& v : series.GetData())
    {
        const epiS32 r = i / w;
        const epiS32 c = i % w;

        epiFloat prod = 0.0f;
        for (epiS32 kR = 0; kR < windowSize; ++kR)
        {
            for (epiS32 kC = 0; kC < windowSize; ++kC)
            {
                prod *= At(r - (kR - windowSize / 2), c - (kC - windowSize / 2), edge);
            }
        }

        series.At(r, c) = std::pow(prod, 1.0f / (windowSize * windowSize));

        ++i;
    }

    return series;
}

dSeries2Df dSeries2Df::MeanHarmonic(epiSize_t windowSize, dSeriesEdgeHandling edge) const
{
    if (windowSize == 0)
    {
        return Duplicate();
    }

    dSeries2Df series;
    series.Resize(GetSize());
    series.SetWidth(GetWidth());

    const epiSize_t w = series.GetWidth();

    epiS32 i = 0;
    for (epiFloat& v : series.GetData())
    {
        const epiS32 r = i / w;
        const epiS32 c = i % w;

        epiFloat sum = 0.0f;
        for (epiS32 kR = 0; kR < windowSize; ++kR)
        {
            for (epiS32 kC = 0; kC < windowSize; ++kC)
            {
                sum += 1.0f / At(r - (kR - windowSize / 2), c - (kC - windowSize / 2), edge);
            }
        }

        series.At(r, c) = (windowSize * windowSize) / sum;

        ++i;
    }

    return series;
}

dSeries2Df dSeries2Df::MeanContraHarmonic(epiSize_t windowSize, dSeriesEdgeHandling edge, epiFloat order) const
{
    if (windowSize == 0)
    {
        return Duplicate();
    }

    dSeries2Df series;
    series.Resize(GetSize());
    series.SetWidth(GetWidth());

    const epiSize_t w = series.GetWidth();

    epiS32 i = 0;
    for (epiFloat& v : series.GetData())
    {
        const epiS32 r = i / w;
        const epiS32 c = i % w;

        epiFloat sumNum = 0.0f;
        epiFloat sumDen = 0.0f;
        for (epiS32 kR = 0; kR < windowSize; ++kR)
        {
            for (epiS32 kC = 0; kC < windowSize; ++kC)
            {
                const epiFloat v = At(r - (kR - windowSize / 2), c - (kC - windowSize / 2), edge);
                const epiFloat y = std::pow(v, order);

                sumNum += y * v;
                sumDen += y;
            }
        }

        series.At(r, c) = sumNum / sumDen;

        ++i;
    }

    return series;
}

dSeries2Df dSeries2Df::Median(epiSize_t windowSize, dSeriesEdgeHandling edge) const
{
    if (windowSize == 0)
    {
        return Duplicate();
    }

    // TODO: use inplace array
    std::vector<epiFloat> localR;
    std::vector<epiFloat> localC;
    localR.resize(windowSize);
    localC.resize(windowSize);

    dSeries2Df series;
    series.Resize(GetSize());
    series.SetWidth(GetWidth());

    const epiSize_t w = series.GetWidth();

    epiS32 i = 0;
    for (epiFloat& v : series.GetData())
    {
        const epiS32 r = i / w;
        const epiS32 c = i % w;

        for (epiS32 k = 0; k < windowSize; ++k)
        {
            localR[k] = At(r, c - (k - windowSize / 2), edge);
            localC[k] = At(r - (k - windowSize / 2), c, edge);
        }

        std::sort(localR.begin(), localR.end());
        std::sort(localC.begin(), localC.end());

        if (windowSize % 2 == 0)
        {
            series.At(r, c) = 0.5f * (0.5f * (localR[windowSize / 2] + localR[windowSize / 2 - 1]) +
                                      0.5f * (localC[windowSize / 2] + localC[windowSize / 2 - 1]));
        }
        else
        {
            series.At(r, c) = 0.5f * (localR[windowSize / 2] + localC[windowSize / 2]);
        }

        ++i;
    }

    return series;
}

dSeries2Df dSeries2Df::Min(epiSize_t windowSize, dSeriesEdgeHandling edge) const
{
    if (windowSize == 0)
    {
        return Duplicate();
    }

    dSeries2Df series;
    series.Resize(GetSize());
    series.SetWidth(GetWidth());

    const epiSize_t w = series.GetWidth();

    epiS32 i = 0;
    for (epiFloat& v : series.GetData())
    {
        const epiS32 r = i / w;
        const epiS32 c = i % w;

        epiFloat minR = std::numeric_limits<epiFloat>::max();
        epiFloat minC = std::numeric_limits<epiFloat>::max();
        for (epiS32 k = 0; k < windowSize; ++k)
        {
            minR = std::min(minR, At(r, c - (k - windowSize / 2), edge));
            minC = std::min(minC, At(r - (k - windowSize / 2), c, edge));
        }

        series.At(r, c) = 0.5f * (minR + minC);

        ++i;
    }

    return series;
}

dSeries2Df dSeries2Df::Max(epiSize_t windowSize, dSeriesEdgeHandling edge) const
{
    if (windowSize == 0)
    {
        return Duplicate();
    }

    dSeries2Df series;
    series.Resize(GetSize());
    series.SetWidth(GetWidth());

    const epiSize_t w = series.GetWidth();

    epiS32 i = 0;
    for (epiFloat& v : series.GetData())
    {
        const epiS32 r = i / w;
        const epiS32 c = i % w;

        epiFloat maxR = std::numeric_limits<epiFloat>::min();
        epiFloat maxC = std::numeric_limits<epiFloat>::min();
        for (epiS32 k = 0; k < windowSize; ++k)
        {
            maxR = std::max(maxR, At(r, c - (k - windowSize / 2), edge));
            maxC = std::max(maxC, At(r - (k - windowSize / 2), c, edge));
        }

        series.At(r, c) = 0.5f * (maxR + maxC);

        ++i;
    }

    return series;
}

dSeries2Df dSeries2Df::MidPoint(epiSize_t windowSize, dSeriesEdgeHandling edge) const
{
    if (windowSize == 0)
    {
        return Duplicate();
    }

    dSeries2Df series;
    series.Resize(GetSize());
    series.SetWidth(GetWidth());

    const epiSize_t w = series.GetWidth();

    epiS32 i = 0;
    for (epiFloat& v : series.GetData())
    {
        const epiS32 r = i / w;
        const epiS32 c = i % w;

        epiFloat minR = std::numeric_limits<epiFloat>::max();
        epiFloat minC = std::numeric_limits<epiFloat>::max();
        epiFloat maxR = std::numeric_limits<epiFloat>::min();
        epiFloat maxC = std::numeric_limits<epiFloat>::min();
        for (epiS32 k = 0; k < windowSize; ++k)
        {
            const epiFloat vR = At(r, c - (k - windowSize / 2), edge);
            const epiFloat vC = At(r - (k - windowSize / 2), c, edge);

            minR = std::min(minR, vR);
            minC = std::min(minC, vC);
            maxR = std::max(maxR, vR);
            maxC = std::max(maxC, vC);
        }

        series.At(r, c) = 0.5f * (0.5f * (maxR + maxC) + 0.5f * (minR + minC));

        ++i;
    }

    return series;
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
        // TODO: submit background task to calculate `FFTW_EXHAUSTIVE` plan and return `FFTW_MEASURE` plan immediately
        p = fftwf_plan_dft_r2c_2d(M, N, in, out, FFTW_MEASURE);
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

dSeries2Df dSeries2Df::DFT_Shift() const
{
    dSeries2Df shift;

    const epiSize_t s = GetSize();
    const epiSize_t w = GetWidth();
    const epiSize_t h = GetHeight();

    shift.SetWidth(w);
    shift.GetData().Resize(s);

    for (epiU32 r = 0; r < h; ++r)
    {
        const epiU32 toR = (r + h / 2) % h;

        for (epiU32 c = 0; c < w; ++c)
        {
            const epiU32 toC = (c + w / 2) % w;

            shift[toC + toR * w] = At(r, c);
        }
    }

    return shift;
}

dSeries2Df dSeries2Df::DFT_IShift() const
{
    dSeries2Df shift;

    const epiSize_t s = GetSize();
    const epiSize_t w = GetWidth();
    const epiSize_t h = GetHeight();

    shift.SetWidth(w);
    shift.GetData().Resize(s);

    for (epiU32 r = 0; r < h; ++r)
    {
        epiS32 toR = r - static_cast<epiS32>(h / 2);
        if (toR < 0)
        {
            toR += h;
        }

        for (epiU32 c = 0; c < w; ++c)
        {
            epiS32 toC = c - static_cast<epiS32>(w / 2);
            if (toC < 0)
            {
                toC += w;
            }

            shift[toC + toR * w] = At(r, c);
        }
    }

    return shift;
}

dSeries2Df dSeries2Df::DFT_RShift() const
{
    dSeries2Df shift;

    const epiSize_t s = GetSize();
    const epiSize_t w = GetWidth();
    const epiSize_t h = GetHeight();

    shift.SetWidth(w);
    shift.GetData().Resize(s);

    for (epiU32 r = 0; r < h; ++r)
    {
        const epiU32 toR = (r + h / 2) % h;

        for (epiU32 c = 0; c < w; ++c)
        {
            shift[c + toR * w] = At(r, c);
        }
    }

    return shift;
}

dSeries2Df dSeries2Df::DFT_IRShift() const
{
    dSeries2Df shift;

    const epiSize_t s = GetSize();
    const epiSize_t w = GetWidth();
    const epiSize_t h = GetHeight();

    shift.SetWidth(w);
    shift.GetData().Resize(s);

    for (epiU32 r = 0; r < h; ++r)
    {
        epiS32 toR = r - static_cast<epiS32>(h / 2);
        if (toR < 0)
        {
            toR += h;
        }

        for (epiU32 c = 0; c < w; ++c)
        {
            shift[c + toR * w] = At(r, c);
        }
    }

    return shift;
}

dSeries2Df dSeries2Df::Transform(std::function<epiFloat(epiFloat)>&& callback) const
{
    return static_cast<dSeries2Df&>(Duplicate().dSeriesf::Transform(std::move(callback)));
}

epiFloat dSeries2Df::At(epiS32 index, dSeriesEdgeHandling edge) const
{
    const epiSize_t w = GetWidth();

    epiAssert(w != 0);

    return At(index / w, index % w, edge);
}

epiFloat& dSeries2Df::At(epiS32 index)
{
    return dSeriesf::At(index);
}

epiFloat dSeries2Df::At(epiS32 r, epiS32 c, dSeriesEdgeHandling edge) const
{
    const epiS32 w = static_cast<epiS32>(GetWidth());
    const epiS32 h = static_cast<epiS32>(GetHeight());

    epiS32 x = 0;
    epiS32 y = 0;
    switch (edge)
    {
    case dSeriesEdgeHandling::Error:
    {
        if (r != std::clamp(r, 0, h - 1) || c != std::clamp(c, 0, w - 1))
        {
            epiLogError("`r={}` should be in range [{}..{}], `c={}` should be in range [{}..{}]", r, 0, h - 1, c, 0, w - 1);
            return 0;
        }

        x = c;
        y = r;
    } break;
    case dSeriesEdgeHandling::Zero:
    {
        if (r != std::clamp(r, 0, h - 1) || c != std::clamp(c, 0, w - 1))
        {
            return 0;
        }

        x = c;
        y = r;
    } break;
    case dSeriesEdgeHandling::One:
    {
        if (r != std::clamp(r, 0, h - 1) || c != std::clamp(c, 0, w - 1))
        {
            return 1.0f;
        }

        x = c;
        y = r;
    } break;
    case dSeriesEdgeHandling::FF:
    {
        if (r != std::clamp(r, 0, h - 1) || c != std::clamp(c, 0, w - 1))
        {
            return 0xff;
        }

        x = c;
        y = r;
    } break;
    case dSeriesEdgeHandling::Nearest:
    {
        x = std::clamp(c, 0, w - 1);
        y = std::clamp(r, 0, h - 1);
    } break;
    case dSeriesEdgeHandling::Wrap:
    {
        if (const epiS32 cc = std::clamp(c, 0, w - 1); cc != c)
        {
            c = c < 0 ? w + c % w : c % w;
        }

        if (const epiS32 rr = std::clamp(r, 0, h - 1); rr != r)
        {
            r = r < 0 ? h + r % h : r % h;
        }

        x = c;
        y = r;
    } break;
    case dSeriesEdgeHandling::Reflect:
    {
        if (const epiS32 cc = std::clamp(c, 0, w - 1); cc != c)
        {
            c = c < 0 ? -(c + 1) % w : (w - 1) - c % w;
        }

        if (const epiS32 rr = std::clamp(r, 0, h - 1); rr != r)
        {
            r = r < 0 ? -(r + 1) % h : (h - 1) - r % h;
        }

        x = c;
        y = r;
    } break;
    case dSeriesEdgeHandling::Mirror:
    {
        if (const epiS32 cc = std::clamp(c, 0, w - 1); cc != c)
        {
            if (c > w - 1)
            {
                c = (w - 1) - (c % w + 1);
            }

            if (c < 0)
            {
                c = -c % w;
            }
        }

        if (const epiS32 rr = std::clamp(r, 0, h - 1); rr != r)
        {
            if (r > h - 1)
            {
                r = (h - 1) - (r % h + 1);
            }

            if (r < 0)
            {
                r = -r % h;
            }
        }

        x = c;
        y = r;
    } break;
    }

    return GetData()[x + y * GetWidth()];
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
