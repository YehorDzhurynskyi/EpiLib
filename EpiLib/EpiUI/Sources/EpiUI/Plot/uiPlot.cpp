EPI_GENREGION_BEGIN(include)
#include "EpiUI/Plot/uiPlot.h"
#include "EpiUI/Plot/uiPlot.cxx"
EPI_GENREGION_END(include)

#include "EpiUI/uiContext.h"
#include "EpiUI/Plot/uiPlotDrawArea.h"

EPI_NAMESPACE_BEGIN()

uiPlot::uiPlot()
{
    dvVMPlot& vm = GetViewModel();

    uiPlotDrawArea& drawArea = Add<uiPlotDrawArea>();
    drawArea.SetViewModel(&vm);
}

EPI_NAMESPACE_END()
