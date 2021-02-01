EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageContrast.h"
#include "EpiMultimedia/Image/ViewModel/mmVMImageContrast.cxx"
EPI_GENREGION_END(include)
namespace
{

EPI_NAMESPACE_USING()

mmImage UpdateImageCallbackContrast(const mmImage& image, mmImage(mmImage::* convert)() const, epiS8 contrast)
{
    mmImage result = (image.*convert)();
    result.Contrast(contrast, contrast, contrast, 0);

    return result;
}

mmImage UpdateImageCallbackContrastStretch(const mmImage& image,
                                           mmImage(mmImage::* convert)() const,
                                           epiU8 contrastStretchLower,
                                           epiU8 contrastStretchUpper)
{
    mmImage result = (image.*convert)();
    result.ContrastStretch(contrastStretchLower,
                           contrastStretchUpper,
                           contrastStretchLower,
                           contrastStretchUpper,
                           contrastStretchLower,
                           contrastStretchUpper,
                           0,
                           0);

    return result;
}

}

EPI_NAMESPACE_BEGIN()

#define UpdateContrast(Channel) \
    UpdateImage<decltype(UpdateImageCallbackContrast), const mmImage&, mmImage(mmImage::*)() const, epiS8> \
                                                        (m_PeriodicalTask##Channel, \
                                                        static_cast<void(mmVMImageBase::*)(const mmImage&)>(&mmVMImageRGB::SetImage##Channel), \
                                                        &UpdateImageCallbackContrast, \
                                                        *GetImageSrc(), \
                                                        &mmImage::ToGrayScale##Channel, \
                                                        value); \
    PropertyChangedTrigger(PID_Contrast##Channel, m_Contrast##Channel, value); \
    epiPropertyChangedCheckAndTrigger(ContrastStretch##Channel, epiVec2u8{});

#define UpdateContrastStretch(Channel) \
    UpdateImage<decltype(UpdateImageCallbackContrastStretch), const mmImage&, mmImage(mmImage::*)() const, epiU8, epiU8> \
                                                        (m_PeriodicalTask##Channel, \
                                                        static_cast<void(mmVMImageBase::*)(const mmImage&)>(&mmVMImageRGB::SetImage##Channel), \
                                                        &UpdateImageCallbackContrastStretch, \
                                                        *GetImageSrc(), \
                                                        &mmImage::ToGrayScale##Channel, \
                                                        value.x, \
                                                        value.y); \
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
