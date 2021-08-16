#pragma once

#include "EpiGraphics/Synchronization/gfxFence.h"

EPI_NAMESPACE_BEGIN()

class gfxFence::Impl
{
public:
    static std::shared_ptr<gfxFence::Impl> ExtractImpl(const gfxFence& fence) { return fence.m_Impl; }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    virtual epiBool Reset() = 0;
    virtual epiBool Wait(epiU64 timeout) = 0;
};

EPI_NAMESPACE_END()
