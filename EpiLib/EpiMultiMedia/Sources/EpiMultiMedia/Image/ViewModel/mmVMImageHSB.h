#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageHSB.hxx"
EPI_GENREGION_END(include)

#include "EpiMultimedia/Image/ViewModel/mmVMImageBase.h"

#include "EpiCore/ObjectModel/epiIPropertyChangedHandler.h"

EPI_NAMESPACE_BEGIN()

class mmVMImageHSB : public mmVMImageBase, public epiIPropertyChangedHandler
{
EPI_GENREGION_BEGIN(mmVMImageHSB)

EPI_GENHIDDEN_mmVMImageHSB()

public:
    constexpr static epiMetaTypeID TypeID{0x828314ca};

    enum mmVMImageHSB_PIDs
    {
        PID_ImageHue = 0x4cca9f05,
        PID_ImageSaturation = 0x78acea8f,
        PID_ImageBrightness = 0x8bf091e4,
        PID_Hue = 0xee581d0e,
        PID_Saturation = 0x6577ae58,
        PID_Brightness = 0x962bd533,
        PID_COUNT = 6
    };

protected:
    void SetHue_Callback(epiS32 value);
    void SetSaturation_Callback(epiS32 value);
    void SetBrightness_Callback(epiS32 value);

protected:
    mmImage m_ImageHue{};
    mmImage m_ImageSaturation{};
    mmImage m_ImageBrightness{};
    epiS32 m_Hue{0};
    epiS32 m_Saturation{0};
    epiS32 m_Brightness{0};

EPI_GENREGION_END(mmVMImageHSB)

protected:
    void SetImageSrc_Internal(mmImage* imageSrc) override;
    mmImage GetImageTgt_Internal() const override;
};

EPI_NAMESPACE_END()
