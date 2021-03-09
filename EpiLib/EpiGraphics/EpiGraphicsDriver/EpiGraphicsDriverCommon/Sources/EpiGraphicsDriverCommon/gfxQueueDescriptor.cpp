EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxQueueDescriptor.h"
#include "EpiGraphicsDriverCommon/gfxQueueDescriptor.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxSurface.h"
#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

epiBool gfxQueueDescriptor::IsResolved() const
{
    return m_Queues.size() == GetDesiredQueueCount();
}

epiBool gfxQueueDescriptor::TryResolveQueue(gfxQueue&& queue)
{
    if (IsResolved())
    {
        return false;
    }

    if (const gfxQueueType desirableType = GetType(); (queue.GetType() & desirableType) != desirableType)
    {
        return false;
    }

    m_Queues.push_back(std::move(queue));

    return true;
}

epiBool gfxQueueDescriptor::IsPresentRequired() const
{
    epiAssert((m_Type & gfxQueueType_Present) == 0 || m_PresentSurface != nullptr);

    return (m_Type & gfxQueueType_Present) && (m_PresentSurface != nullptr);
}

void gfxQueueDescriptor::AddDesiredQueue(epiFloat priority)
{
    GetPriorities().push_back(priority);
}

epiU32 gfxQueueDescriptor::GetDesiredQueueCount_Callback() const
{
    return GetPriorities().Size();
}

void gfxQueueDescriptor::AcquireQueues(std::vector<gfxQueue>& queues)
{
    queues = std::move(m_Queues);
}

const internalgfx::gfxSurfaceImpl* gfxQueueDescriptor::GetPresentSurface() const
{
    return m_PresentSurface;
}

void gfxQueueDescriptor::SetPresentSurface(const internalgfx::gfxSurfaceImpl* surfaceImpl)
{
    m_PresentSurface = surfaceImpl;
}

void gfxQueueDescriptorList::Add(gfxQueueType type, const epiArray<epiFloat>& priorities)
{
    gfxQueueDescriptor desc;
    desc.SetType(type);

    for (const epiFloat priority : priorities)
    {
        desc.AddDesiredQueue(priority);
    }

    Add(std::move(desc));
}

void gfxQueueDescriptorList::Add(gfxQueueDescriptor&& desc)
{
    if (desc.GetPriorities().IsEmpty())
    {
        epiLogError("Number of priorties should be >= 1!");
        return;
    }

    m_QueueDescriptors.push_back(std::move(desc));
}

EPI_NAMESPACE_END()
