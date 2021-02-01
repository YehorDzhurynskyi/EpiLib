EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageGamma.h"
#include "EpiMultimedia/Image/ViewModel/mmVMImageGamma.cxx"
EPI_GENREGION_END(include)

namespace
{

EPI_NAMESPACE_USING();

mmImage UpdateImageCallbackGamma(const mmImage& image, mmImage(mmImage::*convert)() const, epiFloat gamma)
{
    mmImage result = (image.*convert)();
    result.Gamma(gamma, gamma, gamma, 1.0f);

    return result;
}

}

EPI_NAMESPACE_BEGIN()

#define UpdateGamma(Channel) \
    UpdateImage<decltype(UpdateImageCallbackGamma), const mmImage&, mmImage(mmImage::*)() const, epiFloat> \
                                                        (m_PeriodicalTask##Channel, \
                                                        static_cast<void(mmVMImageBase::*)(const mmImage&)>(&mmVMImageRGB::SetImage##Channel), \
                                                        &UpdateImageCallbackGamma, \
                                                        *GetImageSrc(), \
                                                        &mmImage::ToGrayScale##Channel, \
                                                        value); \
    PropertyChangedTrigger(PID_Gamma##Channel, m_Gamma##Channel, value);

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
            UpdateGamma(R);

            if (GetIsGammaSynchronized())
            {
                UpdateGamma(G);
                UpdateGamma(B);
            }
        }
    }
}

void mmVMImageGamma::SetGammaG_Callback(epiFloat value)
{
    if (!epiEqual(GetGammaG(), value))
    {
        if (mmImage* image = GetImageSrc())
        {
            UpdateGamma(G);

            if (GetIsGammaSynchronized())
            {
                UpdateGamma(R);
                UpdateGamma(B);
            }
        }
    }
}

void mmVMImageGamma::SetGammaB_Callback(epiFloat value)
{
    if (!epiEqual(GetGammaB(), value))
    {
        if (mmImage* image = GetImageSrc())
        {
            UpdateGamma(B);

            if (GetIsGammaSynchronized())
            {
                UpdateGamma(R);
                UpdateGamma(G);
            }
        }
    }
}

void mmVMImageGamma::SetIsGammaSynchronized_Callback(epiBool value)
{
    epiPropertyChangedCheckAndTrigger(IsGammaSynchronized, value);
}

#undef UpdateGamma

EPI_NAMESPACE_END()
