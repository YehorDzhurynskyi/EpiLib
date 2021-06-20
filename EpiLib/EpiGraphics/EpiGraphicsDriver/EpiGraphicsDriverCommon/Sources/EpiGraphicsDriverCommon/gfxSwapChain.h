#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxSwapChain.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxSurface.h"
#include "EpiGraphicsDriverCommon/gfxQueueFamily.h"
#include "EpiGraphicsDriverCommon/gfxRenderPass.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxSwapChainImpl;

} // internalgfx

class gfxSwapChainCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxSwapChainCreateInfo)

EPI_GENHIDDEN_gfxSwapChainCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0x23e11eb4};

    enum gfxSwapChainCreateInfo_PIDs
    {
        PID_Surface = 0x73fca7f2,
        PID_RenderPass = 0x662aa9d7,
        PID_QueueFamily = 0xfa954047,
        PID_Capabilities = 0x50af605,
        PID_Format = 0xd91677e9,
        PID_PresentMode = 0x2430171b,
        PID_Extent = 0x21a25c7e,
        PID_COUNT = 7
    };

protected:
    gfxSurface m_Surface{};
    gfxRenderPass m_RenderPass{};
    gfxQueueFamily m_QueueFamily{};
    gfxSurfaceCapabilities m_Capabilities{};
    gfxSurfaceFormat m_Format{};
    gfxSurfacePresentMode m_PresentMode{};
    epiSize2u m_Extent{};

EPI_GENREGION_END(gfxSwapChainCreateInfo)
};

class gfxSwapChain : public Object
{
EPI_GENREGION_BEGIN(gfxSwapChain)

EPI_GENHIDDEN_gfxSwapChain()

public:
    constexpr static epiMetaTypeID TypeID{0x7a8b586};

    enum gfxSwapChain_PIDs
    {
        PID_BufferCount = 0xd1605dff,
        PID_Extent = 0x21a25c7e,
        PID_ImageViews = 0x30732ad6,
        PID_COUNT = 3
    };

protected:
    epiU32 GetBufferCount_Callback() const;
    epiSize2u GetExtent_Callback() const;

protected:
    epiArray<gfxTextureView> m_ImageViews{};

EPI_GENREGION_END(gfxSwapChain)

public:
    friend class internalgfx::gfxSwapChainImpl;

public:
    gfxSwapChain() = default;
    explicit gfxSwapChain(const std::shared_ptr<internalgfx::gfxSwapChainImpl>& impl);

    epiBool Recreate(const gfxSwapChainCreateInfo& info);

    epiS32 AcquireNextImage(const gfxSemaphore* signalSemaphore = nullptr,
                            const gfxFence* signalFence = nullptr,
                            epiU64 timeout = std::numeric_limits<epiU64>::max());

protected:
    void RebindImpl();

protected:
    epiPimpl<internalgfx::gfxSwapChainImpl> m_Impl;
};

EPI_NAMESPACE_END()
