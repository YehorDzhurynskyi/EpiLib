#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Text/gfxTextRendered.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"
#include "EpiGraphics/gfxTexture.h"

EPI_NAMESPACE_BEGIN()

class gfxTextRendered : public Object
{
EPI_GENREGION_BEGIN(gfxTextRendered)
public:
    EPI_GENHIDDEN_gfxTextRendered()

    constexpr static MetaTypeID TypeID{0x55328726};

    enum gfxTextRendered_PIDs
    {
        PID_Texture = 0x4ddb34ee,
        PID_COUNT = 1
    };

protected:
    gfxTexture m_Texture;

EPI_GENREGION_END(gfxTextRendered)
};

EPI_NAMESPACE_END()
