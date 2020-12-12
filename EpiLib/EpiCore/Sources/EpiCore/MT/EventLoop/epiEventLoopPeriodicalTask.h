#pragma once

EPI_NAMESPACE_BEGIN()

class epiEventLoopPeriodicalTask
{
public:
    using Task = std::function<epiBool(void)>;
    using Clock = std::chrono::steady_clock;
    using TimePoint = Clock::time_point;
    using Duration = Clock::duration;

public:
    epiEventLoopPeriodicalTask(Task&& task, Duration period);

    epiBool IsReady() const;
    epiBool IsCancelled() const;

    void Cancel();

    void Execute();

protected:
    Task m_Task;
    Duration m_Period;
    TimePoint m_LastProcessingTime{};
    std::atomic<epiBool> m_IsCancelled{false};
};

EPI_NAMESPACE_END()
