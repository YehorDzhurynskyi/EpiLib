#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiCore/MT/JobSystem/epiIJob.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class epiIJob : public Object
{
EPI_GENREGION_BEGIN(epiIJob)

EPI_GENHIDDEN_epiIJob()

public:
    constexpr static epiMetaTypeID TypeID{0x12acc7c};

    enum epiIJob_PIDs
    {
        PID_IsCompleted = 0x85fc627e,
        PID_COUNT = 1
    };

protected:
    epiBool GetIsCompleted_Callback() const;

EPI_GENREGION_END(epiIJob)

public:
    void Complete();

protected:
    virtual void Execute() = 0;

protected:
    std::atomic<epiBool> m_IsCompleted{false};
};

EPI_NAMESPACE_END()
