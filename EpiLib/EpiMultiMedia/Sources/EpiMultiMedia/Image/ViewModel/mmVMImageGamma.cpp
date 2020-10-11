EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageGamma.h"
#include "EpiMultimedia/Image/ViewModel/mmVMImageGamma.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

mmVMImageGamma::mmVMImageGamma()
{
    SetIsGammaSynchronized(true);
    SetGammaR(1.0f);
    SetGammaG(1.0f);
    SetGammaB(1.0f);
}

void mmVMImageGamma::SetGammaR_Callback(epiFloat value)
{
    if (!epiEqual(GetGammaR(), value))
    {
        if (mmImage* image = GetImageSrc())
        {
            mmImage imageR = image->ToGrayScaleR();
            imageR.Gamma(value);

            SetImageR(imageR);

            if (GetIsGammaSynchronized())
            {
                mmImage imageG = image->ToGrayScaleG();
                imageG.Gamma(value);

                SetImageG(imageG);

                epiPropertyChangedCheckAndTrigger(GammaG, value);

                mmImage imageB = image->ToGrayScaleB();
                imageB.Gamma(value);

                SetImageB(imageB);

                epiPropertyChangedCheckAndTrigger(GammaB, value);
            }
        }
    }

    epiPropertyChangedCheckAndTrigger(GammaR, value);
}

void mmVMImageGamma::SetGammaG_Callback(epiFloat value)
{
    if (!epiEqual(GetGammaG(), value))
    {
        if (mmImage* image = GetImageSrc())
        {
            mmImage imageG = image->ToGrayScaleG();
            imageG.Gamma(value);

            SetImageG(imageG);

            if (GetIsGammaSynchronized())
            {
                mmImage imageR = image->ToGrayScaleR();
                imageR.Gamma(value);

                SetImageR(imageR);

                epiPropertyChangedCheckAndTrigger(GammaR, value);

                mmImage imageB = image->ToGrayScaleB();
                imageB.Gamma(value);

                SetImageB(imageB);

                epiPropertyChangedCheckAndTrigger(GammaB, value);
            }
        }
    }

    epiPropertyChangedCheckAndTrigger(GammaG, value);
}

void mmVMImageGamma::SetGammaB_Callback(epiFloat value)
{
    if (!epiEqual(GetGammaB(), value))
    {
        if (mmImage* image = GetImageSrc())
        {
            mmImage imageB = image->ToGrayScaleB();
            imageB.Gamma(value);

            SetImageB(imageB);

            if (GetIsGammaSynchronized())
            {
                mmImage imageR = image->ToGrayScaleR();
                imageR.Gamma(value);

                SetImageR(imageR);

                epiPropertyChangedCheckAndTrigger(GammaR, value);

                mmImage imageG = image->ToGrayScaleG();
                imageG.Gamma(value);

                SetImageG(imageG);

                epiPropertyChangedCheckAndTrigger(GammaG, value);
            }
        }
    }

    epiPropertyChangedCheckAndTrigger(GammaB, value);
}

void mmVMImageGamma::SetIsGammaSynchronized_Callback(epiBool value)
{
    epiPropertyChangedCheckAndTrigger(IsGammaSynchronized, value);
}

void mmVMImageGamma::SetImageSrc_Internal(mmImage* imageSrc)
{
    if (mmImage* image = GetImageSrc())
    {
        SetImageR(image->ToGrayScaleR());
        SetImageG(image->ToGrayScaleG());
        SetImageB(image->ToGrayScaleB());
    }
}

mmImage mmVMImageGamma::GetImageTgt_Internal() const
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
