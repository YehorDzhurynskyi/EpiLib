EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageMedian.h"
#include "EpiMultimedia/Image/ViewModel/mmVMImageMedian.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

void mmVMImageMedian::SetWindowSize_Callback(epiU8 value)
{
    if (!epiEqual(GetWindowSize(), value))
    {
        if (mmImage* imageSrc = GetImageSrc())
        {
            SetImage(imageSrc->Median(value, dSeriesEdgeHandling::Reflect));

            epiPropertyChangedCheckAndTrigger(WindowSize, value);
        }
    }
}

mmImage mmVMImageMedian::GetImageTgt_Internal() const
{
    return GetImage();
}

EPI_NAMESPACE_END()
