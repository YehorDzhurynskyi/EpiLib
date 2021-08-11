#pragma once

#include "EpiGraphics/gfxSwapChain.h"

EPI_NAMESPACE_BEGIN()

class gfxSwapChain::Impl
{
public:
    static const gfxSwapChain::Impl* ExtractImpl(const gfxSwapChain& swapChain) { return swapChain.m_Impl.get(); }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    virtual epiBool Recreate(const gfxSwapChainCreateInfo& info) = 0;

    virtual epiS32 AcquireNextImage(const gfxSemaphore* signalSemaphore, const gfxFence* signalFence, epiU64 timeout) = 0;

    epiU32 GetBufferCount() const { return m_ImageViews.Size(); }
    virtual epiSize2u GetExtent() const = 0;

    const epiArray<std::shared_ptr<gfxImageView::Impl>>& GetImageViews() const { return m_ImageViews; }

protected:
    epiArray<std::shared_ptr<gfxImageView::Impl>> m_ImageViews;
};

EPI_NAMESPACE_END()
