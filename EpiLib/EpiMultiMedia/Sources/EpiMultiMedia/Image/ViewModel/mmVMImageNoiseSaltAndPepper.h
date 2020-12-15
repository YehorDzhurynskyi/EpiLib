#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageNoiseSaltAndPepper.hxx"
EPI_GENREGION_END(include)

#include "EpiMultimedia/Image/ViewModel/mmVMImageBase.h"

EPI_NAMESPACE_BEGIN()

class mmVMImageNoiseSaltAndPepper : public mmVMImageBase
{
EPI_GENREGION_BEGIN(mmVMImageNoiseSaltAndPepper)

EPI_GENHIDDEN_mmVMImageNoiseSaltAndPepper()

public:
    constexpr static epiMetaTypeID TypeID{0x3f76a0ee};

    enum mmVMImageNoiseSaltAndPepper_PIDs
    {
        PID_Image = 0x4fc2b5b,
        PID_AmountR = 0x866705,
        PID_AmountG = 0x6d5b83ee,
        PID_AmountB = 0x1d317761,
        PID_IsAmountSynchronized = 0x1cf88d67,
        PID_SaltVsPepperR = 0xb149a7a2,
        PID_SaltVsPepperG = 0xdc944349,
        PID_SaltVsPepperB = 0xacfeb7c6,
        PID_IsSaltVsPepperSynchronized = 0xa30bd412,
        PID_COUNT = 9
    };

protected:
    void SetAmountR_Callback(epiFloat value);
    void SetAmountG_Callback(epiFloat value);
    void SetAmountB_Callback(epiFloat value);
    void SetIsAmountSynchronized_Callback(epiBool value);
    void SetSaltVsPepperR_Callback(epiFloat value);
    void SetSaltVsPepperG_Callback(epiFloat value);
    void SetSaltVsPepperB_Callback(epiFloat value);
    void SetIsSaltVsPepperSynchronized_Callback(epiBool value);

protected:
    mmImage m_Image{};
    epiFloat m_AmountR{0.0f};
    epiFloat m_AmountG{0.0f};
    epiFloat m_AmountB{0.0f};
    epiBool m_IsAmountSynchronized{false};
    epiFloat m_SaltVsPepperR{0.0f};
    epiFloat m_SaltVsPepperG{0.0f};
    epiFloat m_SaltVsPepperB{0.0f};
    epiBool m_IsSaltVsPepperSynchronized{false};

EPI_GENREGION_END(mmVMImageNoiseSaltAndPepper)
};

EPI_NAMESPACE_END()
