#include "EpiDataVisualization/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Drawer/dvDrawerSeriesY.h"
#include "EpiDataVisualization/Drawer/dvDrawerSeriesY.cxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/Plot/Series/dvSeriesY.h"

EPI_NAMESPACE_BEGIN()

dvDrawerSeriesY::dvDrawerSeriesY(const gfxCamera& camera)
    : super(camera)
{
}

void dvDrawerSeriesY::Draw_Internal(const dvPlotBase& plot, const dvSeriesBase& series)
{
    epiAssert(series.Is(dvSeriesY::TypeID), "series should be instance of dvSeriesY");

    const dvSeriesY& seriesY = static_cast<const dvSeriesY&>(series);
}

EPI_NAMESPACE_END()
