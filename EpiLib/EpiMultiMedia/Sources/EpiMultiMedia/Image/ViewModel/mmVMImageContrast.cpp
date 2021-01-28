EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageContrast.h"
#include "EpiMultimedia/Image/ViewModel/mmVMImageContrast.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

#define UpdateContrast(Channel) \
    UpdateImage<epiS8, epiS8, epiS8, epiS8>(m_PeriodicalTask##Channel, \
                                            static_cast<void(mmVMImageBase::*)(const mmImage&)>(&mmVMImageRGB::SetImage##Channel), \
                                            &mmImage::ToGrayScale##Channel, \
                                            "Contrast" epiStringify(Channel), \
                                            &mmImage::Contrast, \
                                            value, \
                                            value, \
                                            value, \
                                            0); \
    PropertyChangedTrigger(PID_Contrast##Channel, m_Contrast##Channel, value); \
    epiPropertyChangedCheckAndTrigger(ContrastStretch##Channel, epiVec2u8{});

#define UpdateContrastStretch(Channel) \
    UpdateImage<epiU8, epiU8, epiU8, epiU8, epiU8, epiU8, epiU8, epiU8>(m_PeriodicalTask##Channel, \
                                                                        static_cast<void(mmVMImageBase::*)(const mmImage&)>(&mmVMImageRGB::SetImage##Channel), \
                                                                        &mmImage::ToGrayScale##Channel, \
                                                                        "ContrastStretch" epiStringify(Channel), \
                                                                        &mmImage::ContrastStretch, \
                                                                        value.x, \
                                                                        value.y, \
                                                                        value.x, \
                                                                        value.y, \
                                                                        value.x, \
                                                                        value.y, \
                                                                        0, \
                                                                        0); \
    PropertyChangedTrigger(PID_ContrastStretch##Channel, m_ContrastStretch##Channel, value); \
    epiPropertyChangedCheckAndTrigger(Contrast##Channel, epiS8{});

mmVMImageContrast::mmVMImageContrast()
{
    SetIsContrastSynchronized(true);
    SetIsContrastStretchSynchronized(true);
}

void mmVMImageContrast::SetContrastR_Callback(epiS8 value)
{
    if (!epiEqual(GetContrastR(), value))
    {
        if (mmImage* image = GetImageSrc())
        {
            UpdateContrast(R);

            if (GetIsContrastSynchronized())
            {
                UpdateContrast(G);
                UpdateContrast(B);
            }
        }
    }
}

void mmVMImageContrast::SetContrastG_Callback(epiS8 value)
{
    if (!epiEqual(GetContrastG(), value))
    {
        if (mmImage* image = GetImageSrc())
        {
            UpdateContrast(G);

            if (GetIsContrastSynchronized())
            {
                UpdateContrast(R);
                UpdateContrast(B);
            }
        }
    }
}

void mmVMImageContrast::SetContrastB_Callback(epiS8 value)
{
    if (!epiEqual(GetContrastB(), value))
    {
        if (mmImage* image = GetImageSrc())
        {
            UpdateContrast(B);

            if (GetIsContrastSynchronized())
            {
                UpdateContrast(R);
                UpdateContrast(G);
            }
        }
    }
}

void mmVMImageContrast::SetIsContrastSynchronized_Callback(epiBool value)
{
    epiPropertyChangedCheckAndTrigger(IsContrastSynchronized, value);
}

void mmVMImageContrast::SetContrastStretchR_Callback(const epiVec2u8& value)
{
    if (!epiEqual(GetContrastStretchR(), value))
    {
        if (mmImage* image = GetImageSrc())
        {
            UpdateContrastStretch(R);

            if (GetIsContrastStretchSynchronized())
            {
                UpdateContrastStretch(G);
                UpdateContrastStretch(B);
            }
        }
    }
}

void mmVMImageContrast::SetContrastStretchG_Callback(const epiVec2u8& value)
{
    if (!epiEqual(GetContrastStretchG(), value))
    {
        if (mmImage* image = GetImageSrc())
        {
            UpdateContrastStretch(G);

            if (GetIsContrastStretchSynchronized())
            {
                UpdateContrastStretch(R);
                UpdateContrastStretch(B);
            }
        }
    }
}

void mmVMImageContrast::SetContrastStretchB_Callback(const epiVec2u8& value)
{
    if (!epiEqual(GetContrastStretchB(), value))
    {
        if (mmImage* image = GetImageSrc())
        {
            UpdateContrastStretch(B);

            if (GetIsContrastStretchSynchronized())
            {
                UpdateContrastStretch(R);
                UpdateContrastStretch(G);
            }
        }
    }
}

void mmVMImageContrast::SetIsContrastStretchSynchronized_Callback(epiBool value)
{
    epiPropertyChangedCheckAndTrigger(IsContrastStretchSynchronized, value);
}

#undef UpdateContrast
#undef UpdateContrastStretch

EPI_NAMESPACE_END()
