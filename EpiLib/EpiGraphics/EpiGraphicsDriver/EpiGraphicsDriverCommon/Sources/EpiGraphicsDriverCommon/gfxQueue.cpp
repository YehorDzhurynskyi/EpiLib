EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxQueue.h"
#include "EpiGraphicsDriverCommon/gfxQueue.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxQueue::gfxQueue(const std::shared_ptr<internalgfx::gfxQueueImpl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxQueue::Submit(const gfxQueueSubmitInfo& info)
{
    epiPtrArray<const internalgfx::gfxCommandBufferImpl> commandBuffersImpl;
    commandBuffersImpl.Reserve(info.GetCommandBuffers().Size());

    std::transform(info.GetCommandBuffers().begin(),
                   info.GetCommandBuffers().end(),
                   std::back_inserter(commandBuffersImpl),
                   [](const gfxCommandBuffer& commandBuffer)
    {
        return commandBuffer.m_Impl.Ptr();
    });

    const epiBool hasInvalidCommandBuffer = std::any_of(commandBuffersImpl.begin(),
                                                        commandBuffersImpl.end(),
                                                        [](const internalgfx::gfxCommandBufferImpl* impl)
    {
        return impl == nullptr;
    });

    if (hasInvalidCommandBuffer)
    {
        epiLogError("Failed to Submit! Some CommandBuffer has no implementation!");
        return false;
    }

    return m_Impl->Submit(info, commandBuffersImpl);
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
