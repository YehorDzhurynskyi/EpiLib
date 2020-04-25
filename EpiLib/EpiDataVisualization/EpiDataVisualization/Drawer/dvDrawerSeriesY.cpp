#include "EpiDataVisualization/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Drawer/dvDrawerSeriesY.h"
#include "EpiDataVisualization/Drawer/dvDrawerSeriesY.cxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/Plot/Series/dvSeriesY.h"

EPI_NAMESPACE_BEGIN()

void dvDrawerSeriesY::Draw_Internal(uiContext& uiContext, const dvViewModelPlot& plot, const dvViewModelSeriesBase& series)
{
    epiAssert(series.GetModel()->Is(dvSeriesY::TypeID), "series should be instance of dvSeriesY");

    const epiRect2f& box = plot.GetWorkingBox();

    // TODO: use local ui coord
    const epiRect2f& frame = uiContext.GetCamera().GetFrameDimensionVirtual();

    epiFloat x = 0.0f;
    const dvSeriesY* seriesY = static_cast<const dvSeriesY*>(series.GetModel());
    for (epiFloat y : seriesY->GetDataY())
    {
        const epiVec2f world(x, y);
        const epiVec2f yy = ((world - box.BottomLeft()) / box.GetSize()) * frame.GetSize() + frame.BottomLeft();

        DrawLineStrip(yy, series.GetColor());

        x += seriesY->GetStepX();
    }
}

EPI_NAMESPACE_END()
