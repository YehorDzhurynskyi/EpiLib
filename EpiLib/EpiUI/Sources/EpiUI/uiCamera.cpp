EPI_GENREGION_BEGIN(include)
#include "EpiUI/uiCamera.h"
#include "EpiUI/uiCamera.cxx"
EPI_GENREGION_END(include)

#include <glm/gtc/matrix_transform.hpp>

EPI_NAMESPACE_BEGIN()

epiMat4x4f uiCamera::GetProjectionMatrix_Internal() const
{
    const epiRect2f& rect = GetFrameDimensionVirtual();
    const epiVec2f& tl = rect.TopLeft();
    const epiVec2f& br = rect.BottomRight();

    return glm::ortho(tl.x, br.x, br.y, tl.y, GetPlaneNear(), GetPlaneFar());;
}

EPI_NAMESPACE_END()
