#pragma once

#include "EpiGraphicsImpl/gfxDeviceMemoryAllocatorImpl.h"

struct VkDevice_T;
struct VkDeviceMemory_T;

EPI_NAMESPACE_BEGIN()

class gfxDeviceMemoryAllocatorImplVK : public gfxDeviceMemoryAllocator::Impl
{
public:
    explicit gfxDeviceMemoryAllocatorImplVK(VkDevice_T* device);
    gfxDeviceMemoryAllocatorImplVK(const gfxDeviceMemoryAllocatorImplVK& rhs) = delete;
    gfxDeviceMemoryAllocatorImplVK& operator=(const gfxDeviceMemoryAllocatorImplVK& rhs) = delete;
    gfxDeviceMemoryAllocatorImplVK(gfxDeviceMemoryAllocatorImplVK&& rhs) = default;
    gfxDeviceMemoryAllocatorImplVK& operator=(gfxDeviceMemoryAllocatorImplVK&& rhs) = default;
    ~gfxDeviceMemoryAllocatorImplVK() override;

    epiBool Init(const gfxDeviceMemoryAllocatorCreateInfo& info, const gfxPhysicalDeviceImplVK& physicalDeviceImpl);
};

EPI_NAMESPACE_END()
