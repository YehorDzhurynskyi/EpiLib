#include "EpiGraphicsImpl/gfxSwapChainImpl.h"

EPI_NAMESPACE_BEGIN()

gfxSwapChain::Impl::Impl(const gfxDevice& device)
    : m_Device{device}
{
}

const gfxDevice& gfxSwapChain::Impl::GetDevice() const
{
    return m_Device;
}

EPI_NAMESPACE_END()
