#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxContext.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"
#include "EpiGraphics/gfxVertexArray.h"

EPI_NAMESPACE_BEGIN()

class gfxContext : public Object
{
EPI_GENREGION_BEGIN(gfxContext)
public:
    EPI_GENHIDDEN_gfxContext()

    constexpr static MetaTypeID TypeID{0x30f166e8};

    enum gfxContext_PIDs
    {
        PID_VAO_NULL = 0x624075a1,
        PID_COUNT = 1
    };

protected:
    gfxVertexArray m_VAO_NULL;

EPI_GENREGION_END(gfxContext)
};

EPI_NAMESPACE_END()
