#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDrawer/Camera/drwCamera.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class drwCamera : public Object
{
EPI_GENREGION_BEGIN(drwCamera)

EPI_GENHIDDEN_drwCamera()

public:
    constexpr static epiMetaTypeID TypeID{0xad4ef6de};

    enum drwCamera_PIDs
    {
        PID_ProjectionMatrix = 0x8e67f662,
        PID_ViewMatrix = 0x58d90ca6,
        PID_ProjectionMatrixInverse = 0x93a25de1,
        PID_ViewMatrixInverse = 0xb3318c36,
        PID_Position = 0xbf5a86a3,
        PID_LookAtPosition = 0xbc0855f8,
        PID_UpDirection = 0xce9502ac,
        PID_PlaneFar = 0x23baa358,
        PID_PlaneNear = 0xaac85d59,
        PID_AspectRatio = 0xd8f95d9b,
        PID_COUNT = 10
    };

protected:
    epiMat4x4f GetProjectionMatrix_Callback() const;
    epiMat4x4f GetViewMatrix_Callback() const;
    epiMat4x4f GetProjectionMatrixInverse_Callback() const;
    epiMat4x4f GetViewMatrixInverse_Callback() const;

protected:
    epiVec3f m_Position{};
    epiVec3f m_LookAtPosition{};
    epiVec3f m_UpDirection{};
    epiFloat m_PlaneFar{0.0f};
    epiFloat m_PlaneNear{0.0f};
    epiFloat m_AspectRatio{0.0f};

EPI_GENREGION_END(drwCamera)

protected:
    virtual epiMat4x4f GetProjectionMatrix_Internal() const = 0;
};

EPI_NAMESPACE_END()
