#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageGamma.hxx"
EPI_GENREGION_END(include)

#include "EpiMultimedia/Image/ViewModel/mmVMImageRGB.h"

EPI_NAMESPACE_BEGIN()

class mmVMImageGamma : public mmVMImageRGB
{
EPI_GENREGION_BEGIN(mmVMImageGamma)

EPI_GENHIDDEN_mmVMImageGamma()

public:
    constexpr static epiMetaTypeID TypeID{0x6b9399c7};

    enum mmVMImageGamma_PIDs
    {
        PID_GammaR = 0x770dd819,
        PID_GammaG = 0x1ad03cf2,
        PID_GammaB = 0x6abac87d,
        PID_IsGammaSynchronized = 0x582c3374,
        PID_COUNT = 4
    };

protected:
    void SetGammaR_Callback(epiFloat value);
    void SetGammaG_Callback(epiFloat value);
    void SetGammaB_Callback(epiFloat value);
    void SetIsGammaSynchronized_Callback(epiBool value);

protected:
    epiFloat m_GammaR{0.0f};
    epiFloat m_GammaG{0.0f};
    epiFloat m_GammaB{0.0f};
    epiBool m_IsGammaSynchronized{false};

EPI_GENREGION_END(mmVMImageGamma)

public:
    mmVMImageGamma();
};

EPI_NAMESPACE_END()
