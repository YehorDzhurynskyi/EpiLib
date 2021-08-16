#pragma once

#include "EpiGraphics/gfxPipelineLayout.h"

EPI_NAMESPACE_BEGIN()

class gfxPipelineLayout::Impl
{
public:
    static std::shared_ptr<gfxPipelineLayout::Impl> ExtractImpl(const gfxPipelineLayout& layout) { return layout.m_Impl; }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;
};

EPI_NAMESPACE_END()
