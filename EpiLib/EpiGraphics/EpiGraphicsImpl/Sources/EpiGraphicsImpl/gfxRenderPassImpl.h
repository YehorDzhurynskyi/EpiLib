#pragma once

#include "EpiGraphics/gfxRenderPass.h"

EPI_NAMESPACE_BEGIN()

class gfxRenderPass::Impl
{
public:
    static const gfxRenderPass::Impl* ExtractImpl(const gfxRenderPass& renderPass) { return renderPass.m_Impl.get(); }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;
};

EPI_NAMESPACE_END()
