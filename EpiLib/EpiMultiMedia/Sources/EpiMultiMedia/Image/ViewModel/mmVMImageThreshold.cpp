EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageThreshold.h"
#include "EpiMultimedia/Image/ViewModel/mmVMImageThreshold.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

#define UpdateThreshold(Channel) \
    UpdateImage<decltype(m_Threshold##Channel), epiU8, epiU8, epiU8, epiU8>(m_PeriodicalTask##Channel, \
                                                                            static_cast<void(mmVMImageBase::*)(const mmImage&)>(&mmVMImageRGB::SetImage##Channel), \
                                                                            &mmImage::ToGrayScale##Channel, \
                                                                            &mmImage::Threshold, \
                                                                            PID_Threshold##Channel, \
                                                                            m_Threshold##Channel, \
                                                                            value, \
                                                                            value, \
                                                                            value, \
                                                                            value, \
                                                                            0);

mmVMImageThreshold::mmVMImageThreshold()
{
    SetIsThresholdSynchronized(true);
}

void mmVMImageThreshold::SetThresholdR_Callback(epiU8 value)
{
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
