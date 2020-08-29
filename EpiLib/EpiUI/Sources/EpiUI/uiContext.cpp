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
    GetGFXContext().SceneBegin();

    m_Page.Draw(*this);

    GetGFXContext().SceneEnd();
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
    if (const gfxCamera* camera = GetGFXContext().GetCamera())
    {
        const epiMat4x4f& projInverse = camera->GetProjectionMatrixInverse();
        const epiMat4x4f& viewInverse = camera->GetViewMatrixInverse();

        return viewInverse * projInverse * (epiVec4f{ mouseNDCCoord.x, mouseNDCCoord.y, 0.0f, 1.0f });
    }

    return epiVec2f{ FLT_MAX, FLT_MAX };
}

epiVec2f uiContext::GetMouseUICoord_Callback() const
{
    return CalcMouseUICoordFromMouseNDCCoord(m_MouseNDCCoord);
}


EPI_NAMESPACE_END()
