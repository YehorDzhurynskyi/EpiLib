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
            mmImage imageR = image->ToGrayScaleR();
            imageR.Contrast(value);

            SetImageR(imageR);
        }
    }

    epiPropertyChangedCheckAndTrigger(ContrastR, value);
    epiPropertyChangedCheckAndTrigger(ContrastStretchR, epiVec2s8{});
}

void mmVMImageContrast::SetContrastG_Callback(epiS8 value)
{
    if (m_ContrastG != value)
    {
        if (mmImage* image = GetImageSrc())
        {
            mmImage imageG = image->ToGrayScaleG();
            imageG.Contrast(value);

            SetImageG(imageG);
        }
    }

    epiPropertyChangedCheckAndTrigger(ContrastG, value);
    epiPropertyChangedCheckAndTrigger(ContrastStretchG, epiVec2s8{});
}

void mmVMImageContrast::SetContrastB_Callback(epiS8 value)
{
    if (m_ContrastB != value)
    {
        if (mmImage* image = GetImageSrc())
        {
            mmImage imageB = image->ToGrayScaleB();
            imageB.Contrast(value);

            SetImageB(imageB);
        }
    }

    epiPropertyChangedCheckAndTrigger(ContrastB, value);
    epiPropertyChangedCheckAndTrigger(ContrastStretchB, epiVec2s8{});
}

void mmVMImageContrast::SetContrastStretchR_Callback(const epiVec2s8& value)
{
    if (m_ContrastStretchR != value)
    {
        if (mmImage* image = GetImageSrc())
        {
            mmImage imageR = image->ToGrayScaleR();
            imageR.ContrastStretch(value.x, value.y);

            SetImageR(imageR);
        }
    }

    epiPropertyChangedCheckAndTrigger(ContrastStretchR, value);
    epiPropertyChangedCheckAndTrigger(ContrastR, epiS8{});
}

void mmVMImageContrast::SetContrastStretchG_Callback(const epiVec2s8& value)
{
    if (m_ContrastStretchG != value)
    {
        if (mmImage* image = GetImageSrc())
        {
            mmImage imageG = image->ToGrayScaleG();
            imageG.ContrastStretch(value.x, value.y);

            SetImageG(imageG);
        }
    }

    epiPropertyChangedCheckAndTrigger(ContrastStretchG, value);
    epiPropertyChangedCheckAndTrigger(ContrastG, epiS8{});
}

void mmVMImageContrast::SetContrastStretchB_Callback(const epiVec2s8& value)
{
    if (m_ContrastStretchB != value)
    {
        if (mmImage* image = GetImageSrc())
        {
            mmImage imageB = image->ToGrayScaleB();
            imageB.ContrastStretch(value.x, value.y);

            SetImageB(imageB);
        }
    }

    epiPropertyChangedCheckAndTrigger(ContrastStretchB, value);
    epiPropertyChangedCheckAndTrigger(ContrastB, epiS8{});
}

void mmVMImageContrast::SetImageSrc_Internal(mmImage* imageSrc)
{
    if (mmImage* image = GetImageSrc())
    {
        SetImageR(image->ToGrayScaleR());
        SetImageG(image->ToGrayScaleG());
        SetImageB(image->ToGrayScaleB());
    }
}

mmImage mmVMImageContrast::GetImageTgt_Internal() const
{
    mmImage to;

    const mmImage& r = GetImageR();
    const mmImage& g = GetImageG();
    const mmImage& b = GetImageB();

    epiAssert(r.GetPixelFormat() == mmImagePixelFormat::GRAYSCALE);
    epiAssert(g.GetPixelFormat() == mmImagePixelFormat::GRAYSCALE);
    epiAssert(b.GetPixelFormat() == mmImagePixelFormat::GRAYSCALE);

    epiAssert(r.GetWidth() == g.GetWidth() && g.GetWidth() == b.GetWidth());
    epiAssert(r.GetHeight() == g.GetHeight() && g.GetHeight() == b.GetHeight());
    epiAssert(r.GetBitDepth() == g.GetBitDepth() && g.GetBitDepth() == b.GetBitDepth());

    to.SetWidth(r.GetWidth());
    to.SetHeight(r.GetHeight());
    to.SetPixelFormat(mmImagePixelFormat::R8G8B8);
    epiArray<epiU8>& toData = to.GetData();
    toData.Resize(r.GetData().Size() * 3);

    for (epiU32 i = 0; i < toData.Size() / 3; ++i)
    {
        toData[i * 3 + 0] = r.GetData()[i];
        toData[i * 3 + 1] = g.GetData()[i];
        toData[i * 3 + 2] = b.GetData()[i];
    }

    return to;
}

EPI_NAMESPACE_END()
