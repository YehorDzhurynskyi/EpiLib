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
    m_Impl = rhs.m_Impl;

    rhs.m_Impl = nullptr;
}

gfxSwapChain& gfxSwapChain::operator=(gfxSwapChain&& rhs)
{
    m_Impl = rhs.m_Impl;

    rhs.m_Impl = nullptr;

    return *this;
}

gfxSwapChain::~gfxSwapChain()
{
    delete m_Impl;
}

EPI_NAMESPACE_END()
