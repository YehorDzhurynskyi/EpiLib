#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxContext.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"
#include "EpiGraphics/gfxVertexArray.h"
#include "EpiGraphics/Camera/gfxCameraOrtho.h"

EPI_NAMESPACE_BEGIN()

class gfxContext : public Object
{
EPI_GENREGION_BEGIN(gfxContext)
public:
    EPI_GENHIDDEN_gfxContext()

    constexpr static MetaTypeID TypeID{0x30f166e8};

    enum gfxContext_PIDs
    {
        PID_NullVertexArray = 0xee1c89c1,
        PID_Camera = 0x3cb0eb33,
        PID_COUNT = 2
    };

protected:
    gfxVertexArray m_NullVertexArray;
    gfxCameraOrtho m_Camera;

EPI_GENREGION_END(gfxContext)
};

EPI_NAMESPACE_END()
