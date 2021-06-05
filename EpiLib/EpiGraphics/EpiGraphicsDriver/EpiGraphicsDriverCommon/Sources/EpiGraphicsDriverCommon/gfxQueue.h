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

namespace internalgfx
{

class gfxQueueImpl;

} // internalgfx

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
    friend class gfxSwapChain;
    friend class internalgfx::gfxQueueImpl;

public:
    gfxQueue() = default;
    explicit gfxQueue(const std::shared_ptr<internalgfx::gfxQueueImpl>& impl);

    epiBool Submit(const epiArray<gfxQueueSubmitInfo>& infos);
    epiBool Submit(const epiArray<gfxQueueSubmitInfo>& infos, const gfxFence& signalFence);
    epiBool Submit(const gfxQueueSubmitInfo& info);
    epiBool Submit(const gfxQueueSubmitInfo& info, const gfxFence& signalFence);
    epiBool Wait();

    epiBool IsQueueTypeSupported(gfxQueueType mask) const;

protected:
    epiPimpl<internalgfx::gfxQueueImpl> m_Impl;
};

EPI_NAMESPACE_END()
