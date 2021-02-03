EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageRGB.h"
#include "EpiMultimedia/Image/ViewModel/mmVMImageRGB.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

void mmVMImageRGB::SetImageR_Callback(const mmImage& value)
{
    epiProfileFunction;

    // TODO: `PropertyChangedTriggerCallbacks(PID_ImageTgt);` is being called on each SetImage<Channel> while it can be called only once

    constexpr epiBool kForceAssignment = true;
    PropertyChangedTrigger(PID_ImageR, m_ImageR, value, kForceAssignment);
    PropertyChangedTriggerCallbacks(PID_ImageTgt);
}

void mmVMImageRGB::SetImageG_Callback(const mmImage& value)
{
    epiProfileFunction;

    constexpr epiBool kForceAssignment = true;
    PropertyChangedTrigger(PID_ImageG, m_ImageG, value, kForceAssignment);
    PropertyChangedTriggerCallbacks(PID_ImageTgt);
}

void mmVMImageRGB::SetImageB_Callback(const mmImage& value)
{
    epiProfileFunction;

    constexpr epiBool kForceAssignment = true;
    PropertyChangedTrigger(PID_ImageB, m_ImageB, value, kForceAssignment);
    PropertyChangedTriggerCallbacks(PID_ImageTgt);
}

void mmVMImageRGB::SetImageSrc_Internal(mmImage* imageSrc)
{
    if (imageSrc != nullptr)
    {
        SetImageR(imageSrc->ToGrayScaleR());
        SetImageG(imageSrc->ToGrayScaleG());
        SetImageB(imageSrc->ToGrayScaleB());
    }
}

mmImage mmVMImageRGB::GetImageTgt_Internal() const
{
    epiProfileFunction;

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

EPI_NAMESPACE_END()
