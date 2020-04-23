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
        PID_FrameDimensionPhysical = 0xc6386992,
        PID_FrameDimensionVirtual = 0x20eafb6c,
        PID_COUNT = 2
    };

protected:
    epiRect2f m_FrameDimensionPhysical;
    epiRect2f m_FrameDimensionVirtual;

EPI_GENREGION_END(gfxCameraUI)

protected:
    epiMat4x4f GetProjectionMatrix_Internal() const override;
};

EPI_NAMESPACE_END()
