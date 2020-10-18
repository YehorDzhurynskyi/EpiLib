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
                  ColorGetCallback get[4],
                  const epiVec4s& strideFrom = {},
                  const epiVec4s& strideTo = {},
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
        Color color;
        switch (from.GetPixelFormat())
        {
        case mmImagePixelFormat::GRAYSCALE:
        {
            const epiU8 col = fromData[i];

            color.SetRu(col);
            color.SetGu(col);
            color.SetBu(col);
        } break;
        case mmImagePixelFormat::R8G8B8:
        {
            color.SetAu(0xff);
        }
        case mmImagePixelFormat::R8G8B8A8:
        {
            for (epiU32 c = 0; c < fromChannels; ++c)
            {
                color.GetColor()[c] = fromData[i * fromChannels + strideFrom[c]] / 255.0f;
            }
        }
        }

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
                  ColorGetCallback getR,
                  ColorGetCallback getG,
                  ColorGetCallback getB,
                  const epiVec4s& strideFrom = {},
                  const epiVec4s& strideTo = {},
                  Transform&& transform = nullptr,
                  TransformArgs&& ...transformArgs)
{
    ColorGetCallback getcallbacks[4]{getR, getG, getB, nullptr};
    return ConvertTo(from, toFmt, getcallbacks, strideFrom, strideTo, transform, std::forward<TransformArgs>(transformArgs)...);
}

template<typename Transform = Color(Color::*)() const, typename ...TransformArgs>
mmImage ConvertTo(const mmImage& from,
                  mmImagePixelFormat toFmt,
                  ColorGetCallback get,
                  const epiVec4s& strideFrom = {},
                  const epiVec4s& strideTo = {},
                  Transform&& transform = nullptr,
                  TransformArgs&& ...transformArgs)
{
    ColorGetCallback getcallbacks[4]{get, get, get, get};
    return ConvertTo(from, toFmt, getcallbacks, strideFrom, strideTo, transform, std::forward<TransformArgs>(transformArgs)...);
}

}

EPI_NAMESPACE_BEGIN()

constexpr epiU32 mmImage::BitDepthOf(mmImagePixelFormat fmt)
{
    return ChannelsOf(fmt) * 8;
}

constexpr epiU32 mmImage::ChannelsOf(mmImagePixelFormat fmt)
{
    switch (fmt)
    {
    case mmImagePixelFormat::R8G8B8: return 3;
    case mmImagePixelFormat::R8G8B8A8: return 4;
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

void mmImage::Histogram(dSeries1Df& histogram, epiU8(Color::*get)() const) const
{
    histogram.Resize(256);

    for (epiU32 i = 0; i < 256; ++i)
    {
        histogram[i] = 0.0f;
    }

    for (epiS32 r = 0; r < GetHeight(); ++r)
    {
        for (epiS32 c = 0; c < GetWidth(); ++c)
        {
            const Color color = At(r, c, mmImageEdgeHandling::Error);
            histogram[(color.*get)()] += 1.0f;
        }
    }
}

void mmImage::HistogramEqualize()
{
    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE:
    {
        dSeries1Df histogram;
        Histogram(histogram, &Color::GetLumau);

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

        Histogram(histogramR, &Color::GetRu);
        Histogram(histogramG, &Color::GetGu);
        Histogram(histogramB, &Color::GetBu);

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

void mmImage::Threshold(epiU8 thrR, epiU8 thrG, epiU8 thrB, epiU8 thrA)
{
    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE:
    {
        if (thrR == thrG && thrG == thrB && thrA == 0)
        {
            *this = ConvertTo(*this,
                              mmImagePixelFormat::GRAYSCALE,
                              &Color::GetLumau,
                              epiVec4s{0, 0, 0, 0},
                              epiVec4s{0, 0, 0, 0},
                              &Color::Threshold,
                              thrR,
                              thrG,
                              thrB,
                              thrA);
            break;
        }
        else
        {
            *this = ToR8G8B8();
        }
    }
    case mmImagePixelFormat::R8G8B8:
    {
        if (thrA == 0)
        {
        ColorGetCallback get[]{&Color::GetRu, &Color::GetGu, &Color::GetBu};
        *this = ConvertTo(*this,
                          mmImagePixelFormat::R8G8B8,
                          get,
                          epiVec4s{0, 1, 2, 3},
                          epiVec4s{0, 1, 2, 3},
                          &Color::Threshold,
                          thrR,
                          thrG,
                          thrB,
                          thrA);
            break;
        }
        else
        {
            *this = ToR8G8B8A8();
        }
    }
    case mmImagePixelFormat::R8G8B8A8:
    {
        ColorGetCallback get[]{&Color::GetRu, &Color::GetGu, &Color::GetBu, &Color::GetAu};
        *this = ConvertTo(*this,
                          mmImagePixelFormat::R8G8B8A8,
                          get,
                          epiVec4s{0, 1, 2, 3},
                          epiVec4s{0, 1, 2, 3},
                          &Color::Threshold,
                          thrR,
                          thrG,
                          thrB,
                          thrA);
    } break;
    }
}

void mmImage::Negative()
{
    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE:
    {
        *this = ConvertTo(*this,
                          mmImagePixelFormat::GRAYSCALE,
                          &Color::GetLumau,
                          epiVec4s{0, 0, 0, 0},
                          epiVec4s{0, 0, 0, 0},
                          &Color::Negative);

    } break;
    case mmImagePixelFormat::R8G8B8:
    {
        *this = ConvertTo(*this,
                          mmImagePixelFormat::R8G8B8,
                          &Color::GetRu,
                          &Color::GetGu,
                          &Color::GetBu,
                          epiVec4s{0, 1, 2, 3},
                          epiVec4s{0, 1, 2, 3},
                          &Color::Negative);
    } break;
    case mmImagePixelFormat::R8G8B8A8:
    {
        ColorGetCallback get[]{&Color::GetRu, &Color::GetGu, &Color::GetBu, &Color::GetAu};
        *this = ConvertTo(*this,
                          mmImagePixelFormat::R8G8B8A8,
                          get,
                          epiVec4s{0, 1, 2, 3},
                          epiVec4s{0, 1, 2, 3},
                          &Color::Negative);
    } break;
    }
}

void mmImage::Gamma(epiFloat gammaR, epiFloat gammaG, epiFloat gammaB, epiFloat gammaA)
{
    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE:
    {
        if (epiEqual(gammaR, gammaG) && epiEqual(gammaG, gammaB) && epiEqual(gammaA, 1.0f))
        {
            *this = ConvertTo(*this,
                              mmImagePixelFormat::GRAYSCALE,
                              &Color::GetLumau,
                              epiVec4s{0, 0, 0, 0},
                              epiVec4s{0, 0, 0, 0},
                              &Color::Gamma,
                              gammaR,
                              gammaG,
                              gammaB,
                              gammaA);
            break;
        }
        else
        {
            *this = ToR8G8B8();
        }
    };
    case mmImagePixelFormat::R8G8B8:
    {
        if (epiEqual(gammaA, 1.0f))
        {
            *this = ConvertTo(*this,
                              mmImagePixelFormat::R8G8B8,
                              &Color::GetRu,
                              &Color::GetGu,
                              &Color::GetBu,
                              epiVec4s{0, 1, 2, 3},
                              epiVec4s{0, 1, 2, 3},
                              &Color::Gamma,
                              gammaR,
                              gammaG,
                              gammaB,
                              gammaA);
            break;
        }
        else
        {
            *this = ToR8G8B8A8();
        }
    }
    case mmImagePixelFormat::R8G8B8A8:
    {
        ColorGetCallback get[]{&Color::GetRu, &Color::GetGu, &Color::GetBu, &Color::GetAu};
        *this = ConvertTo(*this,
                          mmImagePixelFormat::R8G8B8A8,
                          get,
                          epiVec4s{0, 1, 2, 3},
                          epiVec4s{0, 1, 2, 3},
                          &Color::Gamma,
                          gammaR,
                          gammaG,
                          gammaB,
                          gammaA);
    } break;
    }
}

void mmImage::Contrast(epiS8 contrastR, epiS8 contrastG, epiS8 contrastB, epiS8 contrastA)
{
    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE:
    {
        if (contrastR == contrastG && contrastG == contrastB && contrastA == 0)
        {
            *this = ConvertTo(*this,
                              mmImagePixelFormat::GRAYSCALE,
                              &Color::GetLumau,
                              epiVec4s{0, 0, 0, 0},
                              epiVec4s{0, 0, 0, 0},
                              &Color::Contrast,
                              contrastR,
                              contrastG,
                              contrastB,
                              contrastA);
            break;
        }
        else
        {
            *this = ToR8G8B8();
        }
    }
    case mmImagePixelFormat::R8G8B8:
    {
        if (contrastA == 0)
        {
            *this = ConvertTo(*this,
                              mmImagePixelFormat::R8G8B8,
                              &Color::GetRu,
                              &Color::GetGu,
                              &Color::GetBu,
                              epiVec4s{0, 1, 2, 3},
                              epiVec4s{0, 1, 2, 3},
                              &Color::Contrast,
                              contrastR,
                              contrastG,
                              contrastB,
                              contrastA);
            break;
        }
        else
        {
            *this = ToR8G8B8A8();
        }
    }
    case mmImagePixelFormat::R8G8B8A8:
    {
        ColorGetCallback get[]{&Color::GetRu, &Color::GetGu, &Color::GetBu, &Color::GetAu};
        *this = ConvertTo(*this,
                          mmImagePixelFormat::R8G8B8A8,
                          get,
                          epiVec4s{0, 1, 2, 3},
                          epiVec4s{0, 1, 2, 3},
                          &Color::Contrast,
                          contrastR,
                          contrastG,
                          contrastB,
                          contrastA);
    } break;
    }
}

void mmImage::ContrastStretch(epiU8 lowerR,
                              epiU8 upperR,
                              epiU8 lowerG,
                              epiU8 upperG,
                              epiU8 lowerB,
                              epiU8 upperB,
                              epiU8 lowerA,
                              epiU8 upperA)
{
    if (lowerR >= upperR) epiLogWarn("lowerR=`{}` >= upperR=`{}`", lowerR, upperR);
    if (lowerG >= upperG) epiLogWarn("lowerG=`{}` >= upperG=`{}`", lowerG, upperG);
    if (lowerB >= upperB) epiLogWarn("lowerB=`{}` >= upperB=`{}`", lowerB, upperB);
    if (lowerA >= upperA) epiLogWarn("lowerA=`{}` >= upperA=`{}`", lowerA, upperA);

    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE:
    {
        if (lowerR == lowerG && lowerG == lowerB &&
            upperR == upperG && upperG == upperB &&
            lowerA == 0 && upperA == 0)
        {
            *this = ConvertTo(*this,
                              mmImagePixelFormat::GRAYSCALE,
                              &Color::GetLumau,
                              epiVec4s{0, 0, 0, 0},
                              epiVec4s{0, 0, 0, 0},
                              &Color::ContrastStretch,
                              lowerR,
                              upperR,
                              lowerG,
                              upperG,
                              lowerB,
                              upperB,
                              lowerA,
                              upperA);
            break;
        }
        else
        {
            *this = ToR8G8B8();
        }
    }
    case mmImagePixelFormat::R8G8B8:
    {
        if (lowerA == 0 && upperA == 0)
        {
            *this = ConvertTo(*this,
                              mmImagePixelFormat::R8G8B8,
                              &Color::GetRu,
                              &Color::GetGu,
                              &Color::GetBu,
                              epiVec4s{0, 1, 2, 3},
                              epiVec4s{0, 1, 2, 3},
                              &Color::ContrastStretch,
                              lowerR,
                              upperR,
                              lowerG,
                              upperG,
                              lowerB,
                              upperB,
                              lowerA,
                              upperA);
            break;
        }
        else
        {
            *this = ToR8G8B8A8();
        }
    }
    case mmImagePixelFormat::R8G8B8A8:
    {
        ColorGetCallback get[]{&Color::GetRu, &Color::GetGu, &Color::GetBu, &Color::GetAu};
        *this = ConvertTo(*this,
                          mmImagePixelFormat::R8G8B8A8,
                          get,
                          epiVec4s{0, 1, 2, 3},
                          epiVec4s{0, 1, 2, 3},
                          &Color::ContrastStretch,
                          lowerR,
                          upperR,
                          lowerG,
                          upperG,
                          lowerB,
                          upperB,
                          lowerA,
                          upperA);
    } break;
    }
}

void mmImage::Shift(epiS32 shiftR, epiS32 shiftG, epiS32 shiftB, epiS32 shiftA)
{
    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE:
    {
        if (shiftR == shiftG && shiftG == shiftB && shiftA == 0)
        {
            *this = ConvertTo(*this,
                              mmImagePixelFormat::GRAYSCALE,
                              &Color::GetLumau,
                              epiVec4s{0, 0, 0, 0},
                              epiVec4s{0, 0, 0, 0},
                              &Color::Shift,
                              shiftR,
                              shiftG,
                              shiftB,
                              shiftA);
            break;
        }
        else
        {
            *this = ToR8G8B8();
        }
    }
    case mmImagePixelFormat::R8G8B8:
    {
        if (shiftA == 0)
        {
            *this = ConvertTo(*this,
                              mmImagePixelFormat::R8G8B8,
                              &Color::GetRu,
                              &Color::GetGu,
                              &Color::GetBu,
                              epiVec4s{0, 1, 2, 3},
                              epiVec4s{0, 1, 2, 3},
                              &Color::Shift,
                              shiftR,
                              shiftG,
                              shiftB,
                              shiftA);
            break;
        }
        else
        {
            *this = ToR8G8B8A8();
        }
    }
    case mmImagePixelFormat::R8G8B8A8:
    {
        ColorGetCallback get[]{&Color::GetRu, &Color::GetGu, &Color::GetBu, &Color::GetAu};
        *this = ConvertTo(*this,
                          mmImagePixelFormat::R8G8B8A8,
                          get,
                          epiVec4s{0, 1, 2, 3},
                          epiVec4s{0, 1, 2, 3},
                          &Color::Shift,
                          shiftR,
                          shiftG,
                          shiftB,
                          shiftA);
    } break;
    }
}

void mmImage::ShiftRotate(epiS32 shiftR, epiS32 shiftG, epiS32 shiftB, epiS32 shiftA)
{
    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE:
    {
        if (shiftR == shiftG && shiftG == shiftB && shiftA == 0)
        {
            *this = ConvertTo(*this,
                              mmImagePixelFormat::GRAYSCALE,
                              &Color::GetLumau,
                              epiVec4s{0, 0, 0, 0},
                              epiVec4s{0, 0, 0, 0},
                              &Color::ShiftRotate,
                              shiftR,
                              shiftG,
                              shiftB,
                              shiftA);
            break;
        }
        else
        {
            *this = ToR8G8B8();
        }
    }
    case mmImagePixelFormat::R8G8B8:
    {
        if (shiftA == 0)
        {
            *this = ConvertTo(*this,
                              mmImagePixelFormat::R8G8B8,
                              &Color::GetRu,
                              &Color::GetGu,
                              &Color::GetBu,
                              epiVec4s{0, 1, 2, 3},
                              epiVec4s{0, 1, 2, 3},
                              &Color::ShiftRotate,
                              shiftR,
                              shiftG,
                              shiftB,
                              shiftA);
            break;
        }
        else
        {
            *this = ToR8G8B8A8();
        }
    }
    case mmImagePixelFormat::R8G8B8A8:
    {
        ColorGetCallback get[]{&Color::GetRu, &Color::GetGu, &Color::GetBu, &Color::GetAu};
        *this = ConvertTo(*this,
                          mmImagePixelFormat::R8G8B8A8,
                          get,
                          epiVec4s{0, 1, 2, 3},
                          epiVec4s{0, 1, 2, 3},
                          &Color::ShiftRotate,
                          shiftR,
                          shiftG,
                          shiftB,
                          shiftA);
    } break;
    }
}

void mmImage::ConvolveWith(const cv::Mat& kernel, mmImageEdgeHandling edge)
{
    ConvolveWith(kernel, kernel, kernel, edge);
}

void mmImage::ConvolveWith(const cv::Mat& kernelR, const cv::Mat& kernelG, const cv::Mat& kernelB, mmImageEdgeHandling edge)
{
    epiAssert(kernelR.channels() == 1);
    epiAssert(kernelG.channels() == 1);
    epiAssert(kernelB.channels() == 1);
    epiAssert(kernelR.depth() == CV_32F);
    epiAssert(kernelG.depth() == CV_32F);
    epiAssert(kernelB.depth() == CV_32F);

    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE:
    {
        const epiBool areEqualKernelRG = kernelR.rows == kernelG.rows &&
                                         kernelR.cols == kernelG.cols &&
                                         std::equal(kernelR.begin<epiFloat>(),
                                                    kernelR.end<epiFloat>(),
                                                    kernelG.begin<epiFloat>(),
                                                    kernelG.end<epiFloat>(),
                                                    [](epiFloat lhs, epiFloat rhs)
        {
            return epiEqual(lhs, rhs);
        });

        const epiBool areEqualKernelGB = kernelG.rows == kernelB.rows &&
                                         kernelG.cols == kernelB.cols &&
                                         std::equal(kernelG.begin<epiFloat>(),
                                                    kernelG.end<epiFloat>(),
                                                    kernelB.begin<epiFloat>(),
                                                    kernelB.end<epiFloat>(),
                                                    [](epiFloat lhs, epiFloat rhs)
        {
            return epiEqual(lhs, rhs);
        });

        if (areEqualKernelRG && areEqualKernelGB)
        {
            for (epiS32 r = 0; r < GetHeight(); ++r)
            {
                for (epiS32 c = 0; c < GetWidth(); ++c)
                {
                    epiFloat sum = 0;
                    for (epiS32 kR = 0; kR < kernelR.rows; ++kR)
                    {
                        for (epiS32 kC = 0; kC < kernelR.cols; ++kC)
                        {
                            const epiU8 pix = At(r + kR - kernelR.rows / 2, c + kC - kernelR.cols / 2, 0, edge);
                            const epiFloat pixKernel = kernelR.at<epiFloat>(kR, kC);

                            sum += pix * pixKernel;
                        }
                    }
                    At(r, c, 0) = static_cast<epiU8>(std::clamp(sum, 0.0f, 255.0f));
                }
            }
            break;
        }
        else
        {
            *this = ToR8G8B8();
        }
    }
    case mmImagePixelFormat::R8G8B8:
    case mmImagePixelFormat::R8G8B8A8:
    {
        for (epiS32 r = 0; r < GetHeight(); ++r)
        {
            for (epiS32 c = 0; c < GetWidth(); ++c)
            {
                epiFloat sumR = 0;
                for (epiS32 kR = 0; kR < kernelR.rows; ++kR)
                {
                    for (epiS32 kC = 0; kC < kernelR.cols; ++kC)
                    {
                        const epiU8 pix = At(r + kR - kernelR.rows / 2, c + kC - kernelR.cols / 2, 0, edge);
                        const epiFloat pixKernel = kernelR.at<epiFloat>(kR, kC);

                        sumR += pix * pixKernel;
                    }
                }
                At(r, c, 0) = static_cast<epiU8>(std::clamp(sumR, 0.0f, 255.0f));

                epiFloat sumG = 0;
                for (epiS32 kR = 0; kR < kernelG.rows; ++kR)
                {
                    for (epiS32 kC = 0; kC < kernelG.cols; ++kC)
                    {
                        const epiU8 pix = At(r + kR - kernelG.rows / 2, c + kC - kernelG.cols / 2, 1, edge);
                        const epiFloat pixKernel = kernelG.at<epiFloat>(kR, kC);

                        sumG += pix * pixKernel;
                    }
                }
                At(r, c, 1) = static_cast<epiU8>(std::clamp(sumG, 0.0f, 255.0f));

                epiFloat sumB = 0;
                for (epiS32 kR = 0; kR < kernelB.rows; ++kR)
                {
                    for (epiS32 kC = 0; kC < kernelB.cols; ++kC)
                    {
                        const epiU8 pix = At(r + kR - kernelB.rows / 2, c + kC - kernelB.cols / 2, 2, edge);
                        const epiFloat pixKernel = kernelB.at<epiFloat>(kR, kC);

                        sumB += pix * pixKernel;
                    }
                }
                At(r, c, 2) = static_cast<epiU8>(std::clamp(sumB, 0.0f, 255.0f));
            }
        }
    } break;
    }
}

mmImage mmImage::Crop(const epiRect2u& crop, mmImageEdgeHandling edge) const
{
    const epiS32 cX1 = crop.Left;
    const epiS32 cY1 = std::min(static_cast<epiS32>(crop.Bottom + crop.GetHeight()), static_cast<epiS32>(GetHeight()));
    const epiS32 cX2 = std::min(static_cast<epiS32>(crop.Left + crop.GetWidth()), static_cast<epiS32>(GetWidth()));
    const epiS32 cY2 = crop.Bottom;

    if (cX1 == cX2 || cY1 == cY2)
    {
        return mmImage{};
    }

    epiAssert(cY1 > cY2);
    epiAssert(cX1 < cX2);

    mmImage image;
    image.SetPixelFormat(GetPixelFormat());
    image.SetWidth(cX2 - cX1);
    image.SetHeight(cY1 - cY2);

    epiArray<epiU8>& data = image.GetData();
    data.Resize(image.GetHeight() * image.GetPitch());
    for (epiS32 r = 0, cR = cY2; cR < cY1; ++cR, ++r)
    {
        const epiS32 rr = image.GetHeight() - 1 - r;
        const epiS32 cRR = GetHeight() - 1 - cR;

        for (epiS32 c = 0, cC = cX1; cC < cX2; ++cC, ++c)
        {
            for (epiS32 ch = 0; ch < ChannelsOf(image.GetPixelFormat()); ++ch)
            {
                image.At(rr, c, ch) = At(cRR, cC, ch, edge);
            }
        }
    }

    return image;
}

void mmImage::Overlap(const mmImage& image, const epiVec2s& shift, const Color& colorTint)
{
    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE:
    {
        if (colorTint.GetRu() == colorTint.GetGu() && colorTint.GetGu() == colorTint.GetBu() && colorTint.GetAu() == 0xff)
        {
            for (epiS32 r = 0; r < image.GetHeight(); ++r)
            {
                for (epiS32 c = 0; c < image.GetWidth(); ++c)
                {
                    const Color color = image.At(r, c, mmImageEdgeHandling::Error) * colorTint;

                    At(r - shift.y, c + shift.x, 0) = color.GetLumau();
                }
            }

            break;
        }
        else
        {
            *this = ToR8G8B8();
        }
    }
    case mmImagePixelFormat::R8G8B8:
    {
        for (epiS32 r = 0; r < image.GetHeight(); ++r)
        {
            const epiS32 rr = r - shift.y;
            if (rr != std::clamp(rr, 0, static_cast<epiS32>(GetHeight() - 1)))
            {
                continue;
            }

            for (epiS32 c = 0; c < image.GetWidth(); ++c)
            {
                const epiS32 cc = c + shift.x;
                if (cc != std::clamp(cc, 0, static_cast<epiS32>(GetWidth() - 1)))
                {
                    continue;
                }

                const Color colorSrc = image.At(r, c, mmImageEdgeHandling::Error) * colorTint;
                const Color colorDst = At(rr, cc, mmImageEdgeHandling::Error);
                const Color color = colorDst.Blend(colorSrc);

                At(rr, cc, 0) = color.GetRu();
                At(rr, cc, 1) = color.GetGu();
                At(rr, cc, 2) = color.GetBu();
            }
        }
    } break;
    }
}

dSeries2Dc mmImage::DFT() const
{
    using namespace std::complex_literals;

    epiAssert(GetPixelFormat() == mmImagePixelFormat::GRAYSCALE);

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
}

epiU8& mmImage::At(epiS32 r, epiS32 c, epiU32 channel)
{
    const epiS32 w = static_cast<epiS32>(GetWidth());
    const epiS32 h = static_cast<epiS32>(GetHeight());

    const epiU32 channels = ChannelsOf(GetPixelFormat());
    const epiS32 x = channels * c + channel;
    const epiS32 y = r;

#ifdef EPI_DEBUG
    if (r != std::clamp(r, 0, h - 1) || c != std::clamp(c, 0, w - 1))
    {
        epiLogFatal("`r={}` should be in range [{}..{}], `c={}` should be in range [{}..{}]", r, 0, h - 1, c, 0, w - 1);
    }
#endif // EPI_DEBUG

    return GetData()[x + y * GetPitch()];
}

epiU8 mmImage::At(epiS32 r, epiS32 c, epiU32 channel, mmImageEdgeHandling edge) const
{
    // TODO: implement different out of bounds handling
    const epiS32 w = static_cast<epiS32>(GetWidth());
    const epiS32 h = static_cast<epiS32>(GetHeight());

    const epiU32 channels = ChannelsOf(GetPixelFormat());

    epiU32 x = 0;
    epiU32 y = 0;
    switch (edge)
    {
    case mmImageEdgeHandling::Error:
    {
        if (r != std::clamp(r, 0, h - 1) || c != std::clamp(c, 0, w - 1))
        {
            epiLogError("`r={}` should be in range [{}..{}], `c={}` should be in range [{}..{}]", r, 0, h - 1, c, 0, w - 1);
            return 0;
        }

        x = c;
        y = r;
    } break;
    case mmImageEdgeHandling::Zero:
    {
        if (r != std::clamp(r, 0, h - 1) || c != std::clamp(c, 0, w - 1))
        {
            return 0;
        }

        x = c;
        y = r;
    } break;
    case mmImageEdgeHandling::FF:
    {
        if (r != std::clamp(r, 0, h - 1) || c != std::clamp(c, 0, w - 1))
        {
            return 0xff;
        }

        x = c;
        y = r;
    } break;
    case mmImageEdgeHandling::Extend:
    {
        x = std::clamp(c, 0, w - 1);
        y = std::clamp(r, 0, h - 1);
    } break;
    case mmImageEdgeHandling::Wrap:
    {
        if (const epiS32 cc = std::clamp(c, 0, w - 1); cc != c)
        {
            c = c < 0 ? (w - 1) + c - 1 : c - (w - 1) - 1;
        }

        if (const epiS32 rr = std::clamp(r, 0, h - 1); rr != r)
        {
            r = r < 0 ? (h - 1) + r - 1 : r - (h - 1) - 1;
        }

        x = c;
        y = r;
    } break;
    case mmImageEdgeHandling::Mirror:
    {
        if (const epiS32 cc = std::clamp(c, 0, w - 1); cc != c)
        {
            c = c < 0 ? cc - c - 1 : (w - 1) - (cc - (w - 1)) + 1;
        }

        if (const epiS32 rr = std::clamp(r, 0, h - 1); rr != r)
        {
            r = r < 0 ? rr - r - 1 : (h - 1) - (rr - (h - 1)) + 1;
        }

        x = c;
        y = r;
    } break;
    }

    return GetData()[channels * x + channel + y * GetPitch()];
}

Color mmImage::At(epiS32 r, epiS32 c, mmImageEdgeHandling edge) const
{
    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE:
    {
        const epiU8 x = At(r, c, 0, edge);
        return Color(x, x, x);
    } break;
    case mmImagePixelFormat::R8G8B8:
    {
        return Color(At(r, c, 0, edge), At(r, c, 1, edge), At(r, c, 2, edge));
    } break;
    case mmImagePixelFormat::R8G8B8A8:
    {
        return Color(At(r, c, 0, edge), At(r, c, 1, edge), At(r, c, 2, edge), At(r, c, 3, edge));
    } break;
    break;
    }
}

mmImage mmImage::ToGrayScaleR() const
{
    return ToGrayScale_Internal(&Color::GetRu);
}

mmImage mmImage::ToGrayScaleG() const
{
    return ToGrayScale_Internal(&Color::GetGu);
}

mmImage mmImage::ToGrayScaleB() const
{
    return ToGrayScale_Internal(&Color::GetBu);
}

mmImage mmImage::ToGrayScaleA() const
{
    return ToGrayScale_Internal(&Color::GetAu);
}

mmImage mmImage::ToGrayScaleMin() const
{
    return ToGrayScale_Internal(&Color::GetMinu);
}

mmImage mmImage::ToGrayScaleMax() const
{
    return ToGrayScale_Internal(&Color::GetMaxu);
}

mmImage mmImage::ToGrayScaleHue() const
{
    return ToGrayScale_Internal(&Color::GetHueu);
}

mmImage mmImage::ToGrayScaleLuma() const
{
    return ToGrayScale_Internal(&Color::GetLumau);
}

mmImage mmImage::ToGrayScaleLuma601() const
{
    return ToGrayScale_Internal(&Color::GetLuma601u);
}

mmImage mmImage::ToGrayScaleLuma240() const
{
    return ToGrayScale_Internal(&Color::GetLuma240u);
}

mmImage mmImage::ToGrayScaleLuma709() const
{
    return ToGrayScale_Internal(&Color::GetLuma709u);
}

mmImage mmImage::ToGrayScaleLuma2020() const
{
    return ToGrayScale_Internal(&Color::GetLuma2020u);
}

mmImage mmImage::ToGrayScaleBrightness() const
{
    return ToGrayScale_Internal(&Color::GetBrightnessu);
}

mmImage mmImage::ToGrayScaleLightness() const
{
    return ToGrayScale_Internal(&Color::GetLightnessu);
}

mmImage mmImage::ToGrayScaleIntensity() const
{
    return ToGrayScale_Internal(&Color::GetIntensityu);
}

mmImage mmImage::ToGrayScaleChroma() const
{
    return ToGrayScale_Internal(&Color::GetChromau);
}

mmImage mmImage::ToGrayScaleSaturationB() const
{
    return ToGrayScale_Internal(&Color::GetSaturationBu);
}

mmImage mmImage::ToGrayScaleSaturationL() const
{
    return ToGrayScale_Internal(&Color::GetSaturationLu);
}

mmImage mmImage::ToGrayScaleSaturationI() const
{
    return ToGrayScale_Internal(&Color::GetSaturationIu);
}

mmImage mmImage::ToGrayScale_Internal(epiU8(Color::*get)() const) const
{
    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE:
    {
        return ConvertTo(*this, mmImagePixelFormat::GRAYSCALE, get);
    } break;
    case mmImagePixelFormat::R8G8B8:
    {
        return ConvertTo(*this, mmImagePixelFormat::GRAYSCALE, get, epiVec4s{0, 1, 2, 3});
    } break;
    case mmImagePixelFormat::R8G8B8A8:
    {
         // TODO: consider alpha channel
        return ConvertTo(*this, mmImagePixelFormat::GRAYSCALE, get, epiVec4s{0, 1, 2, 3});
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
    case mmImagePixelFormat::GRAYSCALE:
    {
        return ConvertTo(*this,
                         mmImagePixelFormat::R8G8B8,
                         &Color::GetLumau,
                         epiVec4s{0, 0, 0, 0},
                         epiVec4s{0, 1, 2, 3});
    } break;
    case mmImagePixelFormat::R8G8B8:
    {
        return ConvertTo(*this,
                         mmImagePixelFormat::R8G8B8,
                         &Color::GetRu,
                         &Color::GetGu,
                         &Color::GetBu,
                         epiVec4s{0, 1, 2, 3},
                         epiVec4s{0, 1, 2, 3});
    } break;
    case mmImagePixelFormat::R8G8B8A8:
    {
        ColorGetCallback get[]{&Color::GetRu, &Color::GetGu, &Color::GetBu, &Color::GetAu};
        return ConvertTo(*this,
                         mmImagePixelFormat::R8G8B8,
                         get,
                         epiVec4s{0, 1, 2, 3},
                         epiVec4s{0, 1, 2, 3});
    } break;
    }

    // TODO: retrieve string representation
    epiLogError("Unhandled pixel fmt=`{}` while converting image", GetPixelFormat());
    return mmImage{};
}

mmImage mmImage::ToR8G8B8A8() const
{
    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE:
    {
        return ConvertTo(*this,
                         mmImagePixelFormat::R8G8B8A8,
                         &Color::GetLumau,
                         epiVec4s{0, 0, 0, 0},
                         epiVec4s{0, 1, 2, 3});
    } break;
    case mmImagePixelFormat::R8G8B8:
    {
        ColorGetCallback get[]{&Color::GetRu, &Color::GetGu, &Color::GetBu};
        return ConvertTo(*this,
                         mmImagePixelFormat::R8G8B8A8,
                         get,
                         epiVec4s{0, 1, 2, 3},
                         epiVec4s{0, 1, 2, 3});
    } break;
    case mmImagePixelFormat::R8G8B8A8:
    {
        ColorGetCallback get[]{&Color::GetRu, &Color::GetGu, &Color::GetBu, &Color::GetAu};
        return ConvertTo(*this,
                         mmImagePixelFormat::R8G8B8A8,
                         get,
                         epiVec4s{0, 1, 2, 3},
                         epiVec4s{0, 1, 2, 3});
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

epiSize_t mmImage::GetPitch_Callback() const
{
    return ChannelsOf(GetPixelFormat()) * GetWidth();
}

EPI_NAMESPACE_END()
