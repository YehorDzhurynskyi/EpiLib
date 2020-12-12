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

void mmVMImageThreshold::SetImageSrc_Internal(mmImage* imageSrc)
{
    if (mmImage* image = GetImageSrc())
    {
        SetImageR(image->ToGrayScaleR());
        SetImageG(image->ToGrayScaleG());
        SetImageB(image->ToGrayScaleB());
    }
}

mmImage mmVMImageThreshold::GetImageTgt_Internal() const
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
    epiAssert(r.GetBPP() == g.GetBPP() && g.GetBPP() == b.GetBPP());
    epiAssert(r.GetBPC() == g.GetBPC() && g.GetBPC() == b.GetBPC());

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

#undef UpdateThreshold

EPI_NAMESPACE_END()
