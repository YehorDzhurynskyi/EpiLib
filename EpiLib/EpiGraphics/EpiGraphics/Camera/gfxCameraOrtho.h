#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Camera/gfxCameraOrtho.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/Camera/gfxCamera.h"

EPI_NAMESPACE_BEGIN()

class gfxCameraOrtho : public gfxCamera
{
EPI_GENREGION_BEGIN(gfxCameraOrtho)
public:
    EPI_GENHIDDEN_gfxCameraOrtho()

    constexpr static MetaTypeID TypeID{0x704891b3};

    enum gfxCameraOrtho_PIDs
    {
        PID_FrameDimension = 0x3726fb2,
        PID_COUNT = 1
    };

protected:
    epiRect2f m_FrameDimension;

EPI_GENREGION_END(gfxCameraOrtho)

protected:
    epiMat4x4f GetProjectionMatrix_Internal() const override;
};

EPI_NAMESPACE_END()
