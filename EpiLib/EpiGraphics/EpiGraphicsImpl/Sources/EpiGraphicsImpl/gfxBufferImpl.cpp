#include "EpiGraphicsImpl/gfxBufferImpl.h"

EPI_NAMESPACE_BEGIN()

gfxBuffer::Impl::Impl(const gfxDevice& device)
    : m_Device{device}
{
}

const gfxDevice& gfxBuffer::Impl::GetDevice() const
{
    return m_Device;
}

EPI_NAMESPACE_END()
