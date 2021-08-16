#pragma once

#include "EpiGraphics/gfxFrameBuffer.h"

EPI_NAMESPACE_BEGIN()

class gfxFrameBuffer::Impl
{
public:
    static std::shared_ptr<gfxFrameBuffer::Impl> ExtractImpl(const gfxFrameBuffer& frameBuffer) { return frameBuffer.m_Impl; }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;
};

EPI_NAMESPACE_END()
