#include "EpiCore/MT/EventLoop/epiEventLoop.h"

EPI_NAMESPACE_BEGIN()

std::unique_ptr<epiEventLoop> epiEventLoop::ms_MainEventLoop;

void epiEventLoop::SetMainEventLoop(std::unique_ptr<epiEventLoop>&& eventLoop)
{
    ms_MainEventLoop = std::move(eventLoop);
}

epiEventLoop* epiEventLoop::GetMainEventLoop()
{
    return ms_MainEventLoop.get();
}

epiEventLoopPeriodicalTask& epiEventLoop::AddPeriodicalTask(epiEventLoopPeriodicalTask::Task&& task, epiEventLoopPeriodicalTask::Duration period)
{
    // TODO: should be a main thread, add `epiAssert`

    return m_Tasks.emplace_back(std::move(task), period);
}

void epiEventLoop::Update()
{
    for (auto& task : m_Tasks)
    {
        if (!task.IsCancelled() && task.IsReady())
        {
            task.Execute();
        }
    }

    m_Tasks.remove_if([](const epiEventLoopPeriodicalTask& task)
    {
        return task.IsCancelled();
    });
}

EPI_NAMESPACE_END()
