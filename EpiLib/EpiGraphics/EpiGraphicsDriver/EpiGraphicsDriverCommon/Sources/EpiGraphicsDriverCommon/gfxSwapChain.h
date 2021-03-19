#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxSwapChain.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxSwapChainImpl;

} // internalgfx

class gfxSwapChain : public Object
{
EPI_GENREGION_BEGIN(gfxSwapChain)

EPI_GENHIDDEN_gfxSwapChain()

public:
    constexpr static epiMetaTypeID TypeID{0x7a8b586};

    enum gfxSwapChain_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxSwapChain)

public:
    gfxSwapChain() = default;
    gfxSwapChain(internalgfx::gfxSwapChainImpl* impl);
    gfxSwapChain(const gfxSwapChain& rhs) = delete;
    gfxSwapChain& operator=(const gfxSwapChain& rhs) = delete;
    gfxSwapChain(gfxSwapChain&& rhs);
    gfxSwapChain& operator=(gfxSwapChain&& rhs);
    ~gfxSwapChain();

protected:
    internalgfx::gfxSwapChainImpl* m_Impl{nullptr};
};

EPI_NAMESPACE_END()
