#pragma once

#include "EpiCore/MT/JobSystem/epiIJob.h"

EPI_NAMESPACE_BEGIN()

class epiJobHandle
{
public:
    epiJobHandle() = default;
    epiJobHandle(std::unique_ptr<epiIJob>&& job);
    epiJobHandle(epiJobHandle&&) = default;
    epiJobHandle(const epiJobHandle&) = default;
    epiJobHandle& operator=(epiJobHandle&&) = default;
    epiJobHandle& operator=(const epiJobHandle&) = default;
    ~epiJobHandle() = default;

    epiBool HasJob() const;
    epiBool IsCompleted() const;
    void Complete();

    template<typename JobType>
    JobType* GetJob();

    epiString ToString() const;

protected:
    std::unique_ptr<epiIJob> m_Job;
};

template<typename JobType>
JobType* epiJobHandle::GetJob()
{
    static_assert(std::is_base_of_v<epiIJob, JobType>);

    return epiAs<JobType, epiIJob>(m_Job.get());
}


EPI_NAMESPACE_END()
