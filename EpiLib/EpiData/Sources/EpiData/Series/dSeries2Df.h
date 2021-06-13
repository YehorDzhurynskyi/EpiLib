#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeries2Df.hxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeriesf.h"

EPI_NAMESPACE_BEGIN()

class dSeries2Dc;
class dSeries2Df : public dSeriesf
{
EPI_GENREGION_BEGIN(dSeries2Df)

EPI_GENHIDDEN_dSeries2Df()

public:
    constexpr static epiMetaTypeID TypeID{0x832d085d};

    enum dSeries2Df_PIDs
    {
        PID_Height = 0xf2e1e039,
        PID_Width = 0x4ddb6a2b,
        PID_COUNT = 2
    };

protected:
    epiSize_t GetHeight_Callback() const;

protected:
    epiSize_t m_Width{0};

EPI_GENREGION_END(dSeries2Df)

public:
    using KernelPPCallback = std::function<epiFloat(const dSeries2Df&, epiFloat, epiS32, epiS32)>;

public:
    static dSeries2Df Identity(epiSize_t w);
    static dSeries2Df Arange(epiSize_t size, epiSize_t w, epiFloat start = 0.0f, epiFloat step = 1.0f);
    static dSeries2Df Rand(epiSize_t size, epiSize_t w, epiFloat min = 0.0f, epiFloat max = 1.0f);
    static dSeries2Df Full(epiSize_t size, epiSize_t w, epiFloat value);
    static dSeries2Df Gaussian(epiSize_t size, epiSize_t w, epiFloat g);

    static dSeries2Df RandomNormal(epiSize_t size, epiSize_t w, epiFloat mean, epiFloat stddev, epiFloat scale = 1.0f);
    static dSeries2Df RandomSaltAndPepper(epiSize_t size, epiSize_t w, epiFloat amount, epiFloat s_vs_p = 0.5f, epiFloat saltValue = 1.0f, epiFloat pepperValue = 0.0f);

public:
    dSeries2Df() = default;
    dSeries2Df(std::initializer_list<epiFloat> list, epiSize_t width);

    // TODO: implement with epigen
    dSeries2Df Duplicate() const;

    dSeries2Df Add(epiFloat scalar) const;
    dSeries2Df Add(const dSeries2Df& series, dSeriesAddressMode addressMode = dSeriesAddressMode::Zero) const;
    dSeries2Df Mult(epiFloat scalar) const;
    dSeries2Df Mult(const dSeries2Df& series, dSeriesAddressMode addressMode = dSeriesAddressMode::Zero) const;
    dSeries2Df Log(epiFloat base) const;
    dSeries2Df Exp(epiFloat base) const;

    dSeries2Df Threshold(epiFloat low, epiFloat high) const;

    dSeries2Df Correlate(const dSeries2Df& kernel, dSeriesAddressMode addressMode = dSeriesAddressMode::Reflect, KernelPPCallback callback = nullptr) const;
    epiFloat CorrelateElement(epiS32 r, epiS32 c, const dSeries2Df& kernel, dSeriesAddressMode addressMode = dSeriesAddressMode::Reflect, KernelPPCallback callback = nullptr) const;
    dSeries2Df Convolve(const dSeries2Df& kernel, dSeriesAddressMode addressMode = dSeriesAddressMode::Reflect, KernelPPCallback callback = nullptr) const;
    epiFloat ConvolveElement(epiS32 r, epiS32 c, const dSeries2Df& kernel, dSeriesAddressMode addressMode = dSeriesAddressMode::Reflect, KernelPPCallback callback = nullptr) const;

    dSeries2Df MeanArithmetic(epiSize_t windowSize, dSeriesAddressMode addressMode = dSeriesAddressMode::Reflect, epiFloat trim = 0.0f) const;
    dSeries2Df MeanGeometric(epiSize_t windowSize, dSeriesAddressMode addressMode = dSeriesAddressMode::Reflect) const;
    dSeries2Df MeanHarmonic(epiSize_t windowSize, dSeriesAddressMode addressMode = dSeriesAddressMode::Reflect) const;
    dSeries2Df MeanContraHarmonic(epiSize_t windowSize, dSeriesAddressMode addressMode = dSeriesAddressMode::Reflect, epiFloat order = 0.0f) const;

    dSeries2Df Median(epiSize_t windowSize, dSeriesAddressMode addressMode = dSeriesAddressMode::Reflect) const;

    dSeries2Df Min(epiSize_t windowSize, dSeriesAddressMode addressMode = dSeriesAddressMode::Reflect) const;
    dSeries2Df Max(epiSize_t windowSize, dSeriesAddressMode addressMode = dSeriesAddressMode::Reflect) const;
    dSeries2Df MidPoint(epiSize_t windowSize, dSeriesAddressMode addressMode = dSeriesAddressMode::Reflect) const;

    dSeries2Dc DFT_R2C() const;
    dSeries2Df DFT_Shift() const;
    dSeries2Df DFT_IShift() const;
    dSeries2Df DFT_RShift() const;
    dSeries2Df DFT_IRShift() const;

    dSeries2Df Transform(std::function<epiFloat(epiFloat)>&& callback) const;

    epiFloat At(epiS32 index, dSeriesAddressMode addressMode = dSeriesAddressMode::Error) const;
    epiFloat& At(epiS32 index);
    epiFloat At(epiS32 r, epiS32 c, dSeriesAddressMode addressMode = dSeriesAddressMode::Error) const;
    epiFloat& At(epiS32 r, epiS32 c);

    friend epiBool operator==(const dSeries2Df& lhs, const dSeries2Df& rhs);
    friend epiBool operator!=(const dSeries2Df& lhs, const dSeries2Df& rhs);

protected:
    epiBool GetIsEmpty_Internal() const override;
};

EPI_NAMESPACE_END()
