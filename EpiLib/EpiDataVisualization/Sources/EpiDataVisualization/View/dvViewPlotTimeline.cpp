EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/View/dvViewPlotTimeline.h"
#include "EpiDataVisualization/View/dvViewPlotTimeline.cxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/View/dvViewPlot.h"

EPI_NAMESPACE_BEGIN()

void dvViewPlotTimeline::Update()
{
    super::Update();

    if (m_MouseDragActive)
    {
        if (dvViewModelPlot* vm = GetViewModel())
        {
            vm->SetOrigin(m_MouseDragOrigin + m_MouseDragPosition - CalcMouseWorldCoord(m_MouseDragOrigin));
        }
    }
}

void dvViewPlotTimeline::Draw(uiContext& uiContext)
{
    super::Draw(uiContext);

    if (dvViewModelPlot* vm = GetViewModel())
    {
        m_Drawer.Draw(uiContext, *vm, GetBBox());
    }
}

void dvViewPlotTimeline::OnMousePrimary(uiMouseAction action)
{
    super::OnMousePrimary(action);

    if (action == uiMouseAction::Release)
    {
        m_MouseDragActive = false;
    }
    else if (action == uiMouseAction::Click)
    {
        if (dvViewModelPlot* vm = GetViewModel())
        {
            dvViewPlot* parent = As<dvViewPlot, uiWidget>(GetParent());
            m_MouseDragOrigin = vm->GetOrigin();
            m_MouseDragPosition = GetMouseWorldCoord();
            m_MouseDragActive = true;
        }
    }
}

void dvViewPlotTimeline::OnMouseWheel(epiFloat dZoom)
{
    super::OnMouseWheel(dZoom);

    if (dvViewModelPlot* vm = GetViewModel())
    {
        const epiRect2f& box = vm->GetBBox();
        const epiFloat domain = box.GetWidth();
        const epiFloat scale = 0.5f * std::powf(10.0f, std::log10f(domain) - 1.0f);

        epiVec2f zoom = vm->GetZoom();
        zoom.x -= scale * dZoom;
        zoom.x = std::clamp(zoom.x, 0.0001f, 1000000.0f); // TODO: use epi attrs force min max

        vm->SetZoom(zoom);
    }
}

void dvViewPlotTimeline::OnMouseFocus(epiBool focused)
{
    super::OnMouseFocus(focused);

    if (!focused)
    {
        m_MouseDragActive = false;
    }
}

epiVec2f dvViewPlotTimeline::CalcMouseWorldCoord(const epiVec2f& origin) const
{
    if (const dvViewModelPlot* vm = GetViewModel())
    {
        const epiRect2f& box = vm->GetBBox();

        const epiVec2f mouseWorldCoord = ((GetMouseLocalUICoord() - GetPosition()) / GetSize()) * box.GetSize() + origin;

        return mouseWorldCoord;
    }

    return epiVec2f();
}

epiVec2f dvViewPlotTimeline::GetMouseWorldCoord_Callback() const
{
    if (const dvViewModelPlot* vm = GetViewModel())
    {
        return CalcMouseWorldCoord(vm->GetOrigin());
    }

    return epiVec2f();
}

EPI_NAMESPACE_END()
