EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Plot/Series/dvSeriesY.h"
#include "EpiDataVisualization/Plot/Series/dvSeriesY.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

void dvSeriesY::Add(epiFloat y)
{
    GetDataY().PushBack(y);
}

EPI_NAMESPACE_END()
