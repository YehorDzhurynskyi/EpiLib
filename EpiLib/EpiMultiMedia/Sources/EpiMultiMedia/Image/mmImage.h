#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/mmImage.hxx"
EPI_GENREGION_END(include)

#include "EpiMultimedia/mmMediaBase.h"

#include "EpiCore/Color.h"

#include "EpiData/Series/dSeries1Df.h"
#include "EpiData/Series/dSeries2Df.h"
#include "EpiData/Series/dSeries2Dc.h"

EPI_NAMESPACE_BEGIN()

enum class mmImagePixelFormat : epiS32
{
EPI_GENREGION_BEGIN(mmImagePixelFormat)
    R8G8B8 = 0,
    R8G8B8A8 = 1,
    GRAYSCALE = 2
EPI_GENREGION_END(mmImagePixelFormat)
};

using mmImageGetColorValueCallback = epiU8(Color::*)() const;

class mmImage : public mmMediaBase
{
EPI_GENREGION_BEGIN(mmImage)

EPI_GENHIDDEN_mmImage()

public:
    constexpr static epiMetaTypeID TypeID{0x1b93299};

    enum mmImage_PIDs
    {
        PID_BPP = 0x5d8f8c1c,
        PID_BPC = 0xd931cdc2,
        PID_Width = 0x4ddb6a2b,
        PID_Height = 0xf2e1e039,
        PID_Pitch = 0xe65e91dd,
        PID_Bytes = 0x70586cca,
        PID_Data = 0xdc15c5d,
        PID_PixelFormat = 0xc9797cbb,
        PID_COUNT = 8
    };

protected:
    epiSize_t GetPitch_Callback() const;
    epiSize_t GetBytes_Callback() const;
    void SetPixelFormat_Callback(mmImagePixelFormat value);

protected:
    epiU32 m_BPP{0};
    epiVec4u m_BPC{};
    epiSize_t m_Width{0};
    epiSize_t m_Height{0};
    epiArray<epiU8> m_Data{};
    mmImagePixelFormat m_PixelFormat{};

EPI_GENREGION_END(mmImage)

public:
    static /* TODO: add constexpr on c++20 */ epiU32 BPP(mmImagePixelFormat fmt);
    static constexpr epiVec4u BPC(mmImagePixelFormat fmt);
    static constexpr epiU32 ChannelsOf(mmImagePixelFormat fmt);

    static mmImage FromSeries2Df_ToGRAYSCALE(const dSeries2Df& series, epiBool clamp = true);
    static mmImage FromSeries2Df_ToGRAYSCALE(const dSeries2Df& series, const epiVec2f& minmax);

    static mmImage FromSeries2Df_ToR8G8B8(const dSeries2Df& seriesR,
                                          const dSeries2Df& seriesG,
                                          const dSeries2Df& seriesB,
                                          epiBool clampR = true,
                                          epiBool clampG = true,
                                          epiBool clampB = true);
    static mmImage FromSeries2Df_ToR8G8B8(const dSeries2Df& seriesR,
                                          const dSeries2Df& seriesG,
                                          const dSeries2Df& seriesB,
                                          const epiVec2f& minmaxR,
                                          const epiVec2f& minmaxG,
                                          const epiVec2f& minmaxB);

public:
    mmImage();
    mmImage(const dSeries2Df& series);
    mmImage(const dSeries2Df& series, epiFloat min, epiFloat max);

    mmImage Duplicate() const; // TODO: replace with auto-generated method

    dSeries1Df Histogram(mmImageGetColorValueCallback get = &Color::GetLumau) const;
    void HistogramEqualize();

    // TODO: implement BSNR, ISNR

    [[nodiscard]] mmImage Add(epiFloat scalar) const;
    [[nodiscard]] mmImage Add(epiFloat scalarR, epiFloat scalarG, epiFloat scalarB) const;
    [[nodiscard]] mmImage Add(const mmImage& image, dSeriesEdgeHandling edge = dSeriesEdgeHandling::Zero) const;
    [[nodiscard]] mmImage Mult(epiFloat scalar) const;
    [[nodiscard]] mmImage Mult(epiFloat scalarR, epiFloat scalarG, epiFloat scalarB) const;
    [[nodiscard]] mmImage Mult(const mmImage& image, dSeriesEdgeHandling edge = dSeriesEdgeHandling::Zero) const;
    [[nodiscard]] mmImage Log(epiFloat base) const;
    [[nodiscard]] mmImage Log(epiFloat baseR, epiFloat baseG, epiFloat baseB) const;
    [[nodiscard]] mmImage Exp(epiFloat base) const;
    [[nodiscard]] mmImage Exp(epiFloat baseR, epiFloat baseG, epiFloat baseB) const;

    void Threshold(epiU8 thrR, epiU8 thrG, epiU8 thrB, epiU8 thrA = 0);
    void Negative();
    void Gamma(epiFloat gammaR, epiFloat gammaG, epiFloat gammaB, epiFloat gammaA = 1.0f);
    void Contrast(epiS8 contrastR, epiS8 contrastG, epiS8 contrastB, epiS8 contrastA = 0);
    void ContrastStretch(epiU8 lowerR,
                         epiU8 upperR,
                         epiU8 lowerG,
                         epiU8 upperG,
                         epiU8 lowerB,
                         epiU8 upperB,
                         epiU8 lowerA = 0,
                         epiU8 upperA = 0);

    void Shift(epiS32 shiftR, epiS32 shiftG, epiS32 shiftB, epiS32 shiftA = 0);
    void ShiftRotate(epiS32 shiftR, epiS32 shiftG, epiS32 shiftB, epiS32 shiftA = 0);

    [[nodiscard]] mmImage Convolve(const dSeries2Df& kernel,
                                   dSeriesEdgeHandling edge = dSeriesEdgeHandling::Reflect,
                                   dSeries2Df::KernelPPCallback callback = nullptr) const;
    [[nodiscard]] mmImage Convolve(const dSeries2Df& kernelR,
                                   const dSeries2Df& kernelG,
                                   const dSeries2Df& kernelB,
                                   dSeriesEdgeHandling edge = dSeriesEdgeHandling::Reflect,
                                   dSeries2Df::KernelPPCallback callback = nullptr) const;

    [[nodiscard]] mmImage Correlate(const dSeries2Df& kernel,
                                    dSeriesEdgeHandling edge = dSeriesEdgeHandling::Reflect,
                                    dSeries2Df::KernelPPCallback callback = nullptr) const;
    [[nodiscard]] mmImage Correlate(const dSeries2Df& kernelR,
                                    const dSeries2Df& kernelG,
                                    const dSeries2Df& kernelB,
                                    dSeriesEdgeHandling edge = dSeriesEdgeHandling::Reflect,
                                    dSeries2Df::KernelPPCallback callback = nullptr) const;

    [[nodiscard]] mmImage Crop(const epiRect2u& crop, dSeriesEdgeHandling edge = dSeriesEdgeHandling::Error) const;

    [[nodiscard]] mmImage Median(epiSize_t windowSize, dSeriesEdgeHandling edge = dSeriesEdgeHandling::Reflect);

    void Overlap(const mmImage& image, const epiVec2s& shift, const Color& colorTint = Color(1.0f, 1.0f, 1.0f, 1.0f));

    epiU8& At(epiS32 index, epiU32 channel);
    epiU8& At(epiS32 r, epiS32 c, epiU32 channel);
    epiU8 At(epiS32 index, epiU32 channel, dSeriesEdgeHandling edge = dSeriesEdgeHandling::Error) const;
    epiU8 At(epiS32 r, epiS32 c, epiU32 channel, dSeriesEdgeHandling edge = dSeriesEdgeHandling::Error) const;
    Color At(epiS32 index, dSeriesEdgeHandling edge = dSeriesEdgeHandling::Error) const;
    Color At(epiS32 r, epiS32 c, dSeriesEdgeHandling edge = dSeriesEdgeHandling::Error) const;

    operator dSeries2Df() const;
    dSeries2Df ToSeries2Df(mmImageGetColorValueCallback get = &Color::GetLumau) const;

    mmImage ToGrayScaleR() const;
    mmImage ToGrayScaleG() const;
    mmImage ToGrayScaleB() const;
    mmImage ToGrayScaleA() const;
    mmImage ToGrayScaleMin() const;
    mmImage ToGrayScaleMax() const;
    mmImage ToGrayScaleHue() const;
    mmImage ToGrayScaleLuma() const;
    mmImage ToGrayScaleLuma601() const;
    mmImage ToGrayScaleLuma240() const;
    mmImage ToGrayScaleLuma709() const;
    mmImage ToGrayScaleLuma2020() const;
    mmImage ToGrayScaleBrightness() const;
    mmImage ToGrayScaleLightness() const;
    mmImage ToGrayScaleIntensity() const;
    mmImage ToGrayScaleChroma() const;
    mmImage ToGrayScaleSaturationB() const;
    mmImage ToGrayScaleSaturationL() const;
    mmImage ToGrayScaleSaturationI() const;

    mmImage ToR8G8B8() const;
    mmImage ToR8G8B8A8() const;

protected:
    mmImage ToGrayScale_Internal(mmImageGetColorValueCallback get) const;
};

EPI_NAMESPACE_END()
