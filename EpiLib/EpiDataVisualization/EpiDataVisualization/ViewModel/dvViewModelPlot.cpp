#include "EpiDataVisualization/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/ViewModel/dvViewModelPlot.h"
#include "EpiDataVisualization/ViewModel/dvViewModelPlot.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

epiFloat dvViewModelPlot::GetClipLeft_Callback() const
{
    return m_ClipBox.Left;
}

void dvViewModelPlot::SetClipLeft_Callback(epiFloat value)
{
    m_ClipBox.Left = value;
}

epiFloat dvViewModelPlot::GetClipTop_Callback() const
{
    return m_ClipBox.Top;
}

void dvViewModelPlot::SetClipTop_Callback(epiFloat value)
{
    m_ClipBox.Top = value;
}

epiFloat dvViewModelPlot::GetClipRight_Callback() const
{
    return m_ClipBox.Right;
}

void dvViewModelPlot::SetClipRight_Callback(epiFloat value)
{
    m_ClipBox.Right = value;
}

epiFloat dvViewModelPlot::GetClipBottom_Callback() const
{
    return m_ClipBox.Bottom;
}

void dvViewModelPlot::SetClipBottom_Callback(epiFloat value)
{
    m_ClipBox.Bottom = value;
}

epiFloat dvViewModelPlot::GetZoomX_Callback() const
{
    return m_Zoom.x;
}

void dvViewModelPlot::SetZoomX_Callback(epiFloat value)
{
    m_Zoom.x = value;
}

epiFloat dvViewModelPlot::GetZoomY_Callback() const
{
    return m_Zoom.y;
}

void dvViewModelPlot::SetZoomY_Callback(epiFloat value)
{
    m_Zoom.y = value;
}

epiRect2f dvViewModelPlot::GetWorkingBox_Callback() const
{
    return GetClipBox() * GetZoom() + GetOrigin();
}

EPI_NAMESPACE_END()
