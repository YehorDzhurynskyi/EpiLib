#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageHomomorphic.hxx"
EPI_GENREGION_END(include)

#include "EpiMultimedia/Image/ViewModel/mmVMImageBase.h"

EPI_NAMESPACE_BEGIN()

class mmVMImageHomomorphic : public mmVMImageBase
{
EPI_GENREGION_BEGIN(mmVMImageHomomorphic)

EPI_GENHIDDEN_mmVMImageHomomorphic()

public:
    constexpr static epiMetaTypeID TypeID{0xb535dd11};

    enum mmVMImageHomomorphic_PIDs
    {
        PID_Image = 0x4fc2b5b,
        PID_HighPassScaleFactor = 0xc6e51743,
        PID_LowPassScaleFactor = 0x83e2f21,
        PID_COUNT = 3
    };

protected:
    void SetHighPassScaleFactor_Callback(epiFloat value);
    void SetLowPassScaleFactor_Callback(epiFloat value);

protected:
    mmImage m_Image{};
    epiFloat m_HighPassScaleFactor{0.0f};
    epiFloat m_LowPassScaleFactor{0.0f};

EPI_GENREGION_END(mmVMImageHomomorphic)

protected:
    mmImage GetImageTgt_Internal() const override;
};

EPI_NAMESPACE_END()
