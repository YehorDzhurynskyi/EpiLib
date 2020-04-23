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

    const epiU32 N = 10;
    const epiFloat step = std::roundf(domain) / N;

    const gfxCameraUI* cameraUI = As<const gfxCameraUI>(&m_Camera);
    const epiRect2f& frame = cameraUI->GetFrameDimensionVirtual();

    const epiString str1 = fmt::format("{:.4f}", box.Left);
    const epiString str2 = fmt::format("{:.4f}", box.Right);

    const epiWString wstr1(str1.begin(), str1.end());
    drawerText.DrawText(wstr1.c_str(), { frame.Left, 0.0f }, 16.0f);

    const epiWString wstr2(str2.begin(), str2.end());
    drawerText.DrawText(wstr2.c_str(), { frame.Right - 100, 0.0f }, 24.0f);

    epiFloat x = 0.0f;
    epiFloat v = box.Left + domain - (N * step);
    for (epiU32 i = 0; i < N; ++i)
    {
        epiVec2f p(frame.Left + x, frame.Bottom);

        drawerPrimitive.DrawLine(p, p + epiVec2f(0.0f, frame.GetHeight()), Color::kDarkGray);

        const epiString str = fmt::format("{:.4f}", v);
        const epiWString wstr(str.begin(), str.end());
        drawerText.DrawText(wstr.c_str(), p + epiVec2f(5.0f, 5.0f), 20.0f);

        x += frame.GetWidth() / N;
        v += step;
    }

#if 0


    epiU32 nLines = domain / std::powf(10.0f, order);

    epiAssert(nLines > 0, "nLines should be greater than 0");
    while (nLines < kMaxGridLineCount)
    {
        if (nLines >= kMinGridLineCount)
        {
            break;
        }
        nLines *= 2;
    }
    nLines = std::clamp(nLines, kMinGridLineCount, kMaxGridLineCount);
    fprintf(stderr, "nLines: %u\n", nLines);

    const gfxCameraUI* cameraUI = As<const gfxCameraUI>(&m_Camera);
    const epiRect2f& frameBox = cameraUI->GetFrameDimensionVirtual();

    const epiFloat frameW = frameBox.GetWidth();
    const epiFloat frameH = frameBox.GetHeight();

    const epiFloat stride = frameW / nLines;
    const epiU32 strideDomain = domain / nLines;

    epiU32 domain = strideDomain;
    epiFloat x = stride;

    for (epiU32 i = 0; i < nLines; ++i)
    {
        epiVec2f p(frameBox.Left + x, frameBox.Bottom);

        drawerPrimitive.DrawLine(p, p + epiVec2f(0.0f, frameH), Color::kDarkGray);

        // TODO: replace with fmt
        const epiU32 sec = domain % 60;
        const epiU32 min = domain / 60;

        epiString str = fmt::format("{:02d}:{:02d}", min, sec);
        epiWString wstr(str.begin(), str.end());

        drawerText.DrawText(wstr.c_str(), p + epiVec2f(5.0f, 5.0f), 16.0f);

        x += stride;
        domain += strideDomain;
    }
#endif
}

EPI_NAMESPACE_END()
