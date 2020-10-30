EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeries1Df.h"
#include "EpiData/Series/dSeries1Df.cxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeries1Dc.h"

#include <fftw3.h>

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

dSeries1Dc dSeries1Df::DFT_R2C() const
{
#if 0
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
    X.GetData().Resize((N / 2) + 1);

    fftwf_complex* out = reinterpret_cast<fftwf_complex*>(X.GetData().data());

// TODO: finish    EPI_AVX2_ONLY(epiAssert(fftwf_alignment_of(in) == 16 && fftwf_alignment_of(out) == 16));

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
