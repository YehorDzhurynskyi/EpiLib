#pragma once

#include "EpiGraphics/gfxDescriptorSet.h"

EPI_NAMESPACE_BEGIN()

class gfxDescriptorSet::Impl
{
public:
    static const gfxDescriptorSet::Impl* ExtractImpl(const gfxDescriptorSet& set) { return set.m_Impl.get(); }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;
};

EPI_NAMESPACE_END()
