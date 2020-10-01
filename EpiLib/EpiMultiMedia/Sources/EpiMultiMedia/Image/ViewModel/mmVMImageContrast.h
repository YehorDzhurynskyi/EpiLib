#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageContrast.hxx"
EPI_GENREGION_END(include)

#include "EpiMultimedia/Image/ViewModel/mmVMImageBase.h"

EPI_NAMESPACE_BEGIN()

class mmVMImageContrast : public mmVMImageBase
{
EPI_GENREGION_BEGIN(mmVMImageContrast)

EPI_GENHIDDEN_mmVMImageContrast()

public:
    constexpr static epiMetaTypeID TypeID{0xc5f69e9d};

    enum mmVMImageContrast_PIDs
    {
        PID_Contrast = 0x5a3b585e,
        PID_COUNT = 1
    };

protected:
    void SetContrast_Callback(epiS8 value);

protected:
    epiS8 m_Contrast{0};

EPI_GENREGION_END(mmVMImageContrast)
};

EPI_NAMESPACE_END()
