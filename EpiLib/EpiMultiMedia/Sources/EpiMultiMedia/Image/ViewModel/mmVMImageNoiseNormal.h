#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageNoiseNormal.hxx"
EPI_GENREGION_END(include)

#include "EpiMultimedia/Image/ViewModel/mmVMImageBase.h"

#include "EpiCore/ObjectModel/epiIPropertyChangedHandler.h"

EPI_NAMESPACE_BEGIN()

class mmVMImageNoiseNormal : public mmVMImageBase, public epiIPropertyChangedHandler
{
EPI_GENREGION_BEGIN(mmVMImageNoiseNormal)

EPI_GENHIDDEN_mmVMImageNoiseNormal()

public:
    constexpr static epiMetaTypeID TypeID{0xb8b33404};

    enum mmVMImageNoiseNormal_PIDs
    {
        PID_Image = 0x4fc2b5b,
        PID_MeanR = 0x5db7bb32,
        PID_MeanG = 0x306a5fd9,
        PID_MeanB = 0x4000ab56,
        PID_IsMeanSynchronized = 0x2fffc966,
        PID_StdDevR = 0xd53a9a07,
        PID_StdDevG = 0xb8e77eec,
        PID_StdDevB = 0xc88d8a63,
        PID_IsStdDevSynchronized = 0x418b787e,
        PID_COUNT = 9
    };

protected:
    void SetMeanR_Callback(epiFloat value);
    void SetMeanG_Callback(epiFloat value);
    void SetMeanB_Callback(epiFloat value);
    void SetIsMeanSynchronized_Callback(epiBool value);
    void SetStdDevR_Callback(epiFloat value);
    void SetStdDevG_Callback(epiFloat value);
    void SetStdDevB_Callback(epiFloat value);
    void SetIsStdDevSynchronized_Callback(epiBool value);

protected:
    mmImage m_Image{};
    epiFloat m_MeanR{0.0f};
    epiFloat m_MeanG{0.0f};
    epiFloat m_MeanB{0.0f};
    epiBool m_IsMeanSynchronized{false};
    epiFloat m_StdDevR{0.0f};
    epiFloat m_StdDevG{0.0f};
    epiFloat m_StdDevB{0.0f};
    epiBool m_IsStdDevSynchronized{false};

EPI_GENREGION_END(mmVMImageNoiseNormal)
};

EPI_NAMESPACE_END()
