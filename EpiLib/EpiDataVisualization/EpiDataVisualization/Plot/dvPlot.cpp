#include "EpiDataVisualization/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Plot/dvPlot.h"
#include "EpiDataVisualization/Plot/dvPlot.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

epiSize_t dvPlot::Size() const
{
    return m_Series.Size();
}

EPI_NAMESPACE_END()
