#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxDrawer.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"
#include "EpiCore/Color.h"
#include "EpiGraphics/gfxContext.h"
#include "EpiGraphics/Text/gfxTextRenderedAtlas.h"

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
    //void DrawRect(Rect2f rect, Color edgeColor, Color fillColor);
    static void DrawLine(gfxContext& ctx, const epiVec3f& p1, const epiVec3f& p2, Color color);
    static void DrawGrid(gfxContext& ctx, const epiVec3f& position, const epiVec2f& dimension, const epiVec2s& nsteps);
    static void DrawText(gfxContext& ctx, const epiWChar* text, const epiVec2f& position, const gfxTextRenderedAtlas& atlas);
};

EPI_NAMESPACE_END()
