#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxDrawer.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"
#include "EpiCore/Color.h"
#include "EpiGraphics/gfxContext.h"

EPI_NAMESPACE_BEGIN()

// TODO: set as struct in epi file
class gfxDrawer : public Object
{
EPI_GENREGION_BEGIN(gfxDrawer)
public:
    EPI_GENHIDDEN_gfxDrawer()

    constexpr static MetaTypeID TypeID{0x74765527};

    enum gfxDrawer_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxDrawer)

public:
    //void DrawLine(epiVec2f p1, epiVec2f p2, Color color);
    //void DrawRect(Rect2f rect, Color edgeColor, Color fillColor);
    //void DrawText(const char* text, epiVec2f pos, epiFloat fontSize, Color color /* alignment, cliprect, wrapping */);
    void DrawGrid(gfxContext& ctx, const epiVec3f position, const epiVec2f& dimension, epiS32 nsteps);
};

EPI_NAMESPACE_END()
