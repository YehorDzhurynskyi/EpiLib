#pragma once

#include "EpiCore/MT/EventLoop/epiEventLoopPeriodicalTask.h"

EPI_NAMESPACE_BEGIN()

class epiEventLoop
{
public:
    epiEventLoop() = default;
    epiEventLoop(const epiEventLoop&) = delete;
    epiEventLoop(epiEventLoop&&) = default;
    epiEventLoop& operator=(const epiEventLoop&) = delete;
    epiEventLoop& operator=(epiEventLoop&&) = default;
    virtual ~epiEventLoop() = default;

public:
    static void SetMainEventLoop(std::unique_ptr<epiEventLoop>&& eventLoop);
    static epiEventLoop* GetMainEventLoop();

    virtual void Run() = 0;

    epiEventLoopPeriodicalTask& AddPeriodicalTask(epiEventLoopPeriodicalTask::Task&& task, epiEventLoopPeriodicalTask::Duration period);

protected:
    void Update();

protected:
    static std::unique_ptr<epiEventLoop> ms_MainEventLoop;

    // TODO: replace with a lock-free list
    std::list<epiEventLoopPeriodicalTask> m_Tasks;
};

EPI_NAMESPACE_END()
