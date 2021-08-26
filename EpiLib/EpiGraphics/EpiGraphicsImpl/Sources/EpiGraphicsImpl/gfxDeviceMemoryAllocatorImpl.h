#pragma once

#include "EpiGraphics/gfxDeviceMemoryAllocator.h"

#include "EpiGraphics/gfxDevice.h"

EPI_NAMESPACE_BEGIN()

class gfxDeviceMemoryAllocation::Impl
{
public:
    explicit Impl(const gfxDeviceMemoryAllocator& allocator);
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    virtual epiBool IsPropertyEnabled(gfxDeviceMemoryPropertyMask mask) const = 0;

    virtual epiBool BindBuffer(const gfxBuffer& buffer) = 0;
    virtual epiBool BindImage(const gfxImage& image) = 0;

    virtual epiBool IsMapped() const = 0;
    virtual epiByte* Mapped() = 0;

    virtual void Map() = 0;
    virtual void Unmap() = 0;

    virtual epiBool Invalidate(epiSize_t offset, epiSize_t size) = 0;
    virtual epiBool Flush(epiSize_t offset, epiSize_t size) = 0;

    const gfxDeviceMemoryAllocator& GetAllocator() const;

protected:
    gfxDeviceMemoryAllocator m_Allocator;
};

class gfxDeviceMemoryAllocator::Impl : public std::enable_shared_from_this<gfxDeviceMemoryAllocator::Impl>
{
public:
    static std::shared_ptr<gfxDeviceMemoryAllocator::Impl> ExtractImpl(const gfxDeviceMemoryAllocator& allocator) { return allocator.m_Impl; }

public:
    explicit Impl(const gfxDevice& device);
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    virtual std::optional<gfxDeviceMemoryAllocationBuffer> CreateBuffer(const gfxDeviceMemoryAllocationCreateInfo& allocationInfo,
                                                                        const gfxBufferCreateInfo& bufferInfo) = 0;

    virtual std::optional<gfxDeviceMemoryAllocationImage> CreateImage(const gfxDeviceMemoryAllocationCreateInfo& allocationInfo,
                                                                      const gfxImageCreateInfo& imageInfo) = 0;

    virtual std::optional<gfxDeviceMemoryAllocation> AllocateBuffer(const gfxDeviceMemoryAllocationCreateInfo& info,
                                                                    const gfxBuffer& buffer) = 0;

    virtual std::optional<gfxDeviceMemoryAllocation> AllocateImage(const gfxDeviceMemoryAllocationCreateInfo& info,
                                                                   const gfxImage& image) = 0;

    const gfxDevice& GetDevice() const;

protected:
    gfxDevice m_Device;
};

EPI_NAMESPACE_END()
