#include "EpiDataVisualization/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Drawer/dvDrawerPlotRealtime.h"
#include "EpiDataVisualization/Drawer/dvDrawerPlotRealtime.cxx"
EPI_GENREGION_END(include)

namespace
{

const epiU32 kTimeLineHeight = 200;
const epiU32 kTimeLineGap = 20;

}

EPI_NAMESPACE_BEGIN()

void dvDrawerPlotRealtime::Draw_Internal(uiContext& uiContext, const dvViewModelPlot& plot, const epiRect2f& frame)
{
    epiRect2f frameGrid = frame;
    frameGrid.Bottom = frame.Bottom + kTimeLineHeight + kTimeLineGap;

    super::Draw_Internal(uiContext, plot, frameGrid);

    const epiRect2f& box = plot.GetBBox();
    const epiFloat domainX = box.GetWidth();

    epiRect2f frameTimeLine = frame;
    frameTimeLine.Top = frame.Bottom + kTimeLineHeight;

    epiFloat stepX;
    epiU32 nLinesX;
    GridMarkup(domainX, stepX, nLinesX);

    epiFloat offsetX = std::fabsf(std::fmodf(box.Left, stepX));
    if (box.Left >= 0.0f)
    {
        offsetX = stepX - offsetX;
    }

    epiFloat x = box.Left + offsetX;
    const epiU32 fpWidthX = std::ceilf(std::fabsf(std::min(0.0f, std::log10f(stepX))));
    for (epiU32 i = 0; i < nLinesX + 1; ++i)
    {
        const epiFloat xx = ((x - box.Left) / domainX) * frameTimeLine.GetWidth();
        epiVec2f p(frameTimeLine.Left + xx, frameTimeLine.Bottom);

        uiContext.GetDrawerPrimitive().DrawLine(p, p + epiVec2f(0.0f, frameTimeLine.GetHeight()), Color::kBlack * Color(1.0f, 1.0f, 1.0f, 0.35f));

        const epiString str = fmt::format("{:.{}f}", x, fpWidthX);
        const epiWString wstr(str.begin(), str.end());
        uiContext.GetDrawerText().DrawText(wstr.c_str(), p + epiVec2f(5.0f, 5.0f), 20.0f);

        x += stepX;
    }
}

EPI_NAMESPACE_END()
