#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Text/gfxTextRenderedAtlas.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/Text/gfxTextRendered.h"

EPI_NAMESPACE_BEGIN()

class gfxTextRenderedAtlas : public gfxTextRendered
{
EPI_GENREGION_BEGIN(gfxTextRenderedAtlas)
public:
    EPI_GENHIDDEN_gfxTextRenderedAtlas()

    constexpr static MetaTypeID TypeID{0x6de735c2};

    enum gfxTextRenderedAtlas_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxTextRenderedAtlas)
};

EPI_NAMESPACE_END()
