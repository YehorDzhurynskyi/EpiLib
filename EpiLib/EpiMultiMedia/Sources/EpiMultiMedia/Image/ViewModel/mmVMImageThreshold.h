#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageThreshold.hxx"
EPI_GENREGION_END(include)

#include "EpiMultimedia/Image/ViewModel/mmVMImageRGB.h"

EPI_NAMESPACE_BEGIN()

class mmVMImageThreshold : public mmVMImageRGB
{
EPI_GENREGION_BEGIN(mmVMImageThreshold)

EPI_GENHIDDEN_mmVMImageThreshold()

public:
    constexpr static epiMetaTypeID TypeID{0x6b79f6f9};

    enum mmVMImageThreshold_PIDs
    {
        PID_ThresholdR = 0x1bd90de,
        PID_ThresholdG = 0x6c607435,
        PID_ThresholdB = 0x1c0a80ba,
        PID_IsThresholdSynchronized = 0xa330125c,
        PID_COUNT = 4
    };

protected:
    void SetThresholdR_Callback(epiU8 value);
    void SetThresholdG_Callback(epiU8 value);
    void SetThresholdB_Callback(epiU8 value);
    void SetIsThresholdSynchronized_Callback(epiBool value);

protected:
    epiU8 m_ThresholdR{0};
    epiU8 m_ThresholdG{0};
    epiU8 m_ThresholdB{0};
    epiBool m_IsThresholdSynchronized{false};

EPI_GENREGION_END(mmVMImageThreshold)
};

EPI_NAMESPACE_END()
