#include "EpiCore/MT/EventLoop/epiEventLoopPeriodicalTask.h"

EPI_NAMESPACE_BEGIN()

epiEventLoopPeriodicalTask::epiEventLoopPeriodicalTask(Task&& task, Duration period)
    : m_Task{std::move(task)}
    , m_Period{period}
{
}

epiBool epiEventLoopPeriodicalTask::IsReady() const
{
    return Clock::now() - m_LastProcessingTime > m_Period;
}

epiBool epiEventLoopPeriodicalTask::IsCancelled() const
{
    return m_IsCancelled.load();
}

void epiEventLoopPeriodicalTask::Cancel()
{
    m_IsCancelled.store(true);
}

void epiEventLoopPeriodicalTask::Execute()
{
    epiProfileFunction;

    epiAssert(IsReady());

    m_LastProcessingTime = Clock::now();
    const epiBool keepAlive = m_Task();
    if (!keepAlive)
    {
        Cancel();
    }
}

EPI_NAMESPACE_END()
