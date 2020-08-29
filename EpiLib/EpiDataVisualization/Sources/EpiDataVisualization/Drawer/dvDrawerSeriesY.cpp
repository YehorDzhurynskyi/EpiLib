EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Drawer/dvDrawerSeriesY.h"
#include "EpiDataVisualization/Drawer/dvDrawerSeriesY.cxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/Plot/Series/dvSeriesY.h"

EPI_NAMESPACE_BEGIN()

void dvDrawerSeriesY::Draw_Internal(gfxContext& ctx, const dvViewModelSeriesBase& series, const epiRect2f& worldFrame, const epiRect2f& uiFrame, epiFloat z)
{
    epiAssert(series.GetModel()->Is(dvSeriesY::TypeID), "The series should be instance of dvSeriesY");

    epiFloat x = 0.0f;
    const dvSeriesY* seriesY = static_cast<const dvSeriesY*>(series.GetModel());
    for (epiFloat y : seriesY->GetDataY())
    {
        const epiVec2f world(x, y);
        const epiVec2f yy = ((world - worldFrame.BottomLeft()) / worldFrame.GetSize()) * uiFrame.GetSize() + uiFrame.BottomLeft();

        DrawLineStrip(yy, series.GetColor(), z);

        x += seriesY->GetStepX();
    }
}

EPI_NAMESPACE_END()
