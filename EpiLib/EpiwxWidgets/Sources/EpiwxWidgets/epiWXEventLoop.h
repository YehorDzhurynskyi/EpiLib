#pragma once

#include "EpiCore/MT/EventLoop/epiEventLoop.h"

#include <wx/event.h>
#include <wx/timer.h>

EPI_NAMESPACE_BEGIN()

class epiWXEventLoop : public epiEventLoop
{
public:
    void Run() override;

protected:
    void OnTimer(wxTimerEvent& event);

protected:
    wxTimer m_Timer;
};

EPI_NAMESPACE_END()
