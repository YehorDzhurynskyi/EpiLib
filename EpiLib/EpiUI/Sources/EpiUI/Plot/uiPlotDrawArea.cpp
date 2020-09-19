EPI_GENREGION_BEGIN(include)
#include "EpiUI/Plot/uiPlotDrawArea.h"
#include "EpiUI/Plot/uiPlotDrawArea.cxx"
EPI_GENREGION_END(include)

#include "EpiUI/uiContext.h"

EPI_NAMESPACE_BEGIN()

void uiPlotDrawArea::Update()
{
    super::Update();

    if (m_MouseDragActive)
    {
        if (dvVMPlot* vm = GetViewModel())
        {
            vm->SetOrigin(m_MouseDragOrigin + m_MouseDragPosition - CalcMouseWorldCoord(m_MouseDragOrigin));
        }
    }
}

void uiPlotDrawArea::Draw(uiContext& uiContext)
{
    super::Draw(uiContext);

    if (dvVMPlot* vm = GetViewModel())
    {
        m_Drawer.Draw(uiContext.GetGFXContext(), *vm, GetBBox());
    }
}

void uiPlotDrawArea::OnMousePrimary(uiMouseAction action)
{
    super::OnMousePrimary(action);

    if (action == uiMouseAction::Release)
    {
        m_MouseDragActive = false;
    }
    else if (action == uiMouseAction::Click)
    {
        if (dvVMPlot* vm = GetViewModel())
        {
            m_MouseDragOrigin = vm->GetOrigin();
            m_MouseDragPosition = GetMouseWorldCoord();
            m_MouseDragActive = true;
        }
    }
}

void uiPlotDrawArea::OnMouseWheel(epiFloat dZoom)
{
    super::OnMouseWheel(dZoom);

    if (dvVMPlot* vm = GetViewModel())
    {
        const epiRect2f& box = vm->GetClipBox();
        const epiFloat domain = box.GetWidth();
        const epiFloat scale = 0.5f * std::powf(10.0f, std::log10f(domain) - 1.0f);

        epiVec2f zoom = vm->GetZoom();
        zoom.x -= scale * dZoom;
        zoom.x = std::clamp(zoom.x, 0.0001f, 1000000.0f); // TODO: use epi attrs force min max

        vm->SetZoom(zoom);
    }
}

void uiPlotDrawArea::OnMouseFocus(epiBool focused)
{
    super::OnMouseFocus(focused);

    if (!focused)
    {
        m_MouseDragActive = false;
    }
}

epiVec2f uiPlotDrawArea::CalcMouseWorldCoord(const epiVec2f& origin) const
{
    if (const dvVMPlot* vm = GetViewModel())
    {
        const epiRect2f& box = vm->GetClipBox();

        const epiVec2f mouseWorldCoord = ((GetMouseLocalUICoord() - GetPosition()) / GetSize()) * box.GetSize() + origin;

        return mouseWorldCoord;
    }

    return epiVec2f();
}

epiVec2f uiPlotDrawArea::GetMouseWorldCoord_Callback() const
{
    if (const dvVMPlot* vm = GetViewModel())
    {
        return CalcMouseWorldCoord(vm->GetOrigin());
    }

    return epiVec2f();
}

EPI_NAMESPACE_END()
