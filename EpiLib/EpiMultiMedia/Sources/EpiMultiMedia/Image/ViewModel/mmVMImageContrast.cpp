EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageContrast.h"
#include "EpiMultimedia/Image/ViewModel/mmVMImageContrast.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

void mmVMImageContrast::SetContrastR_Callback(epiS8 value)
{
    if (m_ContrastR != value)
    {
        if (mmImage* image = GetImageSrc())
        {
            mmImage imageTgt = image->Duplicate();
            imageTgt.Contrast(value, 0, 0);

            SetImageTgt(imageTgt);
        }
    }

    epiPropertyChangedCheckAndTrigger(ContrastR, value);
    epiPropertyChangedCheckAndTrigger(ContrastStretchR, epiVec2s8{});
    epiPropertyChangedCheckAndTrigger(ContrastStretchG, epiVec2s8{});
    epiPropertyChangedCheckAndTrigger(ContrastStretchB, epiVec2s8{});
}

void mmVMImageContrast::SetContrastG_Callback(epiS8 value)
{
    if (m_ContrastG != value)
    {
        if (mmImage* image = GetImageSrc())
        {
            mmImage imageTgt = image->Duplicate();
            imageTgt.Contrast(0, value, 0);

            SetImageTgt(imageTgt);
        }
    }

    epiPropertyChangedCheckAndTrigger(ContrastG, value);
    epiPropertyChangedCheckAndTrigger(ContrastStretchR, epiVec2s8{});
    epiPropertyChangedCheckAndTrigger(ContrastStretchG, epiVec2s8{});
    epiPropertyChangedCheckAndTrigger(ContrastStretchB, epiVec2s8{});
}

void mmVMImageContrast::SetContrastB_Callback(epiS8 value)
{
    if (m_ContrastB != value)
    {
        if (mmImage* image = GetImageSrc())
        {
            mmImage imageTgt = image->Duplicate();
            imageTgt.Contrast(0, 0, value);

            SetImageTgt(imageTgt);
        }
    }

    epiPropertyChangedCheckAndTrigger(ContrastB, value);
    epiPropertyChangedCheckAndTrigger(ContrastStretchR, epiVec2s8{});
    epiPropertyChangedCheckAndTrigger(ContrastStretchG, epiVec2s8{});
    epiPropertyChangedCheckAndTrigger(ContrastStretchB, epiVec2s8{});
}

void mmVMImageContrast::SetContrastStretchR_Callback(const epiVec2s8& value)
{
    if (m_ContrastStretchR != value)
    {
        if (mmImage* image = GetImageSrc())
        {
            mmImage imageTgt = image->Duplicate();
            imageTgt.ContrastStretch(value.x, value.y, 0, 0, 0, 0);

            SetImageTgt(imageTgt);
        }
    }

    epiPropertyChangedCheckAndTrigger(ContrastStretchR, value);
    epiPropertyChangedCheckAndTrigger(ContrastR, epiS8{});
    epiPropertyChangedCheckAndTrigger(ContrastG, epiS8{});
    epiPropertyChangedCheckAndTrigger(ContrastB, epiS8{});
}

void mmVMImageContrast::SetContrastStretchG_Callback(const epiVec2s8& value)
{
    if (m_ContrastStretchG != value)
    {
        if (mmImage* image = GetImageSrc())
        {
            mmImage imageTgt = image->Duplicate();
            imageTgt.ContrastStretch(0, 0, value.x, value.y, 0, 0);

            SetImageTgt(imageTgt);
        }
    }

    epiPropertyChangedCheckAndTrigger(ContrastStretchG, value);
    epiPropertyChangedCheckAndTrigger(ContrastR, epiS8{});
    epiPropertyChangedCheckAndTrigger(ContrastG, epiS8{});
    epiPropertyChangedCheckAndTrigger(ContrastB, epiS8{});
}

void mmVMImageContrast::SetContrastStretchB_Callback(const epiVec2s8& value)
{
    if (m_ContrastStretchB != value)
    {
        if (mmImage* image = GetImageSrc())
        {
            mmImage imageTgt = image->Duplicate();
            imageTgt.ContrastStretch(0, 0, 0, 0, value.x, value.y);

            SetImageTgt(imageTgt);
        }
    }

    epiPropertyChangedCheckAndTrigger(ContrastStretchB, value);
    epiPropertyChangedCheckAndTrigger(ContrastR, epiS8{});
    epiPropertyChangedCheckAndTrigger(ContrastG, epiS8{});
    epiPropertyChangedCheckAndTrigger(ContrastB, epiS8{});
}

EPI_NAMESPACE_END()
