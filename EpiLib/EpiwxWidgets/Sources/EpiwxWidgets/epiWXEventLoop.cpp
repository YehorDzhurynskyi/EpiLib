#include "EpiwxWidgets/epiWXEventLoop.h"


EPI_NAMESPACE_BEGIN()

void epiWXEventLoop::Run()
{
    m_Timer.Bind(wxEVT_TIMER, &epiWXEventLoop::OnTimer, this, m_Timer.GetId());
    m_Timer.Start(30, wxTIMER_CONTINUOUS);
}

void epiWXEventLoop::OnTimer(wxTimerEvent& event)
{
    Update();
}

EPI_NAMESPACE_END()
