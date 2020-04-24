#include "EpiUI/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiUI/uiContext.h"
#include "EpiUI/uiContext.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

void uiContext::OnMouseMove(const epiVec2f& mouseNDCCoord)
{
    m_MouseNDCCoord = mouseNDCCoord;
}

void uiContext::OnMousePrimary(const epiVec2f& mouseNDCCoord)
{
    if (uiWidget* widget = WidgetMouseOver())
    {
        widget->OnMousePrimary(mouseNDCCoord);
    }
}

void uiContext::OnMouseWheel(epiFloat dZoom)
{
    if (uiWidget* widget = WidgetMouseOver())
    {
        widget->OnMouseWheel(dZoom);
    }
}

void uiContext::SceneBegin()
{
    m_DrawerText.SceneBegin();
    m_DrawerPrimitive.SceneBegin();
}

void uiContext::SceneEnd()
{
    m_DrawerPrimitive.SceneEnd(m_Camera);
    m_DrawerText.SceneEnd(m_Camera);
}

uiWidget* uiContext::WidgetMouseOver() const
{
    const epiMat4x4f& projInverse = m_Camera.GetProjectionMatrixInverse();
    const epiMat4x4f& viewInverse = m_Camera.GetViewMatrixInverse();

    const epiVec2f mouseUICoord = viewInverse * projInverse * (epiVec4f{ m_MouseNDCCoord.x, m_MouseNDCCoord.y, 0.0f, 1.0f });

    auto it = std::find_if(m_Children.begin(), m_Children.end(), [&](const uiWidget* widget)
    {
        return widget->GetBBox().IsIn(mouseUICoord);
    });
    return it != m_Children.end() ? *it : nullptr;
}

EPI_NAMESPACE_END()
