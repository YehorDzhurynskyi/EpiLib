EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxQueue.h"
#include "EpiGraphics/gfxQueue.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsImpl/gfxQueueImpl.h"

#include "EpiGraphics/gfxSwapChain.h"
#include "EpiGraphics/gfxCommandBuffer.h"

EPI_NAMESPACE_BEGIN()

gfxQueue::gfxQueue(const std::shared_ptr<Impl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxQueue::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

epiBool gfxQueue::Submit(const gfxQueueSubmitInfo& info)
{
    return Submit(epiArray<gfxQueueSubmitInfo>{info});
}

epiBool gfxQueue::Submit(const gfxQueueSubmitInfo& info, const gfxFence& signalFence)
{
    return Submit(epiArray<gfxQueueSubmitInfo>{info}, signalFence);
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
