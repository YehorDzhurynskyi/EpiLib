#include "EpiUI/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiUI/uiWidget.h"
#include "EpiUI/uiWidget.cxx"
EPI_GENREGION_END(include)

#include "EpiUI/uiContext.h"
#include "EpiUI/uiLayout.h"

EPI_NAMESPACE_BEGIN()

void uiWidget::Update()
{
    for (auto& w : GetChildren())
    {
        w->Update();
    }
}

void uiWidget::Draw(uiContext& uiContext)
{
    for (auto& w : GetChildren())
    {
        w->Draw(uiContext);
    }
}

epiRect2f uiWidget::GetBBox_Callback() const
{
    epiRect2f bbox;
    bbox.Left = m_Position.x;
    bbox.Bottom = m_Position.y;
    bbox.Right = m_Position.x + m_Size.x;
    bbox.Top = m_Position.y + m_Size.y;

    return bbox;
}

void uiWidget::SetBBox_Callback(const epiRect2f& value)
{
    epiRect2f bbox;
    m_Position.x = bbox.Left;
    m_Position.y = bbox.Bottom;
    m_Size.x = bbox.Right - m_Position.x;
    m_Size.y = bbox.Top - m_Position.y;
}

epiFloat uiWidget::GetWidth_Callback() const
{
    return m_Size.x;
}

void uiWidget::SetWidth_Callback(epiFloat value)
{
    m_Size.x = value;
}

epiFloat uiWidget::GetHeight_Callback() const
{
    return m_Size.y;
}

void uiWidget::SetHeight_Callback(epiFloat value)
{
    m_Size.y = value;
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

void uiWidget::OnMouseFocus(epiBool focused)
{
    for (auto& w : GetChildren())
    {
        w->OnMouseFocus(focused);
    }
}

void uiWidget::OnResize()
{
    for (auto& w : m_Children)
    {
        w->OnResize();
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
    auto it = std::find_if(GetChildren().begin(),
                           GetChildren().end(),
                           [&](const uiWidget* widget)
    {
        return widget->GetBBox().IsIn(mouseUICoord);
    });

    return it != GetChildren().end() ? *it : nullptr;
}

EPI_NAMESPACE_END()
