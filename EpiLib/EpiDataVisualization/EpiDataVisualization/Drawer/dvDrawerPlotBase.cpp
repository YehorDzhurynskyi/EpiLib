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

const epiU32 kMinGridLineCount = 6;
const epiU32 kMaxGridLineCount = 13;

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

    const epiFloat domain = box.GetWidth();
    const epiFloat range = box.GetHeight();

    epiFloat order = std::floorf(std::log10f(domain));
    epiFloat step = std::powf(10.0f, order);
    epiU32 nLines = std::roundf(domain / step);

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

    const gfxCameraUI* cameraUI = As<const gfxCameraUI>(&m_Camera);
    const epiRect2f& frame = cameraUI->GetFrameDimensionVirtual();

    const epiString str1 = fmt::format("{:.4f}", box.Left);
    const epiString str2 = fmt::format("{:.4f}", box.Right);

    const epiWString wstr1(str1.begin(), str1.end());
    drawerText.DrawText(wstr1.c_str(), { frame.Left, 0.0f }, 24.0f);

    const epiWString wstr2(str2.begin(), str2.end());
    drawerText.DrawText(wstr2.c_str(), { frame.Right - 100, 0.0f }, 24.0f);

    epiFloat offset = std::fabsf(std::fmodf(box.Left, step));
    if (box.Left >= 0.0f)
    {
        offset = step - offset;
    }

    epiFloat x = box.Left + offset;
    for (epiU32 i = 0; i < nLines; ++i)
    {
        const epiFloat xx = ((x - box.Left) / domain) * frame.GetWidth();
        epiVec2f p(frame.Left + xx, frame.Bottom);

        drawerPrimitive.DrawLine(p, p + epiVec2f(0.0f, frame.GetHeight()), Color::kDarkGray);

        const epiString str = fmt::format("{:.4f}", x);
        const epiWString wstr(str.begin(), str.end());
        drawerText.DrawText(wstr.c_str(), p + epiVec2f(5.0f, 5.0f), 20.0f);

        x += step;
    }
}

EPI_NAMESPACE_END()
