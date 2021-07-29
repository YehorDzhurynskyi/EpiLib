EPI_GENREGION_BEGIN(include)
#include "EpiDrawer/Camera/drwCameraPersp.h"
#include "EpiDrawer/Camera/drwCameraPersp.cxx"
EPI_GENREGION_END(include)

#include <glm/gtc/matrix_transform.hpp>

EPI_NAMESPACE_BEGIN()

epiMat4x4f drwCameraPersp::GetProjectionMatrix_Internal() const
{
    // TODO: handle different hand rule depending on API
    // RH for OpenGL, LH for the others
    return glm::perspectiveLH_ZO(GetFOV(), GetAspectRatio(), GetPlaneNear(), GetPlaneFar());
}

EPI_NAMESPACE_END()
