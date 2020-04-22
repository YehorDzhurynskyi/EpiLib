#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Camera/gfxCameraUI.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/Camera/gfxCamera.h"

EPI_NAMESPACE_BEGIN()

class gfxCameraUI : public gfxCamera
{
EPI_GENREGION_BEGIN(gfxCameraUI)
public:
    EPI_GENHIDDEN_gfxCameraUI()

    constexpr static MetaTypeID TypeID{0xaa6ed86e};

    enum gfxCameraUI_PIDs
    {
        PID_FrameDimension = 0x3726fb2,
        PID_COUNT = 1
    };

protected:
    epiRect2f m_FrameDimension;

EPI_GENREGION_END(gfxCameraUI)

protected:
    epiMat4x4f GetProjectionMatrix_Internal() const override;
};

EPI_NAMESPACE_END()
