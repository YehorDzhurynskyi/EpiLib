#include "EpiUI/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiUI/uiWidget.h"
#include "EpiUI/uiWidget.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

void uiWidget::Update()
{
    for (auto& w : m_Children)
    {
        w->Update();
    }
}

const epiVec2f& uiWidget::GetPosition_Callback() const
{
    return m_BBox.BottomLeft();
}

void uiWidget::SetPosition_Callback(const epiVec2f& value)
{
    m_BBox.Left = value.x;
    m_BBox.Bottom = value.y;
}

epiFloat uiWidget::GetWidth_Callback() const
{
    return m_BBox.GetWidth();
}

void uiWidget::SetWidth_Callback(epiFloat value)
{
    m_BBox.Right = value + m_BBox.Left;
}

epiFloat uiWidget::GetHeight_Callback() const
{
    return m_BBox.GetHeight();
}

void uiWidget::SetHeight_Callback(epiFloat value)
{
    m_BBox.Top = value + m_BBox.Bottom;
}

void uiWidget::OnMousePrimary(MouseAction action)
{
    if (uiWidget* widget = WidgetOverMouse(GetMouseLocalUICoord()))
    {
        widget->OnMousePrimary(action);
    }
}

void uiWidget::OnMouseWheel(epiFloat dZoom)
{
    if (uiWidget* widget = WidgetOverMouse(GetMouseLocalUICoord()))
    {
        widget->OnMouseWheel(dZoom);
    }
}

epiVec2f uiWidget::GetMouseLocalUICoord_Callback() const
{
    return GetMouseLocalUICoord_Internal();
}

epiVec2f uiWidget::GetMouseLocalUICoord_Internal() const
{
    const epiVec2f mouseLocalUICoord = m_Parent->GetMouseLocalUICoord();
    return mouseLocalUICoord; // TODO: implement
}

uiWidget* uiWidget::WidgetOverMouse(const epiVec2f& mouseUICoord) const
{
    auto it = std::find_if(m_Children.begin(), m_Children.end(), [&](const uiWidget* widget)
    {
        return widget->GetBBox().IsIn(mouseUICoord);
    });
    return it != m_Children.end() ? *it : nullptr;
}


EPI_NAMESPACE_END()
