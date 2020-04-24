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
    const epiVec2f& mouseUICoord = CalcMouseUICoordFromNDC(mouseNDCCoord);

    if (uiWidget* widget = WidgetOverMouse(mouseUICoord))
    {
        epiVec2f mouseLocalUICoord = mouseUICoord;
        widget->OnMousePrimary(mouseLocalUICoord);
    }
}

void uiContext::OnMouseWheel(epiFloat dZoom)
{
    const epiVec2f& mouseUICoord = CalcMouseUICoordFromNDC(m_MouseNDCCoord);

    if (uiWidget* widget = WidgetOverMouse(mouseUICoord))
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

epiVec2f uiContext::CalcMouseUICoordFromNDC(const epiVec2f& mouseNDCCoord)
{
    const epiMat4x4f& projInverse = m_Camera.GetProjectionMatrixInverse();
    const epiMat4x4f& viewInverse = m_Camera.GetViewMatrixInverse();

    return viewInverse * projInverse * (epiVec4f{ mouseNDCCoord.x, mouseNDCCoord.y, 0.0f, 1.0f });
}

uiWidget* uiContext::WidgetOverMouse(const epiVec2f& mouseUICoord) const
{
    auto it = std::find_if(m_Children.begin(), m_Children.end(), [&](const uiWidget* widget)
    {
        return widget->GetBBox().IsIn(mouseUICoord);
    });
    return it != m_Children.end() ? *it : nullptr;
}

EPI_NAMESPACE_END()
