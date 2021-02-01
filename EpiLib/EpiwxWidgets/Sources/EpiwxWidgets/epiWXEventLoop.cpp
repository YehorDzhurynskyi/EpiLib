#include "EpiwxWidgets/epiWXEventLoop.h"

EPI_NAMESPACE_BEGIN()

epiWXEventLoop::epiWXEventLoop(epiEventLoopPeriodicalTask::Duration updatePeriod)
    : super(updatePeriod)
{
}

void epiWXEventLoop::Run()
{
    m_Timer.Bind(wxEVT_TIMER, &epiWXEventLoop::OnTimer, this, m_Timer.GetId());

    const epiU32 updatePeriod = std::chrono::duration_cast<std::chrono::milliseconds>(m_UpdatePeriod).count();
    m_Timer.Start(updatePeriod, wxTIMER_CONTINUOUS);
}

void epiWXEventLoop::OnTimer(wxTimerEvent& event)
{
    Update();
}

EPI_NAMESPACE_END()
