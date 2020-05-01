#include "EpiDataVisualization/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Drawer/dvDrawerPlotTimeline.h"
#include "EpiDataVisualization/Drawer/dvDrawerPlotTimeline.cxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/Drawer/dvDrawerSeriesY.h"

#include "EpiUI/uiContext.h"

EPI_NAMESPACE_BEGIN()

void dvDrawerPlotTimeline::Draw(uiContext& uiContext, const dvViewModelPlot& plot, const epiRect2f& frame)
{
    const epiRect2f& box = plot.GetBBox();
    const epiFloat domainX = box.GetWidth();

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
        const epiFloat xx = ((x - box.Left) / domainX) * frame.GetWidth();
        epiVec2f p(frame.Left + xx, frame.Bottom);

        uiContext.GetDrawerPrimitive().DrawLine(p, p + epiVec2f(0.0f, frame.GetHeight()), Color::kBlack * Color(1.0f, 1.0f, 1.0f, 0.35f), -2.0f);

        const epiString str = fmt::format("{:.{}f}", x, fpWidthX);
        const epiWString wstr(str.begin(), str.end());
        uiContext.GetDrawerText().DrawText(wstr.c_str(), p + epiVec2f(5.0f, 5.0f), 24.0f, Color::kDarkGray, -2.0f);

        x += stepX;
    }

    for (const auto& series : plot.GetSeries())
    {
        dvDrawerSeriesY drawer;

        drawer.SceneBegin();
        drawer.Draw(uiContext, *series, box, frame, -2.0f);
        drawer.SceneEnd(uiContext.GetCamera());
    }

    const epiVec2f tl = ((plot.GetClipBox().TopLeft() - box.BottomLeft()) / box.GetSize()) * frame.GetSize() + frame.BottomLeft();
    const epiVec2f br = ((plot.GetClipBox().BottomRight() - box.BottomLeft()) / box.GetSize()) * frame.GetSize() + frame.BottomLeft();

    epiRect2f overlay(tl, br);
    uiContext.GetDrawerPrimitive().DrawQuad(overlay, Color(0x80, 0x80, 0x80, 0x60), -1.0f);
}

EPI_NAMESPACE_END()
