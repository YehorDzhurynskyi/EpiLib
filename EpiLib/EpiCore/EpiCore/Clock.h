#pragma once

namespace epi
{

class Clock
{
public:
    Clock();

    void Start();
    void Tick();

    void SetIsPaused(epiBool pause);
    epiBool GetIsPaused() const;

    epiFloat GetDT() const;
    epiFloat GetElapsedTime() const;
    epiFloat& GetElapsedTime();
    void SetTimeSpeedModifier(epiFloat modifier);
    epiFloat GetTimeSpeedModifier() const;

    epiU32 GetStepNumber() const;

protected:
    epiBool m_IsPaused;

    epiU64 m_Frequency;
    epiU64 m_LastPerfCounter;

    epiFloat m_DT;
    epiFloat m_ElapsedTime;
    epiFloat m_TimeSpeedModifier;

    epiU32 m_StepNumber;
};

}
