#include "EpiDataVisualization/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Drawer/dvDrawerPlotBase.h"
#include "EpiDataVisualization/Drawer/dvDrawerPlotBase.cxx"
EPI_GENREGION_END(include)

#include <glad/glad.h> // TODO: remove (should be available only from gfx)

namespace
{

const epiU32 kMinGridLineCount = 6;
const epiU32 kMaxGridLineCount = 10;

}

EPI_NAMESPACE_BEGIN()

void dvDrawerPlotBase::Draw(const dvPlotBase& plot)
{
    Draw_Internal(plot);
}

void dvDrawerPlotBase::Draw_Internal(const dvPlotBase& plot)
{
    const epiRect2f& clipbox = plot.GetClipBox();

    const epiFloat h = clipbox.Top - clipbox.Bottom;
    const epiFloat w = clipbox.Right - clipbox.Left;
    const epiS32 order = static_cast<epiS32>(std::log10f(w));

    epiU32 nLines = w / std::powf(10.0f, order);
    while (nLines < kMaxGridLineCount)
    {
        if (nLines >= kMinGridLineCount)
        {
            break;
        }
        nLines *= 2;
    }
    nLines = std::clamp(nLines, kMinGridLineCount, kMaxGridLineCount);

    const epiFloat xOffset = 0.0f;
    const epiFloat stride = w / nLines;
    epiFloat x = xOffset;

    for (epiU32 i = 0; i < nLines; ++i)
    {
        epiVec2f p(x, 0.0f);

        DrawLine(p, p + epiVec2f(0.0f, h), Color::kDarkGray);
        x += stride;
    }
}

EPI_NAMESPACE_END()
