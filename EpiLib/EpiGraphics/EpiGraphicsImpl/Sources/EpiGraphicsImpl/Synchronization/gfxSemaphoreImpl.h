#pragma once

#include "EpiGraphics/Synchronization/gfxSemaphore.h"

EPI_NAMESPACE_BEGIN()

class gfxSemaphore::Impl
{
public:
    static const gfxSemaphore::Impl* ExtractImpl(const gfxSemaphore& semaphore) { return semaphore.m_Impl.get(); }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    virtual epiBool Wait(const gfxSemaphoreWaitInfo& info, epiU64 timeout) = 0;
};

EPI_NAMESPACE_END()
