EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageBase.h"
#include "EpiMultimedia/Image/ViewModel/mmVMImageBase.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

void mmVMImageBase::SetImageSrc_Callback(mmImage* value)
{
    m_ImageSrc = value;

    SetImageSrc_Internal(value);
}

mmImage mmVMImageBase::GetImageTgt_Callback() const
{
    return GetImageTgt_Internal();
}

EPI_NAMESPACE_END()
