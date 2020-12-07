#pragma once

#include "EpiCore/MT/JobSystem/epiJobWorker.h"

#include <deque>

EPI_NAMESPACE_BEGIN()

class epiJobScheduler
{
public:
    static epiJobScheduler& GetInstance()
    {
        static epiJobScheduler instance;
        return instance;
    }

public:
    ~epiJobScheduler();

    [[nodiscard]] std::shared_ptr<epiJobHandle> Schedule(std::unique_ptr<epiIJob>&& job);

protected:
    epiJobScheduler();

protected:
    std::deque<epiJobWorker> m_Workers;
};

EPI_NAMESPACE_END()
