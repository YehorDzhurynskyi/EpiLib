#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageBase.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiMultimedia/Image/mmImage.h"

EPI_NAMESPACE_BEGIN()

class mmVMImageBase : public Object
{
EPI_GENREGION_BEGIN(mmVMImageBase)

EPI_GENHIDDEN_mmVMImageBase()

public:
    constexpr static epiMetaTypeID TypeID{0x1ae604c8};

    enum mmVMImageBase_PIDs
    {
        PID_ImageSrc = 0xfa9be066,
        PID_ImageTgt = 0x4bb29530,
        PID_COUNT = 2
    };

protected:
    void SetImageSrc_Callback(mmImage* value);
    mmImage GetImageTgt_Callback() const;

protected:
    mmImage* m_ImageSrc{nullptr};

EPI_GENREGION_END(mmVMImageBase)

protected:
    virtual void SetImageSrc_Internal(mmImage* imageSrc) = 0;
    virtual mmImage GetImageTgt_Internal() const = 0;
};

EPI_NAMESPACE_END()
