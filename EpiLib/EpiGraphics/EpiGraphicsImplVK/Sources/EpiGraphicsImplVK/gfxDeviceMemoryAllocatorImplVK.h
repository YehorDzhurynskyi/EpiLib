#pragma once

#include "EpiGraphicsImpl/gfxDeviceMemoryAllocatorImpl.h"

struct VmaAllocator_T;
struct VmaAllocation_T;

EPI_NAMESPACE_BEGIN()

class gfxDeviceMemoryAllocationImplVK : public gfxDeviceMemoryAllocation::Impl
{
public:
    explicit gfxDeviceMemoryAllocationImplVK(const gfxDeviceMemoryAllocator& allocator);
    gfxDeviceMemoryAllocationImplVK(const gfxDeviceMemoryAllocationImplVK& rhs) = delete;
    gfxDeviceMemoryAllocationImplVK& operator=(const gfxDeviceMemoryAllocationImplVK& rhs) = delete;
    gfxDeviceMemoryAllocationImplVK(gfxDeviceMemoryAllocationImplVK&& rhs) = default;
    gfxDeviceMemoryAllocationImplVK& operator=(gfxDeviceMemoryAllocationImplVK&& rhs) = default;
    ~gfxDeviceMemoryAllocationImplVK() override;

    std::optional<gfxBuffer> InitBuffer(const gfxDeviceMemoryAllocationCreateInfo& info,
                                        const gfxBufferCreateInfo& bufferInfo);

    std::optional<gfxImage> InitImage(const gfxDeviceMemoryAllocationCreateInfo& info,
                                      const gfxImageCreateInfo& imageInfo);

    epiBool InitBufferAllocated(const gfxDeviceMemoryAllocationCreateInfo& info,
                                const gfxBuffer& buffer);

    epiBool InitImageAllocated(const gfxDeviceMemoryAllocationCreateInfo& info,
                               const gfxImage& image);

    epiBool IsPropertyEnabled(gfxDeviceMemoryPropertyMask mask) const override;

    epiBool BindBuffer(const gfxBuffer& buffer) override;
    epiBool BindImage(const gfxImage& image) override;

    epiBool IsMapped() const override;
    epiByte* Mapped() override;

    void Map() override;
    void Unmap() override;

    epiBool Invalidate(epiSize_t offset, epiSize_t size) override;
    epiBool Flush(epiSize_t offset, epiSize_t size) override;

protected:
    VmaAllocation_T* m_VmaAllocation{nullptr};
};

class gfxDeviceMemoryAllocatorImplVK : public gfxDeviceMemoryAllocator::Impl
{
public:
    explicit gfxDeviceMemoryAllocatorImplVK(const gfxDevice& device);
    gfxDeviceMemoryAllocatorImplVK(const gfxDeviceMemoryAllocatorImplVK& rhs) = delete;
    gfxDeviceMemoryAllocatorImplVK& operator=(const gfxDeviceMemoryAllocatorImplVK& rhs) = delete;
    gfxDeviceMemoryAllocatorImplVK(gfxDeviceMemoryAllocatorImplVK&& rhs) = default;
    gfxDeviceMemoryAllocatorImplVK& operator=(gfxDeviceMemoryAllocatorImplVK&& rhs) = default;
    ~gfxDeviceMemoryAllocatorImplVK() override;

    epiBool Init(const gfxDeviceMemoryAllocatorCreateInfo& info);

    std::optional<gfxDeviceMemoryAllocationBuffer> CreateBuffer(const gfxDeviceMemoryAllocationCreateInfo& allocationInfo,
                                                                const gfxBufferCreateInfo& bufferInfo) override;

    std::optional<gfxDeviceMemoryAllocationImage> CreateImage(const gfxDeviceMemoryAllocationCreateInfo& allocationInfo,
                                                              const gfxImageCreateInfo& imageInfo) override;

    std::optional<gfxDeviceMemoryAllocation> AllocateBuffer(const gfxDeviceMemoryAllocationCreateInfo& info,
                                                            const gfxBuffer& buffer) override;

    std::optional<gfxDeviceMemoryAllocation> AllocateImage(const gfxDeviceMemoryAllocationCreateInfo& info,
                                                           const gfxImage& image) override;

    void SetCurrentFrameIndex(epiU32 value) override;

    std::optional<gfxDeviceMemoryAllocatorBudget> QueryBudget() const override;
    std::optional<gfxDeviceMemoryAllocatorStats> QueryStats() const override;

    VmaAllocator_T* GetVmaAllocator() const;

protected:
    VmaAllocator_T* m_VmaAllocator{nullptr};
};

EPI_NAMESPACE_END()
