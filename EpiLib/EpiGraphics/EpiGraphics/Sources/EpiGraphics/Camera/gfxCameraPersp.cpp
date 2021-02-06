EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Camera/gfxCameraPersp.h"
#include "EpiGraphics/Camera/gfxCameraPersp.cxx"
EPI_GENREGION_END(include)

#include <glm/gtc/matrix_transform.hpp>

EPI_NAMESPACE_BEGIN()

epiMat4x4f gfxCameraPersp::GetProjectionMatrix_Internal() const
{
    return glm::perspective(GetFOV(), GetAspectRatio(), GetPlaneNear(), GetPlaneFar());
}

EPI_NAMESPACE_END()
