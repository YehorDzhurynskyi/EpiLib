EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxSwapChain.h"
#include "EpiGraphicsDriverCommon/gfxSwapChain.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxSwapChain::gfxSwapChain(const std::shared_ptr<internalgfx::gfxSwapChainImpl>& impl)
    : m_Impl{impl}
{
    RebindImpl();
}

epiBool gfxSwapChain::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

epiBool gfxSwapChain::Recreate(const gfxSwapChainCreateInfo& info)
{
    if (!m_Impl->Recreate(info))
    {
        return false;
    }

    RebindImpl();

    return true;
}

epiS32 gfxSwapChain::AcquireNextImage(const gfxSemaphore* signalSemaphore, const gfxFence* signalFence, epiU64 timeout)
{
    if (signalSemaphore != nullptr)
    {
        if (!internalgfx::HasImpl<gfxSemaphore::Impl>(*signalSemaphore))
        {
            epiLogError("Failed to AcquireNextImage! The provided signal Semaphore has no implementation!");
            return -1;
        }
    }

    if (signalFence != nullptr)
    {
        if (!internalgfx::HasImpl<internalgfx::gfxFenceImpl>(*signalFence))
        {
            epiLogError("Failed to AcquireNextImage! The provided signal Fence has no implementation!");
            return -1;
        }
    }

    return m_Impl->AcquireNextImage(signalSemaphore, signalFence, timeout);
}

epiU32 gfxSwapChain::GetBufferCount_Callback() const
{
    return m_Impl->GetBufferCount();
}

epiSize2u gfxSwapChain::GetExtent_Callback() const
{
    return m_Impl->GetExtent();
}

void gfxSwapChain::RebindImpl()
{
    epiArray<gfxTextureView>& imageViews = GetImageViews();
    imageViews.Clear();
    imageViews.Reserve(m_Impl->GetImageViews().Size());

    // NOTE: filling gfxQueueFamily with their implementations (gfxDeviceImpl still owns these implementations)
    std::transform(m_Impl->GetImageViews().begin(),
                   m_Impl->GetImageViews().end(),
                   std::back_inserter(imageViews),
                   [](const std::shared_ptr<internalgfx::gfxTextureViewImpl>& imageViewImpl)
    {
        return gfxTextureView(imageViewImpl);
    });
}

EPI_NAMESPACE_END()
