#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDrawer/Camera/drwCameraPersp.hxx"
EPI_GENREGION_END(include)

#include "EpiDrawer/Camera/drwCamera.h"

EPI_NAMESPACE_BEGIN()

class drwCameraPersp : public drwCamera
{
EPI_GENREGION_BEGIN(drwCameraPersp)

EPI_GENHIDDEN_drwCameraPersp()

public:
    constexpr static epiMetaTypeID TypeID{0x5ce32fd};

    enum drwCameraPersp_PIDs
    {
        PID_FOV = 0x7ebf8f6b,
        PID_COUNT = 1
    };

protected:
    epiFloat m_FOV{0.0f};

EPI_GENREGION_END(drwCameraPersp)

protected:
    epiMat4x4f GetProjectionMatrix_Internal() const override;
};

EPI_NAMESPACE_END()
