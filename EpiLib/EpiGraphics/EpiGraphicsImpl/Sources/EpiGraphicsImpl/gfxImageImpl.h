#pragma once

#include "EpiGraphics/gfxImage.h"
#include "EpiGraphics/gfxDevice.h"

EPI_NAMESPACE_BEGIN()

class gfxImage::Impl
{
public:
    static std::shared_ptr<gfxImage::Impl> ExtractImpl(const gfxImage& image) { return image.m_Impl; }

public:
    explicit Impl(const gfxDevice& device);
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    const gfxDevice& GetDevice() const;

protected:
    gfxDevice m_Device;
};

EPI_NAMESPACE_END()
