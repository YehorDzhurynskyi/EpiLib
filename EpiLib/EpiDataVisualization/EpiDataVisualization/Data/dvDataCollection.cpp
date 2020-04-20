#include "EpiDataVisualization/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Data/dvDataCollection.h"
#include "EpiDataVisualization/Data/dvDataCollection.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

void dvDataCollection::PushBack(epiFloat value)
{
    m_Buffer.PushBack(std::move(value));
}

EPI_NAMESPACE_END()
