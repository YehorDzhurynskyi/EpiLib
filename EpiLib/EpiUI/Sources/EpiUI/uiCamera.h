#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiUI/uiCamera.hxx"
EPI_GENREGION_END(include)

#include "EpiDrawer/Camera/drwCamera.h"

EPI_NAMESPACE_BEGIN()

class uiCamera : public drwCamera
{
EPI_GENREGION_BEGIN(uiCamera)

EPI_GENHIDDEN_uiCamera()

public:
    constexpr static epiMetaTypeID TypeID{0x12ce033b};

    enum uiCamera_PIDs
    {
        PID_FrameDimensionPhysical = 0xc6386992,
        PID_FrameDimensionVirtual = 0x20eafb6c,
        PID_COUNT = 2
    };

protected:
    epiRect2f m_FrameDimensionPhysical{};
    epiRect2f m_FrameDimensionVirtual{};

EPI_GENREGION_END(uiCamera)

protected:
    epiMat4x4f GetProjectionMatrix_Internal() const override;
};

EPI_NAMESPACE_END()
