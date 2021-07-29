EPI_GENREGION_BEGIN(include)
#include "EpiDrawer/Camera/drwCamera.h"
#include "EpiDrawer/Camera/drwCamera.cxx"
EPI_GENREGION_END(include)

#include "glm/gtc/matrix_transform.hpp"

EPI_NAMESPACE_BEGIN()

epiMat4x4f drwCamera::GetProjectionMatrix_Callback() const
{
    return GetProjectionMatrix_Internal();
}

epiMat4x4f drwCamera::GetViewMatrix_Callback() const
{
    // TODO: handle different hand rule depending on API
    // RH for OpenGL, LH for the others
    return glm::lookAtLH(GetPosition(), GetLookAtPosition(), GetUpDirection());
}

epiMat4x4f drwCamera::GetProjectionMatrixInverse_Callback() const
{
    return glm::inverse(GetProjectionMatrix());
}

epiMat4x4f drwCamera::GetViewMatrixInverse_Callback() const
{
    return glm::inverse(GetViewMatrix());
}

EPI_NAMESPACE_END()
