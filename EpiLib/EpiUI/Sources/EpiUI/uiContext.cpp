EPI_GENREGION_BEGIN(include)
#include "EpiUI/uiContext.h"
#include "EpiUI/uiContext.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

void uiContext::Update()
{
    m_Page.Update();
}

void uiContext::Draw()
{
    m_DrawerText.SceneBegin();
    m_DrawerPrimitive.SceneBegin();

    m_Page.Draw(*this);

    m_DrawerText.SceneEnd(m_Camera);
    m_DrawerPrimitive.SceneEnd(m_Camera);
}

void uiContext::OnMouseMove(const epiVec2f& mouseNDCCoord)
{
    m_MouseNDCCoord = mouseNDCCoord;
}

void uiContext::OnMousePrimary(uiMouseAction action)
{
    m_Page.OnMousePrimary(action);
}

void uiContext::OnMouseWheel(epiFloat dZoom)
{
    m_Page.OnMouseWheel(dZoom);
}

void uiContext::OnMouseFocus(epiBool focused)
{
    m_Page.OnMouseFocus(focused);
}

void uiContext::OnResize(const epiRect2f& frame)
{
    m_Page.SetBBox(frame);
    m_Page.OnResize();
}

epiVec2f uiContext::CalcMouseUICoordFromMouseNDCCoord(const epiVec2f& mouseNDCCoord) const
{
    // TODO: cache matrices
    const epiMat4x4f& projInverse = m_Camera.GetProjectionMatrixInverse();
    const epiMat4x4f& viewInverse = m_Camera.GetViewMatrixInverse();

    return viewInverse * projInverse * (epiVec4f{ mouseNDCCoord.x, mouseNDCCoord.y, 0.0f, 1.0f });
}

epiVec2f uiContext::GetMouseUICoord_Callback() const
{
    return CalcMouseUICoordFromMouseNDCCoord(m_MouseNDCCoord);
}


EPI_NAMESPACE_END()
