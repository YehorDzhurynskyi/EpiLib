#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxSwapChain.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphics/gfxSurface.h"
#include "EpiGraphics/gfxQueueFamily.h"

EPI_NAMESPACE_BEGIN()

class gfxSwapChainCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxSwapChainCreateInfo)

EPI_GENHIDDEN_gfxSwapChainCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0x23e11eb4};

    enum gfxSwapChainCreateInfo_PIDs
    {
        PID_Surface = 0x73fca7f2,
        PID_SurfacePreTransformMask = 0xbbda978a,
        PID_ImageMinCount = 0x2b760e66,
        PID_ImageFormat = 0xc2f7900b,
        PID_ImageColorSpace = 0x9ac7e266,
        PID_ImageExtent = 0x3a43bb9c,
        PID_ImageArrayLayers = 0x7d55291e,
        PID_ImageUsageMask = 0x7bc0668,
        PID_ImageSharingMode = 0xe4522abc,
        PID_QueueFamilies = 0x459d6c2c,
        PID_CompositeAlphaMask = 0xb9b092ec,
        PID_PresentMode = 0x2430171b,
        PID_IsClipped = 0x458b7017,
        PID_COUNT = 13
    };

protected:
    gfxSurface m_Surface{};
    gfxSurfaceTransformMask m_SurfacePreTransformMask{};
    epiU32 m_ImageMinCount{0};
    gfxFormat m_ImageFormat{};
    gfxSurfaceColorSpace m_ImageColorSpace{};
    epiSize2u m_ImageExtent{};
    epiU32 m_ImageArrayLayers{0};
    gfxImageUsage m_ImageUsageMask{};
    gfxSharingMode m_ImageSharingMode{};
    epiArray<gfxQueueFamily> m_QueueFamilies{};
    gfxCompositeAlphaMask m_CompositeAlphaMask{};
    gfxSurfacePresentMode m_PresentMode{};
    epiBool m_IsClipped{false};

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
    epiArray<gfxImageView> m_ImageViews{};

EPI_GENREGION_END(gfxSwapChain)

public:
    class Impl;

public:
    gfxSwapChain() = default;
    explicit gfxSwapChain(const std::shared_ptr<Impl>& impl);

    epiBool HasImpl() const;

    epiBool Recreate(const gfxSwapChainCreateInfo& info);

    epiS32 AcquireNextImage(const gfxSemaphore* signalSemaphore = nullptr,
                            const gfxFence* signalFence = nullptr,
                            epiU64 timeout = std::numeric_limits<epiU64>::max());

protected:
    void RebindImpl();

protected:
    std::shared_ptr<Impl> m_Impl;
};

EPI_NAMESPACE_END()
