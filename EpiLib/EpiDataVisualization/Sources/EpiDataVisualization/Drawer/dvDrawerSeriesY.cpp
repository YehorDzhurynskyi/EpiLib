EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Drawer/dvDrawerSeriesY.h"
#include "EpiDataVisualization/Drawer/dvDrawerSeriesY.cxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeriesY.h"

EPI_NAMESPACE_BEGIN()

void dvDrawerSeriesY::Draw_Internal(gfxContext& ctx, const dvViewModelSeriesBase& series, const epiRect2f& worldFrame, const epiRect2f& uiFrame, epiFloat z)
{
    epiAssert(series.GetModel()->Is(dSeriesY::TypeID), "The series should be instance of dvSeriesY");

    epiFloat x = 0.0f;
    const dSeriesY* seriesY = static_cast<const dSeriesY*>(series.GetModel());
    for (epiFloat y : seriesY->GetY())
    {
        const epiVec2f world(x, y);
        const epiVec2f yy = ((world - worldFrame.LeftBottom()) / worldFrame.GetSize()) * uiFrame.GetSize() + uiFrame.LeftBottom();

        DrawLineStrip(yy, series.GetColor(), z);

        x += seriesY->GetXStep();
    }
}

EPI_NAMESPACE_END()
