#include "EpiDataVisualization/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/ViewModel/dvViewModelPlot.h"
#include "EpiDataVisualization/ViewModel/dvViewModelPlot.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

epiRect2f dvViewModelPlot::GetWorkingBox_Callback() const
{
    return GetClipBox() * GetZoom() + GetOrigin();
}

EPI_NAMESPACE_END()
