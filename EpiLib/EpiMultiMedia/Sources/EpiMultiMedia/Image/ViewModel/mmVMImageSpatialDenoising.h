#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageSpatialDenoising.hxx"
EPI_GENREGION_END(include)

#include "EpiMultimedia/Image/ViewModel/mmVMImageBase.h"

#include "EpiCore/ObjectModel/epiIPropertyChangedHandler.h"

EPI_NAMESPACE_BEGIN()

class mmVMImageSpatialDenoising : public mmVMImageBase, public epiIPropertyChangedHandler
{
EPI_GENREGION_BEGIN(mmVMImageSpatialDenoising)

EPI_GENHIDDEN_mmVMImageSpatialDenoising()

public:
    constexpr static epiMetaTypeID TypeID{0x910f17a3};

    enum mmVMImageSpatialDenoising_PIDs
    {
        PID_Image = 0x4fc2b5b,
        PID_MeanKernelSize = 0xb26ec37d,
        PID_NoiseVariance = 0xec51a534,
        PID_COUNT = 3
    };

protected:
    void SetMeanKernelSize_Callback(epiU8 value);
    void SetNoiseVariance_Callback(epiU8 value);

protected:
    mmImage m_Image{};
    epiU8 m_MeanKernelSize{0};
    epiU8 m_NoiseVariance{0};

EPI_GENREGION_END(mmVMImageSpatialDenoising)

public:
    mmVMImageSpatialDenoising();

protected:
    void SetImageSrc_Internal(mmImage* imageSrc) override;
    mmImage GetImageTgt_Internal() const override;
};

EPI_NAMESPACE_END()
