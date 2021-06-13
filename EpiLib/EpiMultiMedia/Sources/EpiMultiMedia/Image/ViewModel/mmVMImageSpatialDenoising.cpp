EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageSpatialDenoising.h"
#include "EpiMultimedia/Image/ViewModel/mmVMImageSpatialDenoising.cxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeries2Df.h"

namespace
{

epiFloat SpatiallyAdaptiveNoiseFilter(epiFloat x, epiFloat mean, epiFloat imageVariance, epiFloat noiseVariance)
{
    return (1.0f - (noiseVariance / imageVariance)) * x + (noiseVariance / imageVariance) * mean;
}

}

EPI_NAMESPACE_BEGIN()

mmVMImageSpatialDenoising::mmVMImageSpatialDenoising()
{
    SetMeanKernelSize(3);
}

void mmVMImageSpatialDenoising::SetMeanKernelSize_Callback(epiU8 value)
{
    if (!epiEqual(GetMeanKernelSize(), value))
    {
        if (mmImage* imageSrc = GetImageSrc())
        {
            auto spatiallyAdaptiveNoiseFilter = [noiseVariance = GetNoiseVariance(), kernelSize = value](const dSeries2Df& series, epiFloat mean, epiS32 r, epiS32 c)
            {
                epiFloat imageVariance = 0.0f;
                for (epiS32 kR = 0; kR < kernelSize; ++kR)
                {
                    for (epiS32 kC = 0; kC < kernelSize; ++kC)
                    {
                        const epiFloat v = series.At(r - (kR - kernelSize / 2), c - (kC - kernelSize / 2), dSeriesAddressMode::Reflect);
                        imageVariance += (v - mean) * (v - mean);
                    }
                }

                return SpatiallyAdaptiveNoiseFilter(series.At(r, c), mean, imageVariance, noiseVariance);
            };

            const dSeries2Df kernel = dSeries2Df::Full(value * value, value, 1.0f / (value * value));
            SetImage(imageSrc->Convolve(kernel, dSeriesAddressMode::Reflect, spatiallyAdaptiveNoiseFilter));

            epiPropertyChangedCheckAndTrigger(MeanKernelSize, value);
        }
    }
}

void mmVMImageSpatialDenoising::SetNoiseVariance_Callback(epiU8 value)
{
    if (!epiEqual(GetNoiseVariance(), value))
    {
        if (mmImage* imageSrc = GetImageSrc())
        {
            auto spatiallyAdaptiveNoiseFilter = [noiseVariance = value, kernelSize = GetMeanKernelSize()](const dSeries2Df& series, epiFloat mean, epiS32 r, epiS32 c)
            {
                epiFloat imageVariance = 0.0f;
                for (epiS32 kR = 0; kR < kernelSize; ++kR)
                {
                    for (epiS32 kC = 0; kC < kernelSize; ++kC)
                    {
                        const epiFloat v = series.At(r - (kR - kernelSize / 2), c - (kC - kernelSize / 2), dSeriesAddressMode::Reflect);
                        imageVariance += (v - mean) * (v - mean);
                    }
                }

                return SpatiallyAdaptiveNoiseFilter(series.At(r, c), mean, imageVariance, noiseVariance);
            };

            const epiSize_t kernelSize = GetMeanKernelSize();
            const dSeries2Df kernel = dSeries2Df::Full(kernelSize * kernelSize, kernelSize, 1.0f / (kernelSize * kernelSize));
            SetImage(imageSrc->Convolve(kernel, dSeriesAddressMode::Reflect, spatiallyAdaptiveNoiseFilter));

            epiPropertyChangedCheckAndTrigger(NoiseVariance, value);
        }
    }
}

mmImage mmVMImageSpatialDenoising::GetImageTgt_Internal() const
{
    return GetImage();
}

EPI_NAMESPACE_END()
