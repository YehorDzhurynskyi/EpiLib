EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/mmImage.h"
#include "EpiMultimedia/Image/mmImage.cxx"
EPI_GENREGION_END(include)

namespace
{

EPI_NAMESPACE_USING()

using ColorGetCallback = epiU8(Color::*)() const;

// TODO: add c++20 ranges
template<typename Transform = Color(Color::*)() const, typename ...TransformArgs>
mmImage ConvertTo(const mmImage& from,
                  mmImagePixelFormat toFmt,
                  ColorGetCallback get[3],
                  const epiVec3s& strideFrom = {},
                  const epiVec3s& strideTo = {},
                  Transform&& transform = nullptr,
                  TransformArgs&& ...transformArgs)
{
    mmImage to;
    to.SetPixelFormat(toFmt);
    to.SetWidth(from.GetWidth());
    to.SetHeight(from.GetHeight());

    const epiU32 fromChannels = mmImage::ChannelsOf(from.GetPixelFormat());
    const epiArray<epiU8>& fromData = from.GetData();

    epiArray<epiU8>& toData = to.GetData();
    const epiU32 toChannels = mmImage::ChannelsOf(toFmt);

    epiAssert(fromData.Size() % fromChannels == 0);

    toData.Resize(fromData.Size() / (fromChannels / static_cast<epiFloat>(toChannels)));
    for (epiU32 i = 0; i < toData.Size() / toChannels; ++i)
    {
        Color color(fromData[i * fromChannels + strideFrom.x],
                    fromData[i * fromChannels + strideFrom.y],
                    fromData[i * fromChannels + strideFrom.z]);

        if (transform != nullptr)
        {
            color = (color.*transform)(std::forward<TransformArgs>(transformArgs)...);
        }

        for (epiU32 c = 0; c < toChannels; ++c)
        {
            toData[i * toChannels + strideTo[c]] = (color.*get[c])();
        }
    }

    return to;
}

template<typename Transform = Color(Color::*)() const, typename ...TransformArgs>
mmImage ConvertTo(const mmImage& from,
                  mmImagePixelFormat toFmt,
                  ColorGetCallback get,
                  const epiVec3s& strideFrom = {},
                  const epiVec3s& strideTo = {},
                  Transform&& transform = nullptr,
                  TransformArgs&& ...transformArgs)
{
    ColorGetCallback getcallbacks[3]{get, get, get};
    return ConvertTo(from, toFmt, getcallbacks, strideFrom, strideTo, transform, std::forward<TransformArgs>(transformArgs)...);
}

}

EPI_NAMESPACE_BEGIN()

epiU32 mmImage::BitDepthOf(mmImagePixelFormat fmt)
{
    switch (fmt)
    {
    case mmImagePixelFormat::R8G8B8: return 24;
    case mmImagePixelFormat::GRAYSCALE: return 8;
    }
}

epiU32 mmImage::ChannelsOf(mmImagePixelFormat fmt)
{
    switch (fmt)
    {
    case mmImagePixelFormat::R8G8B8: return 3;
    case mmImagePixelFormat::GRAYSCALE: return 1;
    }
}

mmImage mmImage::Duplicate() const
{
    mmImage image;
    image.SetWidth(GetWidth());
    image.SetHeight(GetHeight());
    image.SetPixelFormat(GetPixelFormat());

    image.GetData() = { GetData().begin(), GetData().end() };

    return image;
}

void mmImage::Histogram(dSeries1Df& histogram) const
{
    // TODO: adapt for any pixelformat
    epiAssert(GetPixelFormat() == mmImagePixelFormat::GRAYSCALE);

    histogram.Resize(256);

    for (epiU32 i = 0; i < 256; ++i)
    {
        histogram[i] = 0.0f;
    }

    for (const epiU8& x : GetData())
    {
        histogram[x] += 1.0f;
    }
}

void mmImage::HistogramPerChannel(dSeries1Df& histogramR, dSeries1Df& histogramG, dSeries1Df& histogramB) const
{
    // TODO: adapt for any pixelformat
    epiAssert(GetPixelFormat() == mmImagePixelFormat::R8G8B8);

    histogramR.Resize(256);
    histogramG.Resize(256);
    histogramB.Resize(256);

    for (epiU32 i = 0; i < 256; ++i)
    {
        histogramR[i] = 0.0f;
        histogramG[i] = 0.0f;
        histogramB[i] = 0.0f;
    }

    const epiArray<epiU8>& data = GetData();
    epiAssert(data.Size() % 3 == 0);
    for (epiU32 i = 0; i < data.Size() / 3; ++i)
    {
        histogramR[data[i * 3 + 0]] += 1.0f;
        histogramG[data[i * 3 + 1]] += 1.0f;
        histogramB[data[i * 3 + 2]] += 1.0f;
    }
}

void mmImage::HistogramEqualize()
{
    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE:
    {
        dSeries1Df histogram;
        Histogram(histogram);

        const epiFloat hSum = std::accumulate(histogram.begin(), histogram.end(), 0.0f);

        std::array<epiFloat, 256> hComp;

        epiAssert(histogram.GetSize() == hComp.size());

        epiFloat h = 0.0f;
        for (epiU32 i = 0; i < 256; ++i)
        {
            hComp[i] = ((h += histogram[i]) / hSum) * 255.0f;

            epiAssert(0.0f <= hComp[i] && hComp[i] <= 255.0f);
        }

        for (epiU8& x : GetData())
        {
            x = static_cast<epiU8>(hComp[x]);
        }
    } break;
    case mmImagePixelFormat::R8G8B8:
    {
        dSeries1Df histogramR;
        dSeries1Df histogramG;
        dSeries1Df histogramB;

        HistogramPerChannel(histogramR, histogramG, histogramB);

        const epiFloat hSumR = std::accumulate(histogramR.begin(), histogramR.end(), 0.0f);
        const epiFloat hSumG = std::accumulate(histogramG.begin(), histogramG.end(), 0.0f);
        const epiFloat hSumB = std::accumulate(histogramB.begin(), histogramB.end(), 0.0f);

        std::array<epiFloat, 256> hCompR;
        std::array<epiFloat, 256> hCompG;
        std::array<epiFloat, 256> hCompB;

        epiAssert(histogramR.GetSize() == hCompR.size());
        epiAssert(histogramG.GetSize() == hCompG.size());
        epiAssert(histogramB.GetSize() == hCompB.size());

        epiFloat hR = 0.0f;
        epiFloat hG = 0.0f;
        epiFloat hB = 0.0f;
        for (epiU32 i = 0; i < 256; ++i)
        {
            hCompR[i] = ((hR += histogramR[i]) / hSumR) * 255.0f;
            hCompG[i] = ((hG += histogramG[i]) / hSumG) * 255.0f;
            hCompB[i] = ((hB += histogramB[i]) / hSumB) * 255.0f;

            epiAssert(0.0f <= hCompR[i] && hCompR[i] <= 255.0f);
            epiAssert(0.0f <= hCompG[i] && hCompG[i] <= 255.0f);
            epiAssert(0.0f <= hCompB[i] && hCompB[i] <= 255.0f);
        }

        epiArray<epiU8>& data = GetData();
        epiAssert(data.Size() % 3 == 0);
        for (epiU32 i = 0; i < data.Size() / 3; ++i)
        {
            data[i * 3 + 0] = static_cast<epiU8>(hCompR[data[i * 3 + 0]]);
            data[i * 3 + 1] = static_cast<epiU8>(hCompG[data[i * 3 + 1]]);
            data[i * 3 + 2] = static_cast<epiU8>(hCompB[data[i * 3 + 2]]);
        }
    } break;
    }
}

void mmImage::Contrast(epiS8 contrast)
{
    Contrast(contrast, contrast, contrast);
}

void mmImage::Contrast(epiS8 contrastR, epiS8 contrastG, epiS8 contrastB)
{
    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE:
    {
        if (contrastR == contrastG && contrastG == contrastB)
        {
            epiArray<epiU8>& data = GetData();
            for (epiU32 i = 0; i < data.Size(); ++i)
            {
                data[i] = Color(data[i], data[i], data[i]).Contrast(contrastR, contrastG, contrastB).GetLumau();
            }
        }
        else
        {
            *this = ToR8G8B8();
            epiArray<epiU8>& data = GetData();
            for (epiU32 i = 0; i < data.Size() / 3; ++i)
            {
                const Color color = Color(data[i * 3 + 0], data[i * 3 + 1], data[i * 3 + 2]).Contrast(contrastR, contrastG, contrastB);

                data[i * 3 + 0] = color.GetRu();
                data[i * 3 + 1] = color.GetGu();
                data[i * 3 + 2] = color.GetBu();
            }
        }
    } break;
    case mmImagePixelFormat::R8G8B8:
    {
        epiArray<epiU8>& data = GetData();
        epiAssert(data.Size() % 3 == 0);
        for (epiU32 i = 0; i < data.Size() / 3; ++i)
        {
            const Color color = Color(data[i * 3 + 0], data[i * 3 + 1], data[i * 3 + 2]).Contrast(contrastR, contrastG, contrastB);
            data[i * 3 + 0] = color.GetRu();
            data[i * 3 + 1] = color.GetGu();
            data[i * 3 + 2] = color.GetBu();
        }
    } break;
    }
}

void mmImage::ContrastStretch(epiU8 lower, epiU8 upper)
{
    ContrastStretch(lower, upper, lower, upper, lower, upper);
}

void mmImage::ContrastStretch(epiU8 lowerR,
                              epiU8 upperR,
                              epiU8 lowerG,
                              epiU8 upperG,
                              epiU8 lowerB,
                              epiU8 upperB)
{
    if (lowerR >= upperR) epiLogWarn("lowerR=`{}` >= upperR=`{}`", lowerR, upperR);
    if (lowerG >= upperG) epiLogWarn("lowerG=`{}` >= upperG=`{}`", lowerG, upperG);
    if (lowerB >= upperB) epiLogWarn("lowerB=`{}` >= upperB=`{}`", lowerB, upperB);

    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE:
    {
        if (lowerR == lowerG && lowerG == lowerB &&
            upperR == upperG && upperG == upperB)
        {
            *this = ConvertTo(*this,
                              mmImagePixelFormat::GRAYSCALE,
                              &Color::GetLumau,
                              epiVec3s{0, 0, 0},
                              epiVec3s{0, 0, 0},
                              &Color::ContrastStretch,
                              lowerR,
                              upperR,
                              lowerG,
                              upperG,
                              lowerB,
                              upperB);
        }
        else
        {
            ColorGetCallback get[3]{&Color::GetRu, &Color::GetGu, &Color::GetBu};
            *this = ConvertTo(ToR8G8B8(),
                              mmImagePixelFormat::R8G8B8,
                              get,
                              epiVec3s{0, 1, 2},
                              epiVec3s{0, 1, 2},
                              &Color::ContrastStretch,
                              lowerR,
                              upperR,
                              lowerG,
                              upperG,
                              lowerB,
                              upperB);
        }
    } break;
    case mmImagePixelFormat::R8G8B8:
    {
        ColorGetCallback get[3]{&Color::GetRu, &Color::GetGu, &Color::GetBu};
        *this = ConvertTo(*this,
                          mmImagePixelFormat::R8G8B8,
                          get,
                          epiVec3s{0, 1, 2},
                          epiVec3s{0, 1, 2},
                          &Color::ContrastStretch,
                          lowerR,
                          upperR,
                          lowerG,
                          upperG,
                          lowerB,
                          upperB);
    } break;
    }
}

void mmImage::Shift(epiS32 shift)
{
    Shift(shift, shift, shift);
}

void mmImage::Shift(epiS32 shiftR, epiS32 shiftG, epiS32 shiftB)
{
}

void mmImage::ShiftRotate(epiS32 shift)
{
    ShiftRotate(shift, shift, shift);
}

void mmImage::ShiftRotate(epiS32 shiftR, epiS32 shiftG, epiS32 shiftB)
{
}

mmImage mmImage::ToGrayScale() const
{
    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE:
    {
        return ConvertTo(*this, mmImagePixelFormat::GRAYSCALE, &Color::GetLumau);
    } break;
    case mmImagePixelFormat::R8G8B8:
    {
        return ConvertTo(*this, mmImagePixelFormat::GRAYSCALE, &Color::GetLumau, epiVec3s{0, 1, 2});
    } break;
    }

    // TODO: retrieve string representation
    epiLogError("Unhandled pixel fmt=`{}` while converting image", GetPixelFormat());
    return mmImage{};
}

mmImage mmImage::ToGrayScaleR() const
{
    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE:
    {
        return ConvertTo(*this, mmImagePixelFormat::GRAYSCALE, &Color::GetRu);
    } break;
    case mmImagePixelFormat::R8G8B8:
    {
        return ConvertTo(*this, mmImagePixelFormat::GRAYSCALE, &Color::GetRu, epiVec3s{0, 0, 0});
    } break;
    }

    // TODO: retrieve string representation
    epiLogError("Unhandled pixel fmt=`{}` while converting image", GetPixelFormat());
    return mmImage{};
}

mmImage mmImage::ToGrayScaleG() const
{
    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE:
    {
        return ConvertTo(*this, mmImagePixelFormat::GRAYSCALE, &Color::GetGu);
    } break;
    case mmImagePixelFormat::R8G8B8:
    {
        return ConvertTo(*this, mmImagePixelFormat::GRAYSCALE, &Color::GetGu, epiVec3s{1, 1, 1});
    } break;
    }

    // TODO: retrieve string representation
    epiLogError("Unhandled pixel fmt=`{}` while converting image", GetPixelFormat());
    return mmImage{};
}

mmImage mmImage::ToGrayScaleB() const
{
    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE:
    {
        return ConvertTo(*this, mmImagePixelFormat::GRAYSCALE, &Color::GetBu);
    } break;
    case mmImagePixelFormat::R8G8B8:
    {
        return ConvertTo(*this, mmImagePixelFormat::GRAYSCALE, &Color::GetBu, epiVec3s{2, 2, 2});
    } break;
    }

    // TODO: retrieve string representation
    epiLogError("Unhandled pixel fmt=`{}` while converting image", GetPixelFormat());
    return mmImage{};
}

mmImage mmImage::ToGrayScaleHue() const
{
    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE:
    {
        return ConvertTo(*this, mmImagePixelFormat::GRAYSCALE, &Color::GetHueu);
    } break;
    case mmImagePixelFormat::R8G8B8:
    {
        return ConvertTo(*this, mmImagePixelFormat::GRAYSCALE, &Color::GetHueu, epiVec3s{0, 1, 2});
    } break;
    }

    // TODO: retrieve string representation
    epiLogError("Unhandled pixel fmt=`{}` while converting image", GetPixelFormat());
    return mmImage{};
}

mmImage mmImage::ToGrayScaleSaturation() const
{
    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE:
    {
        return ConvertTo(*this, mmImagePixelFormat::GRAYSCALE, &Color::GetSaturationBu);
    } break;
    case mmImagePixelFormat::R8G8B8:
    {
        return ConvertTo(*this, mmImagePixelFormat::GRAYSCALE, &Color::GetSaturationBu, epiVec3s{0, 1, 2});
    } break;
    }

    // TODO: retrieve string representation
    epiLogError("Unhandled pixel fmt=`{}` while converting image", GetPixelFormat());
    return mmImage{};
}

mmImage mmImage::ToGrayScaleBrightness() const
{
    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE:
    {
        return ConvertTo(*this, mmImagePixelFormat::GRAYSCALE, &Color::GetBrightnessu);
    } break;
    case mmImagePixelFormat::R8G8B8:
    {
        return ConvertTo(*this, mmImagePixelFormat::GRAYSCALE, &Color::GetBrightnessu, epiVec3s{0, 1, 2});
    } break;
    }

    // TODO: retrieve string representation
    epiLogError("Unhandled pixel fmt=`{}` while converting image", GetPixelFormat());
    return mmImage{};
}

mmImage mmImage::ToR8G8B8() const
{
    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::R8G8B8:
    {
        ColorGetCallback get[3]{&Color::GetRu, &Color::GetGu, &Color::GetBu};
        return ConvertTo(*this,
                         mmImagePixelFormat::R8G8B8,
                         get,
                         epiVec3s{0, 1, 2},
                         epiVec3s{0, 1, 2});
    } break;
    case mmImagePixelFormat::GRAYSCALE:
    {
        return ConvertTo(*this,
                         mmImagePixelFormat::R8G8B8,
                         &Color::GetLumau,
                         epiVec3s{0, 0, 0},
                         epiVec3s{0, 1, 2});
    } break;
    }

    // TODO: retrieve string representation
    epiLogError("Unhandled pixel fmt=`{}` while converting image", GetPixelFormat());
    return mmImage{};
}

#if 0 // TODO: implement, property grid can't handle it properly
epiVec2u mmImage::GetSize_Callback() const
{
    return epiVec2u{GetWidth(), GetHeight()};
}

void mmImage::SetSize_Callback(const epiVec2u& value)
{
    SetWidth(value.x);
    SetHeight(value.y);
}
#endif

void mmImage::SetPixelFormat_Callback(mmImagePixelFormat value)
{
    m_PixelFormat = value;
    m_BitDepth = mmImage::BitDepthOf(value);
}

EPI_NAMESPACE_END()
