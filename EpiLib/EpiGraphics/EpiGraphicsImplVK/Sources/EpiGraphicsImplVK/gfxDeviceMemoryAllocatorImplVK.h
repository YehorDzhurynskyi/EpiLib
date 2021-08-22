#pragma once

#include "EpiGraphicsImpl/gfxDeviceMemoryAllocatorImpl.h"

struct VmaAllocator_T;

EPI_NAMESPACE_BEGIN()

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

protected:
    VmaAllocator_T* m_VmaAllocator{nullptr};
};

EPI_NAMESPACE_END()
