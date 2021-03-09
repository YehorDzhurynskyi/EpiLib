EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxQueue.h"
#include "EpiGraphicsDriverCommon/gfxQueue.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

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

gfxQueueType gfxQueue::GetType_Callback() const
{
    return m_Impl->GetType();
}

EPI_NAMESPACE_END()
