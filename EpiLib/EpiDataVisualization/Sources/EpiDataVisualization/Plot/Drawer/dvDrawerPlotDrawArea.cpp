EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Plot/Drawer/dvDrawerPlotDrawArea.h"
#include "EpiDataVisualization/Plot/Drawer/dvDrawerPlotDrawArea.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxDrawerPrimitive.h"
#include "EpiGraphics/gfxDrawerText.h"

#include "EpiCore/Color.h"

#include <fmt/core.h>

namespace
{

const epiU32 kGridLineCountSecondary = 6;
const epiU32 kGridLineCountMin = 6;
const epiU32 kGridLineCountMax = 13;

}

EPI_NAMESPACE_BEGIN()

void dvDrawerPlotDrawArea::Draw(gfxContext& ctx, const dvVMPlot& plot, const epiRect2f& frame)
{
    const epiRect2f& box = plot.GetClipBox();

    const epiFloat domainX = box.GetWidth();
    const epiFloat domainY = box.GetHeight();

    epiFloat stepX;
    epiU32 nLinesX;
    GridMarkup(domainX, stepX, nLinesX);

    epiFloat stepY;
    epiU32 nLinesY;
    GridMarkup(domainY, stepY, nLinesY);

    epiFloat offsetX = std::fabsf(std::fmodf(box.Left, stepX));
    if (box.Left >= 0.0f)
    {
        offsetX = stepX - offsetX;
    }

    epiFloat offsetY = std::fabsf(std::fmodf(box.Bottom, stepY));
    if (box.Bottom >= 0.0f)
    {
        offsetY = stepY - offsetY;
    }

    epiFloat x = box.Left + offsetX;
    const epiU32 fpWidthX = std::ceilf(std::fabsf(std::min(0.0f, std::log10f(stepX))));
    for (epiU32 i = 0; i < nLinesX + 1; ++i)
    {
        const epiFloat xx = ((x - box.Left) / domainX) * frame.GetWidth() + frame.Left;
        epiVec2f p(xx, frame.Bottom);

        ctx.GetDrawerPrimitive().DrawLine(p, p + epiVec2f(0.0f, frame.GetHeight()), Color::kBlack * Color(1.0f, 1.0f, 1.0f, 0.35f));

        const epiFloat secondaryStepX = stepX / static_cast<epiFloat>(kGridLineCountSecondary);
        epiFloat x2 = x - stepX + secondaryStepX;
        for (epiU32 j = 0; j < kGridLineCountSecondary; ++j)
        {
            const epiFloat xx2 = ((x2 - box.Left) / domainX) * frame.GetWidth() + frame.Left;
            epiVec2f p(xx2, frame.Bottom);

            ctx.GetDrawerPrimitive().DrawLine(p, p + epiVec2f(0.0f, frame.GetHeight()), Color::kLightGray * Color(1.0f, 1.0f, 1.0f, 0.15f));

            x2 += secondaryStepX;
        }

        const epiString str = fmt::format("{:.{}f}", x, fpWidthX);
        const epiWString wstr(str.begin(), str.end());

        // TODO: make text size independent from actual frame size
        ctx.GetDrawerText().DrawText(wstr.c_str(), p + epiVec2f(5.0f, 5.0f), 36.0f);

        x += stepX;
    }

    epiFloat y = box.Bottom + offsetY;
    const epiU32 fpWidthY = std::ceilf(std::fabsf(std::min(0.0f, std::log10f(stepY))));
    for (epiU32 i = 0; i < nLinesY + 1; ++i)
    {
        const epiFloat yy = ((y - box.Bottom) / domainY) * frame.GetHeight() + frame.Bottom;
        epiVec2f p(frame.Left, yy);

        ctx.GetDrawerPrimitive().DrawLine(p, p + epiVec2f(frame.GetWidth(), 0.0f), Color::kBlack * Color(1.0f, 1.0f, 1.0f, 0.35f));

        const epiFloat secondaryStepY = stepY / static_cast<epiFloat>(kGridLineCountSecondary);
        epiFloat y2 = y - stepY + secondaryStepY;
        for (epiU32 j = 0; j < kGridLineCountSecondary; ++j)
        {
            const epiFloat yy2 = ((y2 - box.Bottom) / domainY) * frame.GetHeight() + frame.Bottom;
            epiVec2f p(frame.Left, yy2);

            ctx.GetDrawerPrimitive().DrawLine(p, p + epiVec2f(frame.GetWidth(), 0.0f), Color::kLightGray * Color(1.0f, 1.0f, 1.0f, 0.15f));

            y2 += secondaryStepY;
        }

        const epiString str = fmt::format("{:.{}f}", y, fpWidthY);
        const epiWString wstr(str.begin(), str.end());

        // TODO: make text size independent from actual frame size
        ctx.GetDrawerText().DrawText(wstr.c_str(), p + epiVec2f(5.0f, 5.0f), 36.0f);

        y += stepY;
    }
}

void dvDrawerPlotDrawArea::GridMarkup(epiFloat domain, epiFloat& outStep, epiU32& outNLines)
{
    epiFloat order = std::floorf(std::log10f(domain));
    outStep = std::powf(10.0f, order);
    outNLines = std::roundf(domain / outStep);

    while (outNLines < kGridLineCountMin || outNLines > kGridLineCountMax)
    {
        if (outNLines > kGridLineCountMax)
        {
            outStep *= 2.0f;
        }
        else if (outNLines < kGridLineCountMin)
        {
            order -= 1.0f;
            outStep = std::powf(10.0f, order);
        }
        outNLines = std::roundf(domain / outStep);
    }
}

EPI_NAMESPACE_END()
