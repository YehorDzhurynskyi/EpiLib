EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxSwapChain.h"
#include "EpiGraphicsDriverCommon/gfxSwapChain.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxSwapChain::gfxSwapChain(const std::shared_ptr<internalgfx::gfxSwapChainImpl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxSwapChain::Present(const gfxQueue& queue)
{
    const auto queueImpl = queue.m_Impl;
    if (!queueImpl)
    {
        epiLogError("Failed to present SwapChain! Queue has no implementation!");
        return false;
    }

    return m_Impl->Present(*queueImpl);
}

EPI_NAMESPACE_END()
