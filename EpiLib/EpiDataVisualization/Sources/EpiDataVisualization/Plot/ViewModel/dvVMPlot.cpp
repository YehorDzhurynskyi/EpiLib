EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Plot/ViewModel/dvVMPlot.h"
#include "EpiDataVisualization/Plot/ViewModel/dvVMPlot.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

dvVMPlot::dvVMPlot()
{
    epiRect2f bbox;
    bbox.Left = -FLT_MAX;
    bbox.Right = FLT_MAX;
    bbox.Bottom = -FLT_MAX;
    bbox.Top = FLT_MAX;

    SetBBox(bbox);

    epiRect2f clipbox;
    clipbox.Left = -1.0f;
    clipbox.Right = 1.0f;
    clipbox.Bottom = -1.0f;
    clipbox.Top = 1.0f;

    SetClipBox(clipbox);
}

epiRect2f dvVMPlot::GetClipBox_Callback() const
{
    epiRect2f box;
    box.Left = -1.0f;
    box.Right = 1.0f;
    box.Bottom = -1.0f;
    box.Top = 1.0f;

    epiRect2f clipbox = box * GetZoom() + GetOrigin();

    const epiRect2f& bbox = GetBBox();
    clipbox.Left = std::max(clipbox.Left, bbox.Left);
    clipbox.Bottom = std::max(clipbox.Bottom, bbox.Bottom);
    clipbox.Right = std::min(clipbox.Right, bbox.Right);
    clipbox.Top = std::min(clipbox.Top, bbox.Top);

    return clipbox;
}

void dvVMPlot::SetClipBox_Callback(const epiRect2f& value)
{
    SetZoom({ value.GetWidth() / 2.0f, value.GetHeight() / 2.0f });
    SetOrigin({ value.GetWidth() / 2.0f + value.Left, value.GetHeight() / 2.0f + value.Bottom });
}

void dvVMPlot::SetOrigin_Callback(const epiVec2f& value)
{
    epiRect2f box;
    box.Left = -1.0f;
    box.Right = 1.0f;
    box.Bottom = -1.0f;
    box.Top = 1.0f;

    const epiRect2f& bbox = GetBBox();
    epiRect2f clipbox = box * GetZoom();
    epiVec2f origin = value;

    const epiFloat halfX = clipbox.GetWidth() / 2.0f;
    const epiFloat halfY = clipbox.GetHeight() / 2.0f;

    origin.x = std::clamp(origin.x, bbox.Left + halfX, bbox.Right - halfX);
    origin.y = std::clamp(origin.y, bbox.Bottom + halfY, bbox.Top - halfY);

    m_Origin = origin;
}

void dvVMPlot::SetZoom_Callback(const epiVec2f& value)
{
    epiAssert(value.x > 0.0f && value.y > 0.0f, "zoom value should be greater than 0");

    epiVec2f zoom;

    const epiRect2f& bbox = GetBBox();
    zoom.x = std::min(value.x, bbox.GetWidth() / 2.0f);
    zoom.y = std::min(value.y, bbox.GetHeight() / 2.0f);

    m_Zoom = zoom;

    SetOrigin(GetOrigin());
}

EPI_NAMESPACE_END()
