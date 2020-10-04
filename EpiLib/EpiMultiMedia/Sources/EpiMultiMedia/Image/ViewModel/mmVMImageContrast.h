#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageContrast.hxx"
EPI_GENREGION_END(include)

#include "EpiMultimedia/Image/ViewModel/mmVMImageBase.h"

#include "EpiCore/ObjectModel/epiIPropertyChangedHandler.h"

EPI_NAMESPACE_BEGIN()

class mmVMImageContrast : public mmVMImageBase, public epiIPropertyChangedHandler
{
EPI_GENREGION_BEGIN(mmVMImageContrast)

EPI_GENHIDDEN_mmVMImageContrast()

public:
    constexpr static epiMetaTypeID TypeID{0xc5f69e9d};

    enum mmVMImageContrast_PIDs
    {
        PID_ImageR = 0xabdaab02,
        PID_ImageG = 0xc6074fe9,
        PID_ImageB = 0xb66dbb66,
        PID_ContrastR = 0xdbee98fe,
        PID_ContrastG = 0xb6337c15,
        PID_ContrastB = 0xc659889a,
        PID_ContrastStretchR = 0x7b917e66,
        PID_ContrastStretchG = 0x164c9a8d,
        PID_ContrastStretchB = 0x66266e02,
        PID_COUNT = 9
    };

protected:
    void SetContrastR_Callback(epiS8 value);
    void SetContrastG_Callback(epiS8 value);
    void SetContrastB_Callback(epiS8 value);
    void SetContrastStretchR_Callback(const epiVec2s8& value);
    void SetContrastStretchG_Callback(const epiVec2s8& value);
    void SetContrastStretchB_Callback(const epiVec2s8& value);

protected:
    mmImage m_ImageR{};
    mmImage m_ImageG{};
    mmImage m_ImageB{};
    epiS8 m_ContrastR{0};
    epiS8 m_ContrastG{0};
    epiS8 m_ContrastB{0};
    epiVec2s8 m_ContrastStretchR{};
    epiVec2s8 m_ContrastStretchG{};
    epiVec2s8 m_ContrastStretchB{};

EPI_GENREGION_END(mmVMImageContrast)

protected:
    void SetImageSrc_Internal(mmImage* imageSrc) override;
    mmImage GetImageTgt_Internal() const override;
};

EPI_NAMESPACE_END()
