#include "EpiDataVisualization/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/ViewModel/dvViewModelPlotBase.h"
#include "EpiDataVisualization/ViewModel/dvViewModelPlotBase.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

epiFloat dvViewModelPlotBase::GetClipLeft_Callback() const
{
    return m_ClipBox.Left;
}

void dvViewModelPlotBase::SetClipLeft_Callback(epiFloat value)
{
    m_ClipBox.Left = value;
}

epiFloat dvViewModelPlotBase::GetClipTop_Callback() const
{
    return m_ClipBox.Top;
}

void dvViewModelPlotBase::SetClipTop_Callback(epiFloat value)
{
    m_ClipBox.Top = value;
}

epiFloat dvViewModelPlotBase::GetClipRight_Callback() const
{
    return m_ClipBox.Right;
}

void dvViewModelPlotBase::SetClipRight_Callback(epiFloat value)
{
    m_ClipBox.Right = value;
}

epiFloat dvViewModelPlotBase::GetClipBottom_Callback() const
{
    return m_ClipBox.Bottom;
}

void dvViewModelPlotBase::SetClipBottom_Callback(epiFloat value)
{
    m_ClipBox.Bottom = value;
}

epiFloat dvViewModelPlotBase::GetZoomX_Callback() const
{
    return m_Zoom.x;
}

void dvViewModelPlotBase::SetZoomX_Callback(epiFloat value)
{
    m_Zoom.x = value;
}

epiFloat dvViewModelPlotBase::GetZoomY_Callback() const
{
    return m_Zoom.y;
}

void dvViewModelPlotBase::SetZoomY_Callback(epiFloat value)
{
    m_Zoom.y = value;
}

EPI_NAMESPACE_END()
