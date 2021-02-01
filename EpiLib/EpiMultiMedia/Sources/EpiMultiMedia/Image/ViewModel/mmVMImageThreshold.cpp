EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageThreshold.h"
#include "EpiMultimedia/Image/ViewModel/mmVMImageThreshold.cxx"
EPI_GENREGION_END(include)

namespace
{

EPI_NAMESPACE_USING();

mmImage UpdateImageCallbackThreshold(const mmImage& image, mmImage(mmImage::* convert)() const, epiU8 threshold)
{
    mmImage result = (image.*convert)();
    result.Threshold(threshold, threshold, threshold, 0);

    return result;
}

}

EPI_NAMESPACE_BEGIN()

#define UpdateThreshold(Channel) \
    UpdateImage<decltype(UpdateImageCallbackThreshold), const mmImage&, mmImage(mmImage::*)() const, epiU8> \
                                                        (m_PeriodicalTask##Channel, \
                                                        static_cast<void(mmVMImageBase::*)(const mmImage&)>(&mmVMImageRGB::SetImage##Channel), \
                                                        &UpdateImageCallbackThreshold, \
                                                        *GetImageSrc(), \
                                                        &mmImage::ToGrayScale##Channel, \
                                                        value); \
    PropertyChangedTrigger(PID_Threshold##Channel, m_Threshold##Channel, value);

mmVMImageThreshold::mmVMImageThreshold()
{
    SetIsThresholdSynchronized(true);
}

void mmVMImageThreshold::SetThresholdR_Callback(epiU8 value)
{
    epiProfileFunction;

    if (!epiEqual(GetThresholdR(), value))
    {
        if (mmImage* image = GetImageSrc())
        {
            UpdateThreshold(R);

            if (GetIsThresholdSynchronized())
            {
                UpdateThreshold(G);
                UpdateThreshold(B);
            }
        }
    }
}

void mmVMImageThreshold::SetThresholdG_Callback(epiU8 value)
{
    epiProfileFunction;

    if (!epiEqual(GetThresholdG(), value))
    {
        if (mmImage* image = GetImageSrc())
        {
            UpdateThreshold(G);

            if (GetIsThresholdSynchronized())
            {
                UpdateThreshold(R);
                UpdateThreshold(B);
            }
        }
    }
}

void mmVMImageThreshold::SetThresholdB_Callback(epiU8 value)
{
    epiProfileFunction;

    if (!epiEqual(GetThresholdB(), value))
    {
        if (mmImage* image = GetImageSrc())
        {
            UpdateThreshold(B);

            if (GetIsThresholdSynchronized())
            {
                UpdateThreshold(R);
                UpdateThreshold(G);
            }
        }
    }
}

void mmVMImageThreshold::SetIsThresholdSynchronized_Callback(epiBool value)
{
    epiPropertyChangedCheckAndTrigger(IsThresholdSynchronized, value);
}

#undef UpdateThreshold

EPI_NAMESPACE_END()
