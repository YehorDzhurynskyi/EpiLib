#include "EpiCore/pch.h"
#include "Clock.h"
#include <Windows.h>

namespace epi
{

Clock::Clock()
    : m_IsPaused(true)
    , m_Frequency(0)
    , m_LastPerfCounter(0)
    , m_DT(0.0f)
    , m_ElapsedTime(0.0f)
    , m_TimeSpeedModifier(1.0f)
    , m_StepNumber(0)
{
    QueryPerformanceFrequency((LARGE_INTEGER*)&m_Frequency);
}

void Clock::Start()
{
    SetIsPaused(false);
}

void Clock::Tick()
{
    if (GetIsPaused())
    {
        return;
    }

    ++m_StepNumber;

    epiU64 now;
    QueryPerformanceCounter((LARGE_INTEGER*)&now);
    m_DT = m_TimeSpeedModifier * ((now - m_LastPerfCounter) / (epiFloat)m_Frequency);
    m_LastPerfCounter = now;

    m_ElapsedTime += m_DT;
}

void Clock::SetIsPaused(epiBool pause)
{
    if (!pause)
    {
        QueryPerformanceCounter((LARGE_INTEGER*)&m_LastPerfCounter);
    }

    m_IsPaused = pause;
}

epiBool Clock::GetIsPaused() const
{
    return m_IsPaused;
}

epiFloat Clock::GetDT() const
{
    return m_DT;
}

epiFloat Clock::GetElapsedTime() const
{
    return m_ElapsedTime;
}

epiFloat& Clock::GetElapsedTime()
{
    return m_ElapsedTime;
}

void Clock::SetTimeSpeedModifier(epiFloat modifier)
{
    assert(m_TimeSpeedModifier > 0.0f);
    m_TimeSpeedModifier = modifier;
}

epiFloat Clock::GetTimeSpeedModifier() const
{
    return m_TimeSpeedModifier;
}

epiU32 Clock::GetStepNumber() const
{
    return m_StepNumber;
}

}
