#include "EpiGraphicsImpl/gfxDeviceMemoryAllocatorImpl.h"

EPI_NAMESPACE_BEGIN()

gfxDeviceMemoryAllocator::Impl::Impl(const gfxDevice& device)
    : m_Device{device}
{
}

const gfxDevice& gfxDeviceMemoryAllocator::Impl::GetDevice() const
{
    return m_Device;
}

EPI_NAMESPACE_END()
