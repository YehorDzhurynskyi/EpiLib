#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/DrawerPlotBase.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"
#include "EpiCore/Color.h"

EPI_NAMESPACE_BEGIN()

class DrawerPlotBase : public Object
{
EPI_GENREGION_BEGIN(DrawerPlotBase)
public:
    EPI_GENHIDDEN_DrawerPlotBase()

    constexpr static MetaTypeID TypeID{0x73712b06};

    enum DrawerPlotBase_PIDs
    {
        PID_COUNT = 0
    };

protected:

EPI_GENREGION_END(DrawerPlotBase)

public:

    // TODO: move to EpiGraphics::DrawerBase
    void DrawLine(epiVec2f p1, epiVec2f p2, Color color);
    void DrawRect(Rect2f rect, Color edgeColor, Color fillColor);
    void DrawText(const char* text, epiVec2f pos, epiFloat fontSize, Color color /* alignment, cliprect, wrapping */);
};

EPI_NAMESPACE_END()
