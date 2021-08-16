#pragma once

#include "EpiGraphics/gfxSampler.h"

EPI_NAMESPACE_BEGIN()

class gfxSampler::Impl
{
public:
    static std::shared_ptr<gfxSampler::Impl> ExtractImpl(const gfxSampler& sampler) { return sampler.m_Impl; }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;
};

EPI_NAMESPACE_END()
