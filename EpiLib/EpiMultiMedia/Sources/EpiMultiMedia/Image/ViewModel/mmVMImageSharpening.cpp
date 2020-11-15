EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageSharpening.h"
#include "EpiMultimedia/Image/ViewModel/mmVMImageSharpening.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

void mmVMImageSharpening::SetScaleFactor_Callback(epiFloat value)
{
    if (!epiEqual(GetScaleFactor(), value))
    {
        if (mmImage* imageSrc = GetImageSrc())
        {
            dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
            kernel.At(0, 1) = 1.0f;
            kernel.At(1, 0) = 1.0f;
            kernel.At(1, 1) = -4.0f;
            kernel.At(1, 2) = 1.0f;
            kernel.At(2, 1) = 1.0f;

            SetImage(imageSrc->Add(imageSrc->Convolve(kernel, dSeriesEdgeHandling::Reflect).Mult(1.0f + value)));

            epiPropertyChangedCheckAndTrigger(ScaleFactor, value);
        }
    }
}

void mmVMImageSharpening::SetImageSrc_Internal(mmImage* imageSrc)
{
    if (mmImage* image = GetImageSrc())
    {
        SetImage(image->Duplicate());
    }
}

mmImage mmVMImageSharpening::GetImageTgt_Internal() const
{
    return GetImage();
}

EPI_NAMESPACE_END()
