#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageMedian.hxx"
EPI_GENREGION_END(include)

#include "EpiMultimedia/Image/ViewModel/mmVMImageBase.h"

#include "EpiCore/ObjectModel/epiIPropertyChangedHandler.h"

EPI_NAMESPACE_BEGIN()

class mmVMImageMedian : public mmVMImageBase, public epiIPropertyChangedHandler
{
EPI_GENREGION_BEGIN(mmVMImageMedian)

EPI_GENHIDDEN_mmVMImageMedian()

public:
    constexpr static epiMetaTypeID TypeID{0x537905a8};

    enum mmVMImageMedian_PIDs
    {
        PID_Image = 0x4fc2b5b,
        PID_WindowSize = 0x36fccddf,
        PID_COUNT = 2
    };

protected:
    void SetWindowSize_Callback(epiU8 value);

protected:
    mmImage m_Image{};
    epiU8 m_WindowSize{0};

EPI_GENREGION_END(mmVMImageMedian)

protected:
    void SetImageSrc_Internal(mmImage* imageSrc) override;
    mmImage GetImageTgt_Internal() const override;
};

EPI_NAMESPACE_END()
