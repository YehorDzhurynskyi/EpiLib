EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriver/gfxQueue.h"
#include "EpiGraphicsDriver/gfxQueue.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverImpl/EpiGraphicsDriverImpl.h"

EPI_NAMESPACE_BEGIN()

gfxQueue::gfxQueue(internalgfx::gfxQueueImpl* impl)
    : m_Impl{impl}
{
}

gfxQueue::gfxQueue(gfxQueue&& rhs)
{
    m_Impl = rhs.m_Impl;
    rhs.m_Impl = nullptr;
}

gfxQueue& gfxQueue::operator=(gfxQueue&& rhs)
{
    m_Impl = rhs.m_Impl;
    rhs.m_Impl = nullptr;

    return *this;
}

gfxQueue::~gfxQueue()
{
    delete m_Impl;
}

epiBool gfxQueue::GetIsPresentSupported_Callback() const
{
    return m_Impl->IsPresentSupported();
}

epiBool gfxQueue::IsQueueTypeSupported(gfxQueueType mask) const
{
    return m_Impl->IsQueueTypeSupported(mask);
}

EPI_NAMESPACE_END()
