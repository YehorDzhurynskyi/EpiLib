#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Camera/gfxCameraPersp.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/Camera/gfxCamera.h"

EPI_NAMESPACE_BEGIN()

class gfxCameraPersp : public gfxCamera
{
EPI_GENREGION_BEGIN(gfxCameraPersp)

EPI_GENHIDDEN_gfxCameraPersp()

public:
    constexpr static epiMetaTypeID TypeID{0x7f85441b};

    enum gfxCameraPersp_PIDs
    {
        PID_FOV = 0x7ebf8f6b,
        PID_COUNT = 1
    };

protected:
    epiFloat m_FOV{0.0f};

EPI_GENREGION_END(gfxCameraPersp)

protected:
    epiMat4x4f GetProjectionMatrix_Internal() const override;
};

EPI_NAMESPACE_END()
