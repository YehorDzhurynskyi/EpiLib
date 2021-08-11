#pragma once

#include "EpiGraphics/gfxImageView.h"

EPI_NAMESPACE_BEGIN()

class gfxImageView::Impl
{
public:
    static const gfxImageView::Impl* ExtractImpl(const gfxImageView& imageView) { return imageView.m_Impl.get(); }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;
};

EPI_NAMESPACE_END()
