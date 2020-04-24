#include "EpiDataVisualization/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/View/dvViewPlotBase.h"
#include "EpiDataVisualization/View/dvViewPlotBase.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

void dvViewPlotBase::OnMouseWheel(epiFloat dZoom)
{
    super::OnMouseWheel(dZoom);

    // TODO: use epi attrs force min max
    epi::dvViewModelPlotBase& vm = GetViewModel();
    const epiRect2f& box = vm.GetWorkingBox();
    const epiFloat domain = box.GetWidth();
    const epiFloat scale = 0.05f * std::powf(10.0f, std::log10f(domain) - 1.0f);

    epiFloat zoom = vm.GetZoomX() - scale * dZoom;
    zoom = std::clamp(zoom, 0.0001f, 1000000.0f);

    vm.SetZoomX(zoom);
}

EPI_NAMESPACE_END()
