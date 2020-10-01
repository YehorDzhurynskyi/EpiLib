EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageContrast.h"
#include "EpiMultimedia/Image/ViewModel/mmVMImageContrast.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

void mmVMImageContrast::SetContrast_Callback(epiS8 value)
{
    if (mmImage* image = GetImageSrc())
    {
        mmImage imageTgt = image->Duplicate();
        imageTgt.Contrast(value);

        SetImageTgt(imageTgt);
    }

    m_Contrast = value;
}

EPI_NAMESPACE_END()
