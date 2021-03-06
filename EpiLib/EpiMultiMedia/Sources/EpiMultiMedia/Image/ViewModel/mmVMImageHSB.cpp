EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageHSB.h"
#include "EpiMultimedia/Image/ViewModel/mmVMImageHSB.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

void mmVMImageHSB::SetHue_Callback(epiS32 value)
{
    if (!epiEqual(GetHue(), value))
    {
        if (mmImage* image = GetImageSrc())
        {
            mmImage imageH = image->ToGrayScaleHue();
            imageH.ShiftRotate(value, value, value);

            SetImageHue(imageH);
        }
    }

    epiPropertyChangedCheckAndTrigger(Hue, value);
}

void mmVMImageHSB::SetSaturation_Callback(epiS32 value)
{
    if (!epiEqual(GetSaturation(), value))
    {
        if (mmImage* image = GetImageSrc())
        {
            mmImage imageS = image->ToGrayScaleSaturationB();
            imageS.Shift(value, value, value);

            SetImageSaturation(imageS);
        }
    }

    epiPropertyChangedCheckAndTrigger(Saturation, value);
}

void mmVMImageHSB::SetBrightness_Callback(epiS32 value)
{
    if (!epiEqual(GetBrightness(), value))
    {
        if (mmImage* image = GetImageSrc())
        {
            mmImage imageB = image->ToGrayScaleBrightness();
            imageB.Shift(value, value, value);

            SetImageBrightness(imageB);
        }
    }

    epiPropertyChangedCheckAndTrigger(Brightness, value);
}

void mmVMImageHSB::SetImageSrc_Internal(mmImage* imageSrc)
{
    if (imageSrc != nullptr)
    {
        SetImageHue(imageSrc->ToGrayScaleHue());
        SetImageSaturation(imageSrc->ToGrayScaleSaturationB());
        SetImageBrightness(imageSrc->ToGrayScaleBrightness());
    }
}

mmImage mmVMImageHSB::GetImageTgt_Internal() const
{
    mmImage to;

    const mmImage& h = GetImageHue();
    const mmImage& s = GetImageSaturation();
    const mmImage& b = GetImageBrightness();

    epiAssert(h.GetPixelFormat() == mmImagePixelFormat::GRAYSCALE);
    epiAssert(s.GetPixelFormat() == mmImagePixelFormat::GRAYSCALE);
    epiAssert(b.GetPixelFormat() == mmImagePixelFormat::GRAYSCALE);

    epiAssert(h.GetWidth() == s.GetWidth() && s.GetWidth() == b.GetWidth());
    epiAssert(h.GetHeight() == s.GetHeight() && s.GetHeight() == b.GetHeight());
    epiAssert(h.GetBPP() == s.GetBPP() && s.GetBPP() == b.GetBPP());
    epiAssert(h.GetBPC() == s.GetBPC() && s.GetBPC() == b.GetBPC());

    to.SetWidth(h.GetWidth());
    to.SetHeight(h.GetHeight());
    to.SetPixelFormat(mmImagePixelFormat::R8G8B8);
    epiArray<epiU8>& toData = to.GetData();
    toData.Resize(h.GetData().Size() * 3);

    for (epiU32 i = 0; i < toData.Size() / 3; ++i)
    {
        const Color color = Color::FromHSB(epiVec3u8{h.GetData()[i], s.GetData()[i], b.GetData()[i]});

        toData[i * 3 + 0] = color.GetRu();
        toData[i * 3 + 1] = color.GetGu();
        toData[i * 3 + 2] = color.GetBu();
    }

    return to;
}

EPI_NAMESPACE_END()
