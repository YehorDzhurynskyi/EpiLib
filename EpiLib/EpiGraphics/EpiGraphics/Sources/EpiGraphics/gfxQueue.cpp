EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxQueue.h"
#include "EpiGraphics/gfxQueue.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsImpl/gfxQueueImpl.h"

#include "EpiGraphics/gfxSwapChain.h"

namespace
{

EPI_NAMESPACE_USING()

epiBool QueueSubmitInfoIsValid(const gfxQueueSubmitInfo& info)
{
    const epiBool allcommandBuffersAreValid = std::all_of(info.GetCommandBuffers().begin(),
                                                          info.GetCommandBuffers().end(),
                                                          [](const gfxCommandBuffer& commandBuffer)
    {
        return commandBuffer.HasImpl();
    });

    if (!allcommandBuffersAreValid)
    {
        epiLogError("Failed to Submit QueueSubmitInfo! Some of the provided CommandBuffers has no implementation!");
        return false;
    }

    const epiBool allSignalSemaphoresAreValid = std::all_of(info.GetSignalSemaphores().begin(),
                                                            info.GetSignalSemaphores().end(),
                                                            [](const gfxSemaphore& semaphore)
    {
        return semaphore.HasImpl();
    });

    if (!allSignalSemaphoresAreValid)
    {
        epiLogError("Failed to Submit QueueSubmitInfo! Some of the provided signal Semaphores has no implementation!");
        return false;
    }

    const epiBool allWaitSemaphoresAreValid = std::all_of(info.GetWaitSemaphores().begin(),
                                                          info.GetWaitSemaphores().end(),
                                                          [](const gfxSemaphore& semaphore)
    {
        return semaphore.HasImpl();
    });

    if (!allWaitSemaphoresAreValid)
    {
        epiLogError("Failed to Submit QueueSubmitInfo! Some of the provided wait Semaphores has no implementation!");
        return false;
    }

    if (info.GetWaitSemaphores().Size() != info.GetWaitDstStageMasks().Size())
    {
        epiLogError("Failed to Submit QueueSubmitInfo! The number of the provided wait Semaphores (count=`{}`) "
                    "should be equal to wait dst stage masks (count=`{}`)!",
                    info.GetWaitSemaphores().Size(),
                    info.GetWaitDstStageMasks().Size());
        return false;
    }

    return true;
};


} // namespace

EPI_NAMESPACE_BEGIN()

gfxQueue::gfxQueue(const std::shared_ptr<Impl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxQueue::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

epiBool gfxQueue::Submit(const epiArray<gfxQueueSubmitInfo>& infos)
{
    if (!std::all_of(infos.begin(), infos.end(), &QueueSubmitInfoIsValid))
    {
        return false;
    }

    return m_Impl->Submit(infos);
}

epiBool gfxQueue::Submit(const epiArray<gfxQueueSubmitInfo>& infos, const gfxFence& signalFence)
{
    if (!signalFence.HasImpl())
    {
        epiLogError("Failed to Submit QueueSubmitInfo! The provided signal Fence has no implementation!");
        return false;
    }

    if (!std::all_of(infos.begin(), infos.end(), &QueueSubmitInfoIsValid))
    {
        return false;
    }

    return m_Impl->Submit(infos, signalFence);
}

epiBool gfxQueue::Submit(const gfxQueueSubmitInfo& info)
{
    return Submit(epiArray<gfxQueueSubmitInfo>{info});
}

epiBool gfxQueue::Submit(const gfxQueueSubmitInfo& info, const gfxFence& signalFence)
{
    return Submit(epiArray<gfxQueueSubmitInfo>{info}, signalFence);
}

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
                                                      [](const gfxSwapChain* swapChain)
    {
        return swapChain != nullptr && swapChain->HasImpl();
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

epiBool gfxQueue::Wait()
{
    return m_Impl->Wait();
}

gfxQueueType gfxQueue::GetType_Callback() const
{
    return m_Impl->GetType();
}

epiFloat gfxQueue::GetPriority_Callback() const
{
    return m_Impl->GetPriority();
}

epiBool gfxQueue::IsQueueTypeSupported(gfxQueueType mask) const
{
    return m_Impl->IsQueueTypeSupported(mask);
}

EPI_NAMESPACE_END()
