#pragma once

#include "EpiGraphics/gfxDescriptorSet.h"

EPI_NAMESPACE_BEGIN()

class gfxDescriptorSet::Impl
{
public:
    static std::shared_ptr<gfxDescriptorSet::Impl> ExtractImpl(const gfxDescriptorSet& set) { return set.m_Impl; }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;
};

EPI_NAMESPACE_END()
