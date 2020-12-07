EPI_GENREGION_BEGIN(include)
#include "EpiCore/MT/JobSystem/epiIJob.h"
#include "EpiCore/MT/JobSystem/epiIJob.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

void epiIJob::Complete()
{
    Execute();
    m_IsCompleted.store(true);
}

epiBool epiIJob::GetIsCompleted_Callback() const
{
    return m_IsCompleted.load();
}

EPI_NAMESPACE_END()
