#include "EpiGraphicsImpl/gfxDeviceMemoryAllocatorImpl.h"

EPI_NAMESPACE_BEGIN()

gfxDeviceMemoryAllocation::Impl::Impl(const gfxDeviceMemoryAllocator& allocator)
    : m_Allocator{allocator}
{
}

const gfxDeviceMemoryAllocator& gfxDeviceMemoryAllocation::Impl::GetAllocator() const
{
    return m_Allocator;
}

gfxDeviceMemoryAllocator::Impl::Impl(const gfxDevice& device)
    : m_Device{device}
{
}

const gfxDevice& gfxDeviceMemoryAllocator::Impl::GetDevice() const
{
    return m_Device;
}

EPI_NAMESPACE_END()
