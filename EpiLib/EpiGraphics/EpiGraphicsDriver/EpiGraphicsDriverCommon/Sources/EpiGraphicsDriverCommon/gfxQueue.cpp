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

gfxQueue::gfxQueue(std::shared_ptr<internalgfx::gfxQueueImpl>&& impl)
    : m_Impl{std::move(impl)}
{
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
