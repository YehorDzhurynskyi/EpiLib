#include "EpiDataVisualization/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Drawer/dvDrawerPlotBase.h"
#include "EpiDataVisualization/Drawer/dvDrawerPlotBase.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxDrawerPrimitive.h"
#include "EpiGraphics/gfxDrawerText.h"

#include "EpiGraphics/Camera/gfxCameraUI.h"

#include <glad/glad.h> // TODO: remove (should be available only from gfx)

#include "EpiCore/Color.h"

namespace
{

using namespace epi;

const epiU32 kMinGridLineCount = 6;
const epiU32 kMaxGridLineCount = 13;

void CalcGridMarkup(epiFloat domain, epiFloat& step, epiU32& nLines)
{
    epiFloat order = std::floorf(std::log10f(domain));
    step = std::powf(10.0f, order);
    nLines = std::roundf(domain / step);

    while (nLines < kMinGridLineCount || nLines > kMaxGridLineCount)
    {
        if (nLines > kMaxGridLineCount)
        {
            step *= 2.0f;
        }
        else if (nLines < kMinGridLineCount)
        {
            order -= 1.0f;
            step = std::powf(10.0f, order);
        }
        nLines = std::roundf(domain / step);
    }
}

}

EPI_NAMESPACE_BEGIN()

dvDrawerPlotBase::dvDrawerPlotBase(const gfxCamera& camera)
    : super(camera)
{
}

void dvDrawerPlotBase::Draw(const dvViewModelPlotBase& plot, gfxDrawerPrimitive& drawerPrimitive, gfxDrawerText& drawerText)
{
    Draw_Internal(plot, drawerPrimitive, drawerText);
}

void dvDrawerPlotBase::Draw_Internal(const dvViewModelPlotBase& plot, gfxDrawerPrimitive& drawerPrimitive, gfxDrawerText& drawerText)
{
    const epiRect2f& box = plot.GetClipBox() * plot.GetZoom() + plot.GetOrigin();

    const epiFloat domainX = box.GetWidth();
    const epiFloat domainY = box.GetHeight();

    const gfxCameraUI* cameraUI = As<const gfxCameraUI>(&m_Camera);
    const epiRect2f& frame = cameraUI->GetFrameDimensionVirtual();

    epiFloat stepX;
    epiU32 nLinesX;
    CalcGridMarkup(domainX, stepX, nLinesX);

    epiFloat stepY;
    epiU32 nLinesY;
    CalcGridMarkup(domainY, stepY, nLinesY);

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
    for (epiU32 i = 0; i < nLinesX; ++i)
    {
        const epiFloat xx = ((x - box.Left) / domainX) * frame.GetWidth();
        epiVec2f p(frame.Left + xx, frame.Bottom);

        drawerPrimitive.DrawLine(p, p + epiVec2f(0.0f, frame.GetHeight()), Color::kBlack);

        const epiFloat secondaryStepX = stepX / 3.0f;
        epiFloat x2 = x + secondaryStepX;
        for (epiU32 j = 0; j < 3; ++j)
        {
            const epiFloat xx2 = ((x2 - box.Left) / domainX) * frame.GetWidth();
            epiVec2f p(frame.Left + xx2, frame.Bottom);

            drawerPrimitive.DrawLine(p, p + epiVec2f(0.0f, frame.GetHeight()), Color::kLightGray * Color(1.0f, 1.0f, 1.0f, 0.5f));

            x2 += secondaryStepX;
        }

        const epiString str = fmt::format("{:.{}f}", x, fpWidthX);
        const epiWString wstr(str.begin(), str.end());
        drawerText.DrawText(wstr.c_str(), p + epiVec2f(5.0f, 5.0f), 20.0f);

        x += stepX;
    }

    epiFloat y = box.Bottom + offsetY;
    const epiU32 fpWidthY = std::ceilf(std::fabsf(std::min(0.0f, std::log10f(stepY))));
    for (epiU32 i = 0; i < nLinesY; ++i)
    {
        const epiFloat yy = ((y - box.Bottom) / domainY) * frame.GetHeight();
        epiVec2f p(frame.Left, frame.Bottom + yy);

        drawerPrimitive.DrawLine(p, p + epiVec2f(frame.GetWidth(), 0.0f), Color::kBlack);

        const epiFloat secondaryStepY = stepY / 3.0f;
        epiFloat y2 = y + secondaryStepY;
        for (epiU32 j = 0; j < 3; ++j)
        {
            const epiFloat yy2 = ((y2 - box.Bottom) / domainY) * frame.GetHeight();
            epiVec2f p(frame.Left, frame.Bottom + yy2);

            drawerPrimitive.DrawLine(p, p + epiVec2f(frame.GetWidth(), 0.0f), Color::kLightGray * Color(1.0f, 1.0f, 1.0f, 0.5f));

            y2 += secondaryStepY;
        }

        const epiString str = fmt::format("{:.{}f}", y, fpWidthY);
        const epiWString wstr(str.begin(), str.end());
        drawerText.DrawText(wstr.c_str(), p + epiVec2f(5.0f, 5.0f), 20.0f);

        y += stepY;
    }
}

EPI_NAMESPACE_END()
