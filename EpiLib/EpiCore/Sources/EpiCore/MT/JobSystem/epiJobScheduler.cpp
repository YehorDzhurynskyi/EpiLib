#include "EpiCore/MT/JobSystem/epiJobScheduler.h"

#include "EpiCore/Platform/epiPlatform.h"

EPI_NAMESPACE_BEGIN()

epiJobScheduler::epiJobScheduler()
{
    if (const epiDeviceCPUBase* cpu = epiPlatform::GetInstance().GetDeviceCPU())
    {
        const epiSize_t nOfWorkers = std::max(1ull, cpu->GetNumberOfLogicalThreads() - 1);
        m_Workers.resize(nOfWorkers);
    }
    else
    {
        epiLogFatal("Couldn't retrieve the number of CPUs logical threads!");
    }
}

epiJobScheduler::~epiJobScheduler()
{
    for (auto& worker : m_Workers)
    {
        worker.Cancel();
    }
}

std::shared_ptr<epiJobHandle> epiJobScheduler::Schedule(std::unique_ptr<epiIJob>&& job)
{
    epiProfileFunction;

    std::shared_ptr<epiJobHandle> handle;

    epiJobWorker* bestMatchWorker = nullptr;
    epiProfileBlock("Loop");
    for (auto& worker : m_Workers)
    {
        epiProfileBlock("Iteration");

        epiAssert(!worker.IsCancelled());

        if (!worker.HasJob())
        {
            bestMatchWorker = &worker;
            break;
        }
        else if (bestMatchWorker == nullptr)
        {
            bestMatchWorker = &worker;
        }

        bestMatchWorker = worker.GetTotalJobsCount() < bestMatchWorker->GetTotalJobsCount() ? &worker : bestMatchWorker;
    }
    epiProfileBlockEnd;

    epiProfileBlock("Assignment");
    if (bestMatchWorker != nullptr)
    {
        epiProfileBlock("Log");
        epiLogTrace(bestMatchWorker->ToString() + ": Scheduling job `" + job->ToString() + "`");
        epiProfileBlockEnd;

        handle = bestMatchWorker->Push(std::move(job));
    }
    else
    {
        epiLogFatal("Couldn't schedule job! The best match worker hasn't found!");
    }

    return handle;
}

EPI_NAMESPACE_END()
