#include "EpiGraphics/pch.h"

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

EPI_NAMESPACE_END()
