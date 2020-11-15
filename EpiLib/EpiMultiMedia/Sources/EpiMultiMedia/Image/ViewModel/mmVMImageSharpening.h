#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageSharpening.hxx"
EPI_GENREGION_END(include)

#include "EpiMultimedia/Image/ViewModel/mmVMImageBase.h"

#include "EpiCore/ObjectModel/epiIPropertyChangedHandler.h"

EPI_NAMESPACE_BEGIN()

class mmVMImageSharpening : public mmVMImageBase, public epiIPropertyChangedHandler
{
EPI_GENREGION_BEGIN(mmVMImageSharpening)

EPI_GENHIDDEN_mmVMImageSharpening()

public:
    constexpr static epiMetaTypeID TypeID{0x4dd35cd2};

    enum mmVMImageSharpening_PIDs
    {
        PID_Image = 0x4fc2b5b,
        PID_ScaleFactor = 0xfe8fbe7e,
        PID_COUNT = 2
    };

protected:
    void SetScaleFactor_Callback(epiFloat value);

protected:
    mmImage m_Image{};
    epiFloat m_ScaleFactor{0.0f};

EPI_GENREGION_END(mmVMImageSharpening)

protected:
    void SetImageSrc_Internal(mmImage* imageSrc) override;
    mmImage GetImageTgt_Internal() const override;
};

EPI_NAMESPACE_END()
