#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxVertexArray.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxBindable.h"

EPI_NAMESPACE_BEGIN()

class gfxVertexArray : public gfxBindable
{
EPI_GENREGION_BEGIN(gfxVertexArray)
public:
    EPI_GENHIDDEN_gfxVertexArray()

    constexpr static MetaTypeID TypeID{0x7d61d88d};

    enum gfxVertexArray_PIDs
    {
        PID_ID = 0x11d3633a,
        PID_COUNT = 1
    };

protected:
    epiU32 m_ID{0};

EPI_GENREGION_END(gfxVertexArray)

public:
    void Bind() override;
    void UnBind() override;
};

EPI_NAMESPACE_END()
