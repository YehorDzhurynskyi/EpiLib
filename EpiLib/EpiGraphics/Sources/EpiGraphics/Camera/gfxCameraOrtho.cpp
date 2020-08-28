EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Camera/gfxCameraOrtho.h"
#include "EpiGraphics/Camera/gfxCameraOrtho.cxx"
EPI_GENREGION_END(include)

#include <glm/gtc/matrix_transform.hpp>

EPI_NAMESPACE_BEGIN()

epiMat4x4f gfxCameraOrtho::GetProjectionMatrix_Internal() const
{
    const epiRect2f& rect = GetFrameDimension();
    const epiVec2f& tl = rect.TopLeft();
    const epiVec2f& br = rect.BottomRight();

    epiMat4x4f mat = glm::ortho(tl.x, br.x, br.y, tl.y, GetPlaneNear(), GetPlaneFar());
    mat[0][0] /= GetAspectRatio();

    return mat;
}

EPI_NAMESPACE_END()
