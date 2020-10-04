EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/mmImage.h"
#include "EpiMultimedia/Image/mmImage.cxx"
EPI_GENREGION_END(include)

#include "EpiCore/Color.h"

EPI_NAMESPACE_BEGIN()

epiU32 mmImage::BitDepthOf(mmImagePixelFormat fmt)
{
    switch (fmt)
    {
    case mmImagePixelFormat::R8G8B8: return 24;
    case mmImagePixelFormat::GRAYSCALE: return 8;
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
    epiAssert(lowerR <= upperR);
    epiAssert(lowerG <= upperG);
    epiAssert(lowerB <= upperB);

    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE:
    {
        if (lowerR == lowerG && lowerG == lowerB &&
            upperR == upperG && upperG == upperB)
        {
            epiArray<epiU8>& data = GetData();
            for (epiU32 i = 0; i < data.Size(); ++i)
            {
                data[i] = Color(data[i], data[i], data[i]).ContrastStretch(lowerR, upperR, lowerG, upperG, lowerB, upperB).GetLumau();
            }
        }
        else
        {
            *this = ToR8G8B8();
            epiArray<epiU8>& data = GetData();
            for (epiU32 i = 0; i < data.Size() / 3; ++i)
            {
                const Color color = Color(data[i * 3 + 0], data[i * 3 + 1], data[i * 3 + 2]).ContrastStretch(lowerR, upperR, lowerG, upperG, lowerB, upperB);

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
            const Color color = Color(data[i * 3 + 0], data[i * 3 + 1], data[i * 3 + 2]).ContrastStretch(lowerR, upperR, lowerG, upperG, lowerB, upperB);

            data[i * 3 + 0] = color.GetRu();
            data[i * 3 + 1] = color.GetGu();
            data[i * 3 + 2] = color.GetBu();
        }
    } break;
    }
}

mmImage mmImage::ToGrayScale() const
{
    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE:
    {
        return GrayScaleToGrayScale();
    } break;
    case mmImagePixelFormat::R8G8B8:
    {
        return R8G8B8ToGrayScale(0, 1, 2);
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
        return GrayScaleToGrayScale();
    } break;
    case mmImagePixelFormat::R8G8B8:
    {
        return R8G8B8ToGrayScale(0, 0, 0);
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
        return GrayScaleToGrayScale();
    } break;
    case mmImagePixelFormat::R8G8B8:
    {
        return R8G8B8ToGrayScale(1, 1, 1);
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
        return GrayScaleToGrayScale();
    } break;
    case mmImagePixelFormat::R8G8B8:
    {
        return R8G8B8ToGrayScale(2, 2, 2);
    } break;
    }

    // TODO: retrieve string representation
    epiLogError("Unhandled pixel fmt=`{}` while converting image", GetPixelFormat());
    return mmImage{};
}

mmImage mmImage::GrayScaleToGrayScale() const
{
    mmImage to;
    to.SetPixelFormat(mmImagePixelFormat::GRAYSCALE);
    to.SetWidth(GetWidth());
    to.SetHeight(GetHeight());

    const epiArray<epiU8>& fromData = GetData();
    epiArray<epiU8>& toData = to.GetData();

    toData.Resize(fromData.Size());
    for (epiU32 i = 0; i < fromData.Size(); ++i)
    {
        toData[i] = fromData[i];
    }

    return to;
}

mmImage mmImage::R8G8B8ToGrayScale(epiS32 strideR, epiS32 strideG, epiS32 strideB) const
{
    mmImage to;
    to.SetPixelFormat(mmImagePixelFormat::GRAYSCALE);
    to.SetWidth(GetWidth());
    to.SetHeight(GetHeight());

    const epiArray<epiU8>& fromData = GetData();
    epiArray<epiU8>& toData = to.GetData();
    epiAssert(fromData.Size() % 3 == 0);

    toData.Resize(fromData.Size() / 3);
    for (epiU32 i = 0; i < toData.Size(); ++i)
    {
        toData[i] = Color(fromData[i * 3 + strideR], fromData[i * 3 + strideG], fromData[i * 3 + strideB]).GetLumau();
    }

    return to;
}

mmImage mmImage::ToR8G8B8() const
{
    mmImage to;
    to.SetPixelFormat(mmImagePixelFormat::R8G8B8);
    to.SetWidth(GetWidth());
    to.SetHeight(GetHeight());

    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::R8G8B8:
    {
        const epiArray<epiU8>& fromData = GetData();
        epiArray<epiU8>& toData = to.GetData();

        toData.Resize(fromData.Size());
        for (epiU32 i = 0; i < fromData.Size(); ++i)
        {
            toData[i] = fromData[i];
        }
} break;
    case mmImagePixelFormat::GRAYSCALE:
    {
        const epiArray<epiU8>& fromData = GetData();
        epiArray<epiU8>& toData = to.GetData();

        toData.Resize(fromData.Size() * 3);
        for (epiU32 i = 0; i < toData.Size() / 3; ++i)
        {
            toData[i * 3 + 0] = fromData[i];
            toData[i * 3 + 1] = fromData[i];
            toData[i * 3 + 2] = fromData[i];
        }
    } break;
    }

    return to;
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
