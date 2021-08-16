#pragma once

#include "EpiGraphics/gfxImage.h"

EPI_NAMESPACE_BEGIN()

class gfxImage::Impl
{
public:
    static std::shared_ptr<gfxImage::Impl> ExtractImpl(const gfxImage& image) { return image.m_Impl; }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;
};

EPI_NAMESPACE_END()
