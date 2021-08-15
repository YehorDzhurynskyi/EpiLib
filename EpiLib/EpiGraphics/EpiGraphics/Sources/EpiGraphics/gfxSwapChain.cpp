EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxSwapChain.h"
#include "EpiGraphics/gfxSwapChain.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsImpl/gfxSwapChainImpl.h"
#include "EpiGraphicsImpl/gfxQueueImpl.h"

EPI_NAMESPACE_BEGIN()

gfxSwapChain::gfxSwapChain(const std::shared_ptr<Impl>& impl)
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
        if (!signalSemaphore->HasImpl())
        {
            epiLogError("Failed to AcquireNextImage! The provided signal Semaphore has no implementation!");
            return -1;
        }
    }

    if (signalFence != nullptr)
    {
        if (!signalFence->HasImpl())
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
    epiArray<gfxImageView>& imageViews = GetImageViews();
    imageViews.Clear();
    imageViews.Reserve(m_Impl->GetImageViews().Size());

    // NOTE: filling gfxQueueFamily with their implementations (gfxDeviceImpl still owns these implementations)
    std::transform(m_Impl->GetImageViews().begin(),
                   m_Impl->GetImageViews().end(),
                   std::back_inserter(imageViews),
                   [](const std::shared_ptr<gfxImageView::Impl>& imageViewImpl)
    {
        return gfxImageView(imageViewImpl);
    });
}

// NOTE: `gfxQueuePresentInfo` is located in the SwapChain translation because of cyclic including
epiBool gfxQueue::Present(const gfxQueuePresentInfo& info)
{
    if (!IsQueueTypeSupported(gfxQueueType_Graphics))
    {
        epiLogError("Failed to Present QueuePresentInfo! Present should be called on graphics Queue!");
        return false;
    }

    const epiBool allSemaphoresAreValid = std::all_of(info.GetWaitSemaphores().begin(),
                                                      info.GetWaitSemaphores().end(),
                                                      [](const gfxSemaphore& semaphore)
    {
        return semaphore.HasImpl();
    });

    if (!allSemaphoresAreValid)
    {
        epiLogError("Failed to Present QueuePresentInfo! Some of the provided wait Semaphores have no implementation!");
        return false;
    }

    const epiBool allSwapChainsAreValid = std::all_of(info.GetSwapChains().begin(),
                                                      info.GetSwapChains().end(),
                                                      [](const gfxSwapChain& swapChain)
    {
        return swapChain.HasImpl();
    });

    if (!allSwapChainsAreValid)
    {
        epiLogError("Failed to Present QueuePresentInfo! Some of the provided SwapChains have no implementation!");
        return false;
    }

    if (info.GetSwapChains().Size() != info.GetSwapChainImageIndices().Size())
    {
        epiLogError("Failed to Present QueuePresentInfo! The number of the SwapChain image indices "
                    "(count=`{}`) and SwapChains (count=`{}`) should be equal!",
                    info.GetSwapChainImageIndices().Size(),
                    info.GetSwapChains().Size());
        return false;
    }

    return m_Impl->Present(info);
}

EPI_NAMESPACE_END()
