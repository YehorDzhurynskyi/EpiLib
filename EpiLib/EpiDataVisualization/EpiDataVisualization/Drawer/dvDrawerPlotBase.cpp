#include "EpiDataVisualization/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Drawer/dvDrawerPlotBase.h"
#include "EpiDataVisualization/Drawer/dvDrawerPlotBase.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxDrawerPrimitive.h"
#include "EpiGraphics/gfxDrawerText.h"

#include "EpiGraphics/Camera/gfxCameraOrtho.h"

#include <glad/glad.h> // TODO: remove (should be available only from gfx)

#include "EpiCore/Color.h"

namespace
{

const epiU32 kMinGridLineCount = 6;
const epiU32 kMaxGridLineCount = 10;

}

EPI_NAMESPACE_BEGIN()

dvDrawerPlotBase::dvDrawerPlotBase(const gfxCamera& camera)
    : super(camera)
{
}

void dvDrawerPlotBase::Draw(const dvPlotBase& plot, gfxDrawerPrimitive& drawerPrimitive, gfxDrawerText& drawerText)
{
    Draw_Internal(plot, drawerPrimitive, drawerText);
}

void dvDrawerPlotBase::Draw_Internal(const dvPlotBase& plot, gfxDrawerPrimitive& drawerPrimitive, gfxDrawerText& drawerText)
{
    const epiRect2f& clipbox = plot.GetClipBox();

    const epiFloat rangeH = clipbox.Top - clipbox.Bottom;
    const epiFloat domainW = clipbox.Right - clipbox.Left;
    const epiS32 order = static_cast<epiS32>(std::log10f(domainW));

    epiU32 nLines = domainW / std::powf(10.0f, order);
    while (nLines < kMaxGridLineCount)
    {
        if (nLines >= kMinGridLineCount)
        {
            break;
        }
        nLines *= 2;
    }
    nLines = std::clamp(nLines, kMinGridLineCount, kMaxGridLineCount);

    const gfxCameraOrtho* cameraOrtho = As<const gfxCameraOrtho>(&m_Camera);

    const epiRect2f& frameBox = cameraOrtho->GetFrameDimension();
    const epiFloat frameH = frameBox.Top - frameBox.Bottom;
    const epiFloat frameW = frameBox.Right - frameBox.Left;

    const epiFloat stride = frameW / nLines;
    const epiU32 strideDomain = domainW / nLines;

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
}

EPI_NAMESPACE_END()
