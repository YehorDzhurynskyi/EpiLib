#pragma once

#include "EpiCore/MT/JobSystem/epiJobHandle.h"

EPI_NAMESPACE_BEGIN()

class epiJobWorker
{
public:
    epiJobWorker();
    epiJobWorker(const epiJobWorker&) = delete;
    epiJobWorker(epiJobWorker&&) = default;
    epiJobWorker& operator=(const epiJobWorker&) = delete;
    epiJobWorker& operator=(epiJobWorker&&) = default;
    ~epiJobWorker();

    void Cancel();
    epiBool IsCancelled() const;

    std::shared_ptr<epiJobHandle> Push(std::unique_ptr<epiIJob>&& job);

    epiBool HasJob() const;
    epiSize_t GetTotalJobsCount() const;
    epiSize_t GetPendingJobsCount() const;

    epiString ToString() const;

protected:
    void Run();

protected:
    std::thread m_Thread;
    std::vector<std::shared_ptr<epiJobHandle>> m_JobHandles;
    std::mutex m_JobHandlesMutex; // TODO: replace with lock-free queue
    std::condition_variable m_JobHandlesCondVar;
    std::atomic<epiBool> m_IsCancelled{false};
    std::atomic<epiBool> m_IsProcessingJob{false};
};

EPI_NAMESPACE_END()
