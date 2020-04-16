#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Camera/gfxCameraPersp.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/Camera/gfxCamera.h"

EPI_NAMESPACE_BEGIN()

class gfxCameraPersp : public gfxCamera
{
EPI_GENREGION_BEGIN(gfxCameraPersp)
public:
    EPI_GENHIDDEN_gfxCameraPersp()

    constexpr static MetaTypeID TypeID{0x7f85441b};

    enum gfxCameraPersp_PIDs
    {
        PID_FOV = 0x7ebf8f6b,
        PID_COUNT = 1
    };

protected:
    epiFloat m_FOV{0.0f};

EPI_GENREGION_END(gfxCameraPersp)
};

EPI_NAMESPACE_END()
