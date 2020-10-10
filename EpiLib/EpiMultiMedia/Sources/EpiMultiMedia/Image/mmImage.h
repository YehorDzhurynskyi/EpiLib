#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/mmImage.hxx"
EPI_GENREGION_END(include)

#include "EpiMultimedia/mmMediaBase.h"

#include "EpiCore/Color.h"

#include "EpiData/Series/dSeries1Df.h"

EPI_NAMESPACE_BEGIN()

enum class mmImagePixelFormat : epiS32
{
EPI_GENREGION_BEGIN(mmImagePixelFormat)
    R8G8B8 = 0,
    GRAYSCALE = 1
EPI_GENREGION_END(mmImagePixelFormat)
};

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
        PID_Data = 0xdc15c5d,
        PID_PixelFormat = 0xc9797cbb,
        PID_COUNT = 5
    };

protected:
    void SetPixelFormat_Callback(mmImagePixelFormat value);

protected:
    epiU32 m_BitDepth{0};
    epiSize_t m_Width{0};
    epiSize_t m_Height{0};
    epiArray<epiU8> m_Data{};
    mmImagePixelFormat m_PixelFormat{};

EPI_GENREGION_END(mmImage)

public:
    static epiU32 BitDepthOf(mmImagePixelFormat fmt);
    static epiU32 ChannelsOf(mmImagePixelFormat fmt);

public:
    mmImage Duplicate() const; // TODO: replace with auto-generated method

    void Histogram(dSeries1Df& histogram) const;
    void HistogramPerChannel(dSeries1Df& histogramR, dSeries1Df& histogramG, dSeries1Df& histogramB) const;
    void HistogramEqualize();

    void Contrast(epiS8 contrast);
    void Contrast(epiS8 contrastR, epiS8 contrastG, epiS8 contrastB);
    void ContrastStretch(epiU8 lower, epiU8 upper);
    void ContrastStretch(epiU8 lowerR,
                         epiU8 upperR,
                         epiU8 lowerG,
                         epiU8 upperG,
                         epiU8 lowerB,
                         epiU8 upperB);

    void Shift(epiS32 shift);
    void Shift(epiS32 shiftR, epiS32 shiftG, epiS32 shiftB);
    void ShiftRotate(epiS32 shift);
    void ShiftRotate(epiS32 shiftR, epiS32 shiftG, epiS32 shiftB);

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

protected:
    mmImage ToGrayScale_Internal(epiU8 (Color::*get)() const) const;
};

EPI_NAMESPACE_END()
