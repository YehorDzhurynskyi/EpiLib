EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Camera/gfxCamera.h"
#include "EpiGraphics/Camera/gfxCamera.cxx"
EPI_GENREGION_END(include)

#include "glm/gtc/matrix_transform.hpp"

EPI_NAMESPACE_BEGIN()

epiMat4x4f gfxCamera::GetProjectionMatrix_Callback() const
{
    return GetProjectionMatrix_Internal();
}

epiMat4x4f gfxCamera::GetViewMatrix_Callback() const
{
    return glm::lookAt(GetPosition(), GetLookAtPosition(), GetUpDirection());
}

epiMat4x4f gfxCamera::GetProjectionMatrixInverse_Callback() const
{
    return glm::inverse(GetProjectionMatrix());
}

epiMat4x4f gfxCamera::GetViewMatrixInverse_Callback() const
{
    return glm::inverse(GetViewMatrix());
}

EPI_NAMESPACE_END()
