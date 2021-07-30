#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Synchronization/gfxSemaphore.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphics/gfxEnum.h"

EPI_NAMESPACE_BEGIN()

class gfxSemaphoreCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxSemaphoreCreateInfo)

EPI_GENHIDDEN_gfxSemaphoreCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0xac56e7df};

    enum gfxSemaphoreCreateInfo_PIDs
    {
        PID_CreateMask = 0xc2e0d2f0,
        PID_COUNT = 1
    };

protected:
    gfxSemaphoreCreateMask m_CreateMask{};

EPI_GENREGION_END(gfxSemaphoreCreateInfo)
};

class gfxSemaphoreWaitInfo;
class gfxSemaphore : public Object
{
EPI_GENREGION_BEGIN(gfxSemaphore)

EPI_GENHIDDEN_gfxSemaphore()

public:
    constexpr static epiMetaTypeID TypeID{0xe4e7c5d4};

    enum gfxSemaphore_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxSemaphore)

public:
    class Impl;

public:
    gfxSemaphore() = default;
    explicit gfxSemaphore(const std::shared_ptr<Impl>& impl);

    epiBool HasImpl() const;

    epiBool Wait(const gfxSemaphoreWaitInfo& info, epiU64 timeout = std::numeric_limits<epiU64>::max());

protected:
    std::shared_ptr<Impl> m_Impl;
};

class gfxSemaphoreWaitInfo : public Object
{
EPI_GENREGION_BEGIN(gfxSemaphoreWaitInfo)

EPI_GENHIDDEN_gfxSemaphoreWaitInfo()

public:
    constexpr static epiMetaTypeID TypeID{0xb431b9e0};

    enum gfxSemaphoreWaitInfo_PIDs
    {
        PID_WaitMask = 0xcab0c968,
        PID_Semaphores = 0x86a4b6af,
        PID_Values = 0x3d0b49d0,
        PID_COUNT = 3
    };

protected:
    gfxSemaphoreWaitMask m_WaitMask{};
    epiArray<gfxSemaphore> m_Semaphores{};
    epiArray<epiU64> m_Values{};

EPI_GENREGION_END(gfxSemaphoreWaitInfo)
};

EPI_NAMESPACE_END()
