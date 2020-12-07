#include "EpiCore/MT/JobSystem/epiJobHandle.h"

EPI_NAMESPACE_BEGIN()

epiJobHandle::epiJobHandle(std::unique_ptr<epiIJob>&& job)
{
    m_Job = std::move(job);
}

epiBool epiJobHandle::HasJob() const
{
    return !!m_Job;
}

epiBool epiJobHandle::IsCompleted() const
{
    return HasJob() ? m_Job->GetIsCompleted() : false;
}

void epiJobHandle::Complete()
{
    if (HasJob())
    {
        m_Job->Complete();
    }
}

epiString epiJobHandle::ToString() const
{
    return HasJob() ? m_Job->ToString() : "EmptyJob";
}

EPI_NAMESPACE_END()
