EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageHomomorphic.h"
#include "EpiMultimedia/Image/ViewModel/mmVMImageHomomorphic.cxx"
EPI_GENREGION_END(include)

namespace
{

EPI_NAMESPACE_USING()

mmImage HomomorphicTransform(const mmImage& image, epiFloat highPassScaleFactor, epiFloat lowPassScaleFactor)
{
    dSeries2Df highPassFilter = dSeries2Df::Full(3 * 3, 3, 0.0f);
    highPassFilter.At(0, 1) = 1.0f;
    highPassFilter.At(1, 0) = 1.0f;
    highPassFilter.At(1, 1) = -4.0f;
    highPassFilter.At(1, 2) = 1.0f;
    highPassFilter.At(2, 1) = 1.0f;

    auto highIntensity = [&image, &highPassFilter](mmImageGetColorValueCallback callback, epiFloat highPassScaleFactor) -> dSeries2Df
    {
        return image.ToSeries2Df(callback).Log(M_E).Convolve(highPassFilter).Mult(highPassScaleFactor);
    };

    const dSeries2Df lowPassFilter = dSeries2Df::Full(3 * 3, 3, 1.0f / (3.0f * 3.0f));

    auto lowIntensity = [&image, &lowPassFilter](mmImageGetColorValueCallback callback, epiFloat lowPassScaleFactor) -> dSeries2Df
    {
        return image.ToSeries2Df(callback).Log(M_E).Convolve(lowPassFilter).Mult(lowPassScaleFactor);
    };

    switch (image.GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE:
    {
        const dSeries2Df luma = highIntensity(&Color::GetLumau, highPassScaleFactor).Add(lowIntensity(&Color::GetLumau, lowPassScaleFactor)).Exp(M_E);

        return mmImage::FromSeries2Df_ToGRAYSCALE(luma);
    } break;
    case mmImagePixelFormat::R8G8B8:
    case mmImagePixelFormat::R8G8B8A8:
    {
        const dSeries2Df r = highIntensity(&Color::GetRu, highPassScaleFactor).Add(lowIntensity(&Color::GetRu, lowPassScaleFactor)).Exp(M_E);
        const dSeries2Df g = highIntensity(&Color::GetGu, highPassScaleFactor).Add(lowIntensity(&Color::GetGu, lowPassScaleFactor)).Exp(M_E);
        const dSeries2Df b = highIntensity(&Color::GetBu, highPassScaleFactor).Add(lowIntensity(&Color::GetBu, lowPassScaleFactor)).Exp(M_E);

        return mmImage::FromSeries2Df_ToR8G8B8(r, g, b);
    } break;
    }
}

}

EPI_NAMESPACE_BEGIN()

void mmVMImageHomomorphic::SetHighPassScaleFactor_Callback(epiFloat value)
{
    if (!epiEqual(GetHighPassScaleFactor(), value))
    {
        if (mmImage* imageSrc = GetImageSrc())
        {
            SetImage(HomomorphicTransform(*imageSrc, value, GetLowPassScaleFactor()));

            epiPropertyChangedCheckAndTrigger(HighPassScaleFactor, value);
        }
    }
}

void mmVMImageHomomorphic::SetLowPassScaleFactor_Callback(epiFloat value)
{
    if (!epiEqual(GetLowPassScaleFactor(), value))
    {
        if (mmImage* imageSrc = GetImageSrc())
        {
            SetImage(HomomorphicTransform(*imageSrc, GetHighPassScaleFactor(), value));

            epiPropertyChangedCheckAndTrigger(LowPassScaleFactor, value);
        }
    }
}

void mmVMImageHomomorphic::SetImageSrc_Internal(mmImage* imageSrc)
{
    if (mmImage* image = GetImageSrc())
    {
        SetImage(image->Duplicate());
    }
}

mmImage mmVMImageHomomorphic::GetImageTgt_Internal() const
{
    return GetImage();
}

EPI_NAMESPACE_END()
