#pragma once

#include "EpiGraphics/gfxBuffer.h"

EPI_NAMESPACE_BEGIN()

class gfxBuffer::Impl
{
public:
    static const gfxBuffer::Impl* ExtractImpl(const gfxBuffer& buffer) { return buffer.m_Impl.get(); }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;
};

EPI_NAMESPACE_END()
