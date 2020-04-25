#include "EpiDataVisualization/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/View/dvViewPlotBase.h"
#include "EpiDataVisualization/View/dvViewPlotBase.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

void dvViewPlotBase::Update()
{
    super::Update();

    if (m_MouseDragActive)
    {
        dvViewModelPlotBase& vm = GetViewModel();
        vm.SetOrigin(m_MouseDragOrigin + m_MouseDragPosition - CalcMouseWorldCoord(m_MouseDragOrigin));
    }
}

void dvViewPlotBase::OnMousePrimary(MouseAction action)
{
    super::OnMousePrimary(action);

    if (action == MouseAction::Release)
    {
        m_MouseDragActive = false;
    }
    else if (action == MouseAction::Click)
    {
        const dvViewModelPlotBase& vm = GetViewModel();

        m_MouseDragOrigin = vm.GetOrigin();
        m_MouseDragPosition = GetMouseWorldCoord();
        m_MouseDragActive = true;
    }
}

void dvViewPlotBase::OnMouseWheel(epiFloat dZoom)
{
    super::OnMouseWheel(dZoom);

    epi::dvViewModelPlotBase& vm = GetViewModel();
    const epiRect2f& box = vm.GetWorkingBox();
    const epiFloat domain = box.GetWidth();
    const epiFloat scale = 0.05f * std::powf(10.0f, std::log10f(domain) - 1.0f);

    epiFloat zoom = vm.GetZoomX() - scale * dZoom;
    zoom = std::clamp(zoom, 0.0001f, 1000000.0f); // TODO: use epi attrs force min max

    vm.SetZoomX(zoom);
}

epiVec2f dvViewPlotBase::CalcMouseWorldCoord(const epiVec2f& origin) const
{
    const dvViewModelPlotBase& vm = GetViewModel();
    const epiRect2f& workingBox = vm.GetWorkingBox();

    const epiVec2f mouseWorldCoord = ((GetMouseLocalUICoord() - m_BBox.BottomLeft()) / m_BBox.GetSize()) * workingBox.GetSize() + origin;

    return mouseWorldCoord;
}

epiVec2f dvViewPlotBase::GetMouseWorldCoord_Callback() const
{
    const dvViewModelPlotBase& vm = GetViewModel();
    return CalcMouseWorldCoord(vm.GetOrigin());
}

EPI_NAMESPACE_END()
