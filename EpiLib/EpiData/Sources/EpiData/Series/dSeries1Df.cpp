EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeries1Df.h"
#include "EpiData/Series/dSeries1Df.cxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeries1Dc.h"

EPI_NAMESPACE_BEGIN()

dSeries1Df::dSeries1Df(std::initializer_list<epiFloat> list)
    : m_Data{list}
{
}

epiBool dSeries1Df::GetIsEmpty_Callback() const
{
    return GetData().IsEmpty();
}

epiSize_t dSeries1Df::GetSize_Callback() const
{
    return GetData().GetSize();
}

void dSeries1Df::Reserve(epiSize_t capacity)
{
    GetData().Reserve(capacity);
}

void dSeries1Df::Resize(epiSize_t size)
{
    GetData().Resize(size);
}

void dSeries1Df::Clear()
{
    GetData().Clear();
}

epiFloat& dSeries1Df::PushBack(epiFloat&& value)
{
    return GetData().PushBack(std::move(value));
}

using namespace std::complex_literals;

dSeries1Dc dSeries1Df::DFT() const
{
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
}

dSeries1Df dSeries1Df::IDFT(const dSeries1Dc& series)
{
    const epiSize_t N = series.GetSize();
    if (N == 0)
    {
        return dSeries1Df{};
    }

    return IDFT(series, (N - 1) * 2);
}

dSeries1Df dSeries1Df::IDFT(const dSeries1Dc& series, epiSize_t N)
{
    // TODO: rewrite in more optimal way
    dSeries1Df y;

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

epiFloat dSeries1Df::At(epiS32 index) const
{
    epiAssert(index >= 0 && index < GetSize());
    return GetData()[index];
}

epiFloat& dSeries1Df::At(epiS32 index)
{
    epiAssert(index >= 0 && index < GetSize());
    return GetData()[index];
}

epiFloat dSeries1Df::operator[](epiS32 index) const
{
    return At(index);
}

epiFloat& dSeries1Df::operator[](epiS32 index)
{
    return At(index);
}

epiBool operator==(const dSeries1Df& lhs, const dSeries1Df& rhs)
{
    return lhs.GetData() == rhs.GetData();
}

epiBool operator!=(const dSeries1Df& lhs, const dSeries1Df& rhs)
{
    return !(operator==(lhs, rhs));
}

EPI_NAMESPACE_END()
