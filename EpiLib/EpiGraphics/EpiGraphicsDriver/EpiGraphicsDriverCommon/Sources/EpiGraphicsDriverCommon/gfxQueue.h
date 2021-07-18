#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxQueue.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxEnum.h"
#include "EpiGraphicsDriverCommon/gfxCommandBuffer.h"
#include "EpiGraphicsDriverCommon/Synchronization/gfxFence.h"
#include "EpiGraphicsDriverCommon/Synchronization/gfxSemaphore.h"

EPI_NAMESPACE_BEGIN()

class gfxQueueSubmitInfo : public Object
{
EPI_GENREGION_BEGIN(gfxQueueSubmitInfo)

EPI_GENHIDDEN_gfxQueueSubmitInfo()

public:
    constexpr static epiMetaTypeID TypeID{0x37aceed2};

    enum gfxQueueSubmitInfo_PIDs
    {
        PID_WaitSemaphores = 0xde36b270,
        PID_WaitDstStageMasks = 0x5c9921bb,
        PID_SignalSemaphores = 0xa8746c09,
        PID_CommandBuffers = 0xc25694f,
        PID_COUNT = 4
    };

protected:
    epiArray<gfxSemaphore> m_WaitSemaphores{};
    epiArray<gfxPipelineStage> m_WaitDstStageMasks{};
    epiArray<gfxSemaphore> m_SignalSemaphores{};
    epiArray<gfxCommandBuffer> m_CommandBuffers{};

EPI_GENREGION_END(gfxQueueSubmitInfo)
};

class gfxQueuePresentInfo : public Object
{
EPI_GENREGION_BEGIN(gfxQueuePresentInfo)

EPI_GENHIDDEN_gfxQueuePresentInfo()

public:
    constexpr static epiMetaTypeID TypeID{0xcfe3f532};

    enum gfxQueuePresentInfo_PIDs
    {
        PID_WaitSemaphores = 0xde36b270,
        PID_SwapChains = 0x322c907,
        PID_SwapChainImageIndices = 0x4d0af9fd,
        PID_COUNT = 3
    };

protected:
    epiArray<gfxSemaphore> m_WaitSemaphores{};
    epiArray<gfxSwapChain> m_SwapChains{};
    epiArray<epiU32> m_SwapChainImageIndices{};

EPI_GENREGION_END(gfxQueuePresentInfo)
};

class gfxQueue : public Object
{
EPI_GENREGION_BEGIN(gfxQueue)

EPI_GENHIDDEN_gfxQueue()

public:
    constexpr static epiMetaTypeID TypeID{0xc80527c2};

    enum gfxQueue_PIDs
    {
        PID_Type = 0x2cecf817,
        PID_Priority = 0x9bd0be71,
        PID_COUNT = 2
    };

protected:
    gfxQueueType GetType_Callback() const;
    epiFloat GetPriority_Callback() const;

EPI_GENREGION_END(gfxQueue)

public:
    class Impl;

public:
    gfxQueue() = default;
    explicit gfxQueue(const std::shared_ptr<Impl>& impl);

    epiBool HasImpl() const;

    epiBool Submit(const epiArray<gfxQueueSubmitInfo>& infos);
    epiBool Submit(const epiArray<gfxQueueSubmitInfo>& infos, const gfxFence& signalFence);
    epiBool Submit(const gfxQueueSubmitInfo& info);
    epiBool Submit(const gfxQueueSubmitInfo& info, const gfxFence& signalFence);

    epiBool Present(const gfxQueuePresentInfo& info);

    epiBool Wait();

    epiBool IsQueueTypeSupported(gfxQueueType mask) const;

protected:
    std::shared_ptr<Impl> m_Impl;
};

EPI_NAMESPACE_END()
