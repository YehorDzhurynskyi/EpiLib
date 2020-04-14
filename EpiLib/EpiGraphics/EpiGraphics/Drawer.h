#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Drawer.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"
#include "EpiCore/Color.h"

EPI_NAMESPACE_BEGIN()

class Drawer : public Object
{
EPI_GENREGION_BEGIN(Drawer)
public:
    EPI_GENHIDDEN_Drawer()

    constexpr static MetaTypeID TypeID{0xd2bc3b37};

    enum Drawer_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(Drawer)

public:
    void DrawLine(epiVec2f p1, epiVec2f p2, Color color);
    void DrawRect(Rect2f rect, Color edgeColor, Color fillColor);
    void DrawText(const char* text, epiVec2f pos, epiFloat fontSize, Color color /* alignment, cliprect, wrapping */);
};

EPI_NAMESPACE_END()
