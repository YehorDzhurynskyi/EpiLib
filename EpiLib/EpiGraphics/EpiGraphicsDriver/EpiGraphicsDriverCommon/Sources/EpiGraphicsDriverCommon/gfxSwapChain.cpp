EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxSwapChain.h"
#include "EpiGraphicsDriverCommon/gfxSwapChain.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxSwapChain::gfxSwapChain(internalgfx::gfxSwapChainImpl* impl)
    : m_Impl{impl}
{
}

gfxSwapChain::gfxSwapChain(gfxSwapChain&& rhs)
{
    if (this != &rhs) // TODO: add this check to every move ctor/operator
    {
        m_Impl = rhs.m_Impl;
        rhs.m_Impl = nullptr;
    }
}

gfxSwapChain& gfxSwapChain::operator=(gfxSwapChain&& rhs)
{
    if (this != &rhs)
    {
        m_Impl = rhs.m_Impl;
        rhs.m_Impl = nullptr;
    }

    return *this;
}

gfxSwapChain::~gfxSwapChain()
{
    delete m_Impl;
}

epiBool gfxSwapChain::Present(const gfxQueue& queue)
{
    const internalgfx::gfxQueueImpl* queueImpl = queue.m_Impl;
    if (queueImpl == nullptr)
    {
        epiLogError("Failed to present SwapChain! Queue has no implementation!");
        return false;
    }

    return m_Impl->Present(*queueImpl);
}

EPI_NAMESPACE_END()
