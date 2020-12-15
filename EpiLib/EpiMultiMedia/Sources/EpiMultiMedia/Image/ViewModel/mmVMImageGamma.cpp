EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageGamma.h"
#include "EpiMultimedia/Image/ViewModel/mmVMImageGamma.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

#define UpdateGamma(Channel) \
    UpdateImage<decltype(m_Gamma##Channel), epiFloat, epiFloat, epiFloat, epiFloat>(PID_Gamma##Channel, \
                                                                                    m_Gamma##Channel, \
                                                                                    value, \
                                                                                    m_PeriodicalTask##Channel, \
                                                                                    static_cast<void(mmVMImageBase::*)(const mmImage&)>(&mmVMImageRGB::SetImage##Channel), \
                                                                                    &mmImage::ToGrayScale##Channel, \
                                                                                    &mmImage::Gamma, \
                                                                                    value, \
                                                                                    value, \
                                                                                    value, \
                                                                                    1.0f);

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
