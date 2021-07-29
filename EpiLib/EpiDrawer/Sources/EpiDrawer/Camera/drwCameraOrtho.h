#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDrawer/Camera/drwCameraOrtho.hxx"
EPI_GENREGION_END(include)

#include "EpiDrawer/Camera/drwCamera.h"

EPI_NAMESPACE_BEGIN()

class drwCameraOrtho : public drwCamera
{
EPI_GENREGION_BEGIN(drwCameraOrtho)

EPI_GENHIDDEN_drwCameraOrtho()

public:
    constexpr static epiMetaTypeID TypeID{0xa03e755};

    enum drwCameraOrtho_PIDs
    {
        PID_FrameDimension = 0x3726fb2,
        PID_COUNT = 1
    };

protected:
    epiRect2f m_FrameDimension{};

EPI_GENREGION_END(drwCameraOrtho)

protected:
    epiMat4x4f GetProjectionMatrix_Internal() const override;
};

EPI_NAMESPACE_END()
