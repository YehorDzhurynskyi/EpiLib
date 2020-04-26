#include "EpiDataVisualization/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Drawer/dvDrawerPlotRealtime.h"
#include "EpiDataVisualization/Drawer/dvDrawerPlotRealtime.cxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/Drawer/dvDrawerSeriesY.h"

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

    epiRect2f frameTimeLinePanel = frameTimeLine;
    frameTimeLinePanel.Top += kTimeLineGap;

    epiFloat stepX;
    epiU32 nLinesX;
    GridMarkup(domainX, stepX, nLinesX);

    epiFloat offsetX = std::fabsf(std::fmodf(box.Left, stepX));
    if (box.Left >= 0.0f)
    {
        offsetX = stepX - offsetX;
    }

    uiContext.GetDrawerPrimitive().DrawQuad(frameTimeLinePanel, Color(0xfa, 0xfa, 0xfa, 0xff), -10.0f);

    epiFloat x = box.Left + offsetX;
    const epiU32 fpWidthX = std::ceilf(std::fabsf(std::min(0.0f, std::log10f(stepX))));
    for (epiU32 i = 0; i < nLinesX + 1; ++i)
    {
        const epiFloat xx = ((x - box.Left) / domainX) * frameTimeLine.GetWidth();
        epiVec2f p(frameTimeLine.Left + xx, frameTimeLine.Bottom);

        uiContext.GetDrawerPrimitive().DrawLine(p, p + epiVec2f(0.0f, frameTimeLine.GetHeight()), Color::kBlack * Color(1.0f, 1.0f, 1.0f, 0.35f), -2.0f);

        const epiString str = fmt::format("{:.{}f}", x, fpWidthX);
        const epiWString wstr(str.begin(), str.end());
        uiContext.GetDrawerText().DrawText(wstr.c_str(), p + epiVec2f(5.0f, 5.0f), 24.0f, Color::kDarkGray, -2.0f);

        x += stepX;
    }

    for (const auto& series : plot.GetSeries())
    {
        dvDrawerSeriesY drawer;

        drawer.SceneBegin();
        drawer.Draw(uiContext, *series, box, frameTimeLine, -2.0f);
        drawer.SceneEnd(uiContext.GetCamera());
    }

    const epiVec2f tl = ((plot.GetClipBox().TopLeft() - box.BottomLeft()) / box.GetSize()) * frameTimeLine.GetSize() + frameTimeLine.BottomLeft();
    const epiVec2f br = ((plot.GetClipBox().BottomRight() - box.BottomLeft()) / box.GetSize()) * frameTimeLine.GetSize() + frameTimeLine.BottomLeft();

    epiRect2f overlay(tl, br);
    uiContext.GetDrawerPrimitive().DrawQuad(overlay, Color(0x80, 0x80, 0x80, 0x60), -1.0f);
}

EPI_NAMESPACE_END()
