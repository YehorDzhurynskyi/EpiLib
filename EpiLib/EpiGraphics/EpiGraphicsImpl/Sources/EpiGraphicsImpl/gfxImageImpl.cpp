#include "EpiGraphicsImpl/gfxImageImpl.h"

EPI_NAMESPACE_BEGIN()

gfxImage::Impl::Impl(const gfxDevice& device)
    : m_Device{device}
{
}

const gfxDevice& gfxImage::Impl::GetDevice() const
{
    return m_Device;
}

EPI_NAMESPACE_END()
