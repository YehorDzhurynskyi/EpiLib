#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Camera/gfxCamera.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class gfxCamera : public Object
{
EPI_GENREGION_BEGIN(gfxCamera)
public:
    EPI_GENHIDDEN_gfxCamera()

    constexpr static MetaTypeID TypeID{0x9a7a8523};

    enum gfxCamera_PIDs
    {
        PID_ProjectionMatrix2D = 0xde0d136c,
        PID_ProjectionMatrix3D = 0xc716222d,
        PID_ViewMatrix2D = 0x2cf3cc9a,
        PID_ViewMatrix3D = 0x35e8fddb,
        PID_LookAtPosition = 0xbc0855f8,
        PID_Position = 0xbf5a86a3,
        PID_LookAtDirection = 0x400189bf,
        PID_UpDirection = 0xce9502ac,
        PID_PlaneFar = 0x23baa358,
        PID_PlaneNear = 0xaac85d59,
        PID_AspectRation = 0x1f0d1043,
        PID_COUNT = 11
    };

protected:
    epiMat3x3f GetProjectionMatrix2D_Callback() const;
    epiMat4x4f GetProjectionMatrix3D_Callback() const;
    epiMat3x3f GetViewMatrix2D_Callback() const;
    epiMat4x4f GetViewMatrix3D_Callback() const;
    void SetLookAtPosition_Callback(const epiVec3f& value);

protected:
    epiVec3f m_Position;
    epiVec3f m_LookAtDirection;
    epiVec3f m_UpDirection;
    epiFloat m_PlaneFar{0.0f};
    epiFloat m_PlaneNear{0.0f};
    epiFloat m_AspectRation{0.0f};

EPI_GENREGION_END(gfxCamera)

    
};

EPI_NAMESPACE_END()
