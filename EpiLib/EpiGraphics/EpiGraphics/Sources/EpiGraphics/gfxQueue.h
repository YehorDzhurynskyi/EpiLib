#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxQueue.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphics/gfxEnum.h"

EPI_NAMESPACE_BEGIN()

class gfxFence;
class gfxQueueSubmitInfo;
class gfxQueuePresentInfo;
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

    epiBool Present(const gfxQueuePresentInfo& info); // NOTE: this function is defined in gfxSwapChain.cpp because of cyclic including

    epiBool Wait();

    epiBool IsQueueTypeSupported(gfxQueueType mask) const;

protected:
    std::shared_ptr<Impl> m_Impl;
};

EPI_NAMESPACE_END()
