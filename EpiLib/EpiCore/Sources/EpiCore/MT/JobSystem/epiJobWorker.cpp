#include "EpiCore/MT/JobSystem/epiJobWorker.h"

EPI_NAMESPACE_BEGIN()

epiJobWorker::epiJobWorker()
{
    m_Thread = std::thread(&epiJobWorker::Run, this);
}

epiJobWorker::~epiJobWorker()
{
    m_Thread.join();
}

void epiJobWorker::Cancel()
{
    m_IsCancelled.store(true);
    m_JobHandlesCondVar.notify_one();
}

epiBool epiJobWorker::IsCancelled() const
{
    return m_IsCancelled.load();
}

void epiJobWorker::Run()
{
#ifdef EPI_BUILD_PROFILE
    std::string threadName;

    {
        std::stringstream ss;
        ss << "Worker: " << m_Thread.get_id();

        threadName = std::move(ss.str());
    }

    epiProfileThread(threadName.c_str());
#endif

    while (!IsCancelled())
    {
        std::shared_ptr<epiJobHandle> handle;

        {
            std::unique_lock<std::mutex> lk(m_JobHandlesMutex);
            m_JobHandlesCondVar.wait(lk, [this]() { return IsCancelled() || !m_JobHandles.empty(); });

            if (!m_JobHandles.empty() && !IsCancelled())
            {
                m_IsProcessingJob.store(true);
            }

            handle = std::move(m_JobHandles.back());
            m_JobHandles.pop_back();
        }

        if (IsCancelled())
        {
            break;
        }

        epiLogTrace(ToString() + ": Processing job `" + handle->ToString() + "`...");

        handle->Complete();

        m_IsProcessingJob.store(false);
        epiLogTrace(ToString() + ": Job processing has finished `" + handle->ToString() + "`");
    }
}

std::shared_ptr<epiJobHandle> epiJobWorker::Push(std::unique_ptr<epiIJob>&& job)
{
    epiProfileFunction;

    std::shared_ptr<epiJobHandle> handle = std::make_shared<epiJobHandle>(std::move(job));

    {
        std::lock_guard<std::mutex> lk(m_JobHandlesMutex);
        m_JobHandles.push_back(handle);
    }

    m_JobHandlesCondVar.notify_one();

    return handle;
}

epiBool epiJobWorker::HasJob() const
{
    return !m_JobHandles.empty() || m_IsProcessingJob.load();
}

epiSize_t epiJobWorker::GetTotalJobsCount() const
{
    return GetPendingJobsCount() + m_IsProcessingJob.load() ? 1 : 0;
}

epiSize_t epiJobWorker::GetPendingJobsCount() const
{
    return m_JobHandles.size();
}

epiString epiJobWorker::ToString() const
{
    std::ostringstream ss;

    ss << "epiJobWorker[" << m_Thread.get_id() << "]";

    return ss.str();
}

EPI_NAMESPACE_END()
