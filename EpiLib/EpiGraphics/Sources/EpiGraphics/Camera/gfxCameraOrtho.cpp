EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Camera/gfxCameraOrtho.h"
#include "EpiGraphics/Camera/gfxCameraOrtho.cxx"
EPI_GENREGION_END(include)

#include <glm/gtc/matrix_transform.hpp>

EPI_NAMESPACE_BEGIN()

epiMat4x4f gfxCameraOrtho::GetProjectionMatrix_Internal() const
{
    const epiRect2f& rect = GetFrameDimension();
    const epiVec2f& lb = rect.LeftBottom();
    const epiVec2f& rt = rect.RightTop();

    epiMat4x4f mat = glm::ortho(lb.x, rt.x, lb.y, rt.y, GetPlaneNear(), GetPlaneFar());
    mat[0][0] /= GetAspectRatio();

    return mat;
}

EPI_NAMESPACE_END()
