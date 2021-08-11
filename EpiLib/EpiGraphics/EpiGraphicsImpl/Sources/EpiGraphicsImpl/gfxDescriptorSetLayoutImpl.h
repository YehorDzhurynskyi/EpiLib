#pragma once

#include "EpiGraphics/gfxDescriptorSetLayout.h"

EPI_NAMESPACE_BEGIN()

class gfxDescriptorSetLayout::Impl
{
public:
    static const gfxDescriptorSetLayout::Impl* ExtractImpl(const gfxDescriptorSetLayout& layout) { return layout.m_Impl.get(); }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;
};

EPI_NAMESPACE_END()
