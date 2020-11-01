#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/mmImage.hxx"
EPI_GENREGION_END(include)

#include "EpiMultimedia/mmMediaBase.h"

#include "EpiCore/Color.h"

#include "EpiData/Series/dSeries1Df.h"
#include "EpiData/Series/dSeries2Dc.h"

#include <opencv2/core.hpp>

EPI_NAMESPACE_BEGIN()

enum class mmImagePixelFormat : epiS32
{
EPI_GENREGION_BEGIN(mmImagePixelFormat)
    R8G8B8 = 0,
    R8G8B8A8 = 1,
    GRAYSCALE = 2
EPI_GENREGION_END(mmImagePixelFormat)
};

enum class mmImageEdgeHandling : epiS32
{
EPI_GENREGION_BEGIN(mmImageEdgeHandling)
    Error = 0,
    Zero = 1,
    FF = 2,
    Extend = 3,
    Wrap = 4,
    Mirror = 5
EPI_GENREGION_END(mmImageEdgeHandling)
};

using mmImageGetColorValueCallback = epiU8(Color::*)() const;

class dSeries2Df;
class mmImage : public mmMediaBase
{
EPI_GENREGION_BEGIN(mmImage)

EPI_GENHIDDEN_mmImage()

public:
    constexpr static epiMetaTypeID TypeID{0x1b93299};

    enum mmImage_PIDs
    {
        PID_BitDepth = 0x7d479868,
        PID_Width = 0x4ddb6a2b,
        PID_Height = 0xf2e1e039,
        PID_Pitch = 0xe65e91dd,
        PID_Data = 0xdc15c5d,
        PID_PixelFormat = 0xc9797cbb,
        PID_COUNT = 6
    };

protected:
    epiSize_t GetPitch_Callback() const;
    void SetPixelFormat_Callback(mmImagePixelFormat value);

protected:
    epiU32 m_BitDepth{0};
    epiSize_t m_Width{0};
    epiSize_t m_Height{0};
    epiArray<epiU8> m_Data{};
    mmImagePixelFormat m_PixelFormat{};

EPI_GENREGION_END(mmImage)

public:
    static constexpr epiU32 BitDepthOf(mmImagePixelFormat fmt);
    static constexpr epiU32 ChannelsOf(mmImagePixelFormat fmt);

public:
    mmImage() = default;
    mmImage(const dSeries2Df& series);

    mmImage Duplicate() const; // TODO: replace with auto-generated method

    dSeries1Df Histogram(mmImageGetColorValueCallback get = &Color::GetLumau) const;
    void HistogramEqualize();

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

    void ConvolveWith(const cv::Mat& kernel, mmImageEdgeHandling edge = mmImageEdgeHandling::Extend);
    void ConvolveWith(const cv::Mat& kernelR, const cv::Mat& kernelG, const cv::Mat& kernelB, mmImageEdgeHandling edge = mmImageEdgeHandling::Extend);

    mmImage Crop(const epiRect2u& crop, mmImageEdgeHandling edge = mmImageEdgeHandling::Error) const;

    void Overlap(const mmImage& image, const epiVec2s& shift, const Color& colorTint = Color(1.0f, 1.0f, 1.0f, 1.0f));

    epiU8& At(epiS32 index, epiU32 channel);
    epiU8& At(epiS32 r, epiS32 c, epiU32 channel);
    epiU8 At(epiS32 index, epiU32 channel, mmImageEdgeHandling edge = mmImageEdgeHandling::Error) const;
    epiU8 At(epiS32 r, epiS32 c, epiU32 channel, mmImageEdgeHandling edge = mmImageEdgeHandling::Error) const;
    Color At(epiS32 index, mmImageEdgeHandling edge = mmImageEdgeHandling::Error) const;
    Color At(epiS32 r, epiS32 c, mmImageEdgeHandling edge = mmImageEdgeHandling::Error) const;

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
