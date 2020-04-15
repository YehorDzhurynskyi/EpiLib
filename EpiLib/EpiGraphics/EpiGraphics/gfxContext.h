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
        PID_NullVertexArray = 0xee1c89c1,
        PID_COUNT = 1
    };

protected:
    gfxVertexArray m_NullVertexArray;

EPI_GENREGION_END(gfxContext)
};

EPI_NAMESPACE_END()
