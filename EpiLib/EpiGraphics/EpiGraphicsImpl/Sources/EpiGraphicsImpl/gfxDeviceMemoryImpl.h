#pragma once

#include "EpiGraphics/gfxDeviceMemory.h"

EPI_NAMESPACE_BEGIN()

class gfxDeviceMemory::Impl
{
public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    virtual epiBool IsPropertyEnabled(gfxDeviceMemoryPropertyMask mask) const = 0;

    virtual epiBool BindBuffer(const gfxBindBufferMemoryInfo& info) = 0;
    virtual epiBool BindImage(const gfxBindImageMemoryInfo& info) = 0;

    virtual epiByte* Map(epiSize_t size, epiSize_t offset) = 0;
    virtual void Unmap() = 0;
};

EPI_NAMESPACE_END()
