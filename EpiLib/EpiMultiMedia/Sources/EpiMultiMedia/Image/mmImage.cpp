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

void mmImage::Threshold(epiU8 thr)
{
    Threshold(thr, thr, thr);
}

void mmImage::Threshold(epiU8 thrR, epiU8 thrG, epiU8 thrB)
{
    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE:
    {
        if (thrR == thrG && thrG == thrB)
        {
            *this = ConvertTo(*this,
                              mmImagePixelFormat::GRAYSCALE,
                              &Color::GetLumau,
                              epiVec3s{0, 0, 0},
                              epiVec3s{0, 0, 0},
                              &Color::Threshold,
                              thrR,
                              thrG,
                              thrB);
        }
        else
        {
            ColorGetCallback get[3]{&Color::GetRu, &Color::GetGu, &Color::GetBu};
            *this = ConvertTo(ToR8G8B8(),
                              mmImagePixelFormat::R8G8B8,
                              get,
                              epiVec3s{0, 1, 2},
                              epiVec3s{0, 1, 2},
                              &Color::Threshold,
                              thrR,
                              thrG,
                              thrB);
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
                          &Color::Threshold,
                          thrR,
                          thrG,
                          thrB);
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
                            epiVec3s{0, 0, 0},
                            epiVec3s{0, 0, 0},
                            &Color::Negative);

    } break;
    case mmImagePixelFormat::R8G8B8:
    {
        ColorGetCallback get[3]{&Color::GetRu, &Color::GetGu, &Color::GetBu};
        *this = ConvertTo(*this,
                          mmImagePixelFormat::R8G8B8,
                          get,
                          epiVec3s{0, 1, 2},
                          epiVec3s{0, 1, 2},
                          &Color::Negative);
    } break;
    }
}

void mmImage::Gamma(epiFloat gamma)
{
    Gamma(gamma, gamma, gamma);
}

void mmImage::Gamma(epiFloat gammaR, epiFloat gammaG, epiFloat gammaB)
{
    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE:
    {
        if (epiEqual(gammaR, gammaG) && epiEqual(gammaG, gammaB))
        {
            *this = ConvertTo(*this,
                              mmImagePixelFormat::GRAYSCALE,
                              &Color::GetLumau,
                              epiVec3s{0, 0, 0},
                              epiVec3s{0, 0, 0},
                              &Color::Gamma,
                              gammaR,
                              gammaG,
                              gammaB);
        }
        else
        {
            ColorGetCallback get[3]{&Color::GetRu, &Color::GetGu, &Color::GetBu};
            *this = ConvertTo(ToR8G8B8(),
                              mmImagePixelFormat::R8G8B8,
                              get,
                              epiVec3s{0, 1, 2},
                              epiVec3s{0, 1, 2},
                              &Color::Gamma,
                              gammaR,
                              gammaG,
                              gammaB);
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
                          &Color::Gamma,
                          gammaR,
                          gammaG,
                          gammaB);
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
            *this = ConvertTo(*this,
                              mmImagePixelFormat::GRAYSCALE,
                              &Color::GetLumau,
                              epiVec3s{0, 0, 0},
                              epiVec3s{0, 0, 0},
                              &Color::Contrast,
                              contrastR,
                              contrastG,
                              contrastB);
        }
        else
        {
            ColorGetCallback get[3]{&Color::GetRu, &Color::GetGu, &Color::GetBu};
            *this = ConvertTo(ToR8G8B8(),
                              mmImagePixelFormat::R8G8B8,
                              get,
                              epiVec3s{0, 1, 2},
                              epiVec3s{0, 1, 2},
                              &Color::Contrast,
                              contrastR,
                              contrastG,
                              contrastB);
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
                          &Color::Contrast,
                          contrastR,
                          contrastG,
                          contrastB);
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
    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE:
    {
        *this = ConvertTo(*this,
                          mmImagePixelFormat::GRAYSCALE,
                          &Color::GetLumau,
                          epiVec3s{0, 0, 0},
                          epiVec3s{0, 0, 0},
                          &Color::Shift,
                          shiftR,
                          shiftG,
                          shiftB);
    } break;
    case mmImagePixelFormat::R8G8B8:
    {
        ColorGetCallback get[3]{&Color::GetRu, &Color::GetGu, &Color::GetBu};
        *this = ConvertTo(*this,
                          mmImagePixelFormat::R8G8B8,
                          get,
                          epiVec3s{0, 1, 2},
                          epiVec3s{0, 1, 2},
                          &Color::Shift,
                          shiftR,
                          shiftG,
                          shiftB);
    } break;
    }
}

void mmImage::ShiftRotate(epiS32 shift)
{
    ShiftRotate(shift, shift, shift);
}

void mmImage::ShiftRotate(epiS32 shiftR, epiS32 shiftG, epiS32 shiftB)
{
    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE:
    {
        *this = ConvertTo(*this,
                          mmImagePixelFormat::GRAYSCALE,
                          &Color::GetLumau,
                          epiVec3s{0, 0, 0},
                          epiVec3s{0, 0, 0},
                          &Color::ShiftRotate,
                          shiftR,
                          shiftG,
                          shiftB);
    } break;
    case mmImagePixelFormat::R8G8B8:
    {
        ColorGetCallback get[3]{&Color::GetRu, &Color::GetGu, &Color::GetBu};
        *this = ConvertTo(*this,
                          mmImagePixelFormat::R8G8B8,
                          get,
                          epiVec3s{0, 1, 2},
                          epiVec3s{0, 1, 2},
                          &Color::ShiftRotate,
                          shiftR,
                          shiftG,
                          shiftB);
    } break;
    }
}

void mmImage::ConvolveWith(const cv::Mat& kernel)
{
    ConvolveWith(kernel, kernel, kernel);
}

void mmImage::ConvolveWith(const cv::Mat& kernelR, const cv::Mat& kernelG, const cv::Mat& kernelB)
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
                            const epiU8 pix = At(r + kR - kernelR.rows / 2, c + kC - kernelR.cols / 2, 0);
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
                        const epiU8 pix = At(r + kR - kernelR.rows / 2, c + kC - kernelR.cols / 2, 0);
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
                        const epiU8 pix = At(r + kR - kernelG.rows / 2, c + kC - kernelG.cols / 2, 1);
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
                        const epiU8 pix = At(r + kR - kernelB.rows / 2, c + kC - kernelB.cols / 2, 2);
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

mmImage mmImage::Crop(const epiRect2u& crop) const
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
                image.At(rr, c, ch) = At(cRR, cC, ch);
            }
        }
    }

    return image;
}

epiU8& mmImage::At(epiU32 r, epiU32 c, epiU32 channel)
{
    // TODO: implement different out of bounds handling
    const epiU32 w = static_cast<epiU32>(GetWidth());
    const epiU32 h = static_cast<epiU32>(GetHeight());

    const epiU32 channels = ChannelsOf(GetPixelFormat());
    const epiU32 x = channels * std::clamp(c, 0u, w - 1) + channel;
    const epiU32 y = std::clamp(r, 0u, h - 1);

    return GetData()[x + y * GetPitch()];
}

epiU8 mmImage::At(epiU32 r, epiU32 c, epiU32 channel) const
{
    // TODO: implement different out of bounds handling
    const epiU32 w = static_cast<epiU32>(GetWidth());
    const epiU32 h = static_cast<epiU32>(GetHeight());

    const epiU32 channels = ChannelsOf(GetPixelFormat());
    const epiU32 x = channels * std::clamp(c, 0u, w - 1) + channel;
    const epiU32 y = std::clamp(r, 0u, h - 1);

    return GetData()[x + y * GetPitch()];
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
        return ConvertTo(*this, mmImagePixelFormat::GRAYSCALE, get, epiVec3s{0, 1, 2});
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

epiSize_t mmImage::GetPitch_Callback() const
{
    return ChannelsOf(GetPixelFormat()) * GetWidth();
}

EPI_NAMESPACE_END()
