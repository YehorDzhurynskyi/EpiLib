#pragma once

#include "EpiGraphics/gfxQueue.h"

EPI_NAMESPACE_BEGIN()

class gfxQueue::Impl
{
public:
    static const gfxQueue::Impl* ExtractImpl(const gfxQueue& queue) { return queue.m_Impl.get(); }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    virtual epiBool Submit(const epiArray<gfxQueueSubmitInfo>& infos) = 0;
    virtual epiBool Submit(const epiArray<gfxQueueSubmitInfo>& infos, const gfxFence& signalFence) = 0;

    virtual epiBool Present(const gfxQueuePresentInfo& info) = 0;

    virtual epiBool Wait() = 0;

    virtual gfxQueueType GetType() const = 0;
    virtual epiFloat GetPriority() const = 0;
    virtual epiBool IsQueueTypeSupported(gfxQueueType mask) const = 0;
};

EPI_NAMESPACE_END()
