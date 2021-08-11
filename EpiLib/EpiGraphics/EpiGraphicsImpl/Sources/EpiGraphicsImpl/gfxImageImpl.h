#pragma once

#include "EpiGraphics/gfxImage.h"

EPI_NAMESPACE_BEGIN()

class gfxImage::Impl
{
public:
    static const gfxImage::Impl* ExtractImpl(const gfxImage& image) { return image.m_Impl.get(); }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;
};

EPI_NAMESPACE_END()
