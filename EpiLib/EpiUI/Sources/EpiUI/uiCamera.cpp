EPI_GENREGION_BEGIN(include)
#include "EpiUI/uiCamera.h"
#include "EpiUI/uiCamera.cxx"
EPI_GENREGION_END(include)

#include <glm/gtc/matrix_transform.hpp>

EPI_NAMESPACE_BEGIN()

epiMat4x4f uiCamera::GetProjectionMatrix_Internal() const
{
    const epiRect2f& rect = GetFrameDimensionVirtual();
    const epiVec2f& lt = rect.LeftTop();
    const epiVec2f& rb = rect.RightBottom();

    return glm::ortho(lt.x, rb.x, rb.y, lt.y, GetPlaneNear(), GetPlaneFar());;
}

EPI_NAMESPACE_END()
