#include "EpiGraphics/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Camera/gfxCameraUI.h"
#include "EpiGraphics/Camera/gfxCameraUI.cxx"
EPI_GENREGION_END(include)

#include <glm/gtc/matrix_transform.hpp>

EPI_NAMESPACE_BEGIN()

epiMat4x4f gfxCameraUI::GetProjectionMatrix_Internal() const
{
    const epiRect2f& rect = GetFrameDimension();
    const epiVec2f& tl = rect.TopLeft();
    const epiVec2f& br = rect.BottomRight();

    return glm::ortho(tl.x, br.x, br.y, tl.y, GetPlaneNear(), GetPlaneFar());;
}

EPI_NAMESPACE_END()
