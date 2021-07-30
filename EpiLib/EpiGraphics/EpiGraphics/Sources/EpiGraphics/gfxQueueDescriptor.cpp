EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxQueueDescriptor.h"
#include "EpiGraphics/gfxQueueDescriptor.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxDriverInternal.h"
#include "EpiGraphics/gfxSurface.h"

EPI_NAMESPACE_BEGIN()

gfxQueueDescriptor::gfxQueueDescriptor(gfxQueueType typeMask, const epiArray<epiFloat>& priorities, const epiArray<gfxSurface>& surfaceTargets)
    : m_TypeMask{typeMask}
    , m_Priorities{priorities.begin(), priorities.end()}
    , m_SurfaceTargets{surfaceTargets.begin(), surfaceTargets.end()}
{
}

epiU32 gfxQueueDescriptor::GetQueueCount_Callback() const
{
    return GetPriorities().Size();
}

epiSize_t gfxQueueDescriptorList::GetSize_Callback() const
{
    return m_QueueDescriptors.size();
}

void gfxQueueDescriptorList::Push(gfxQueueType typeMask, const epiArray<epiFloat>& priorities, const epiArray<gfxSurface>& surfaceTargets)
{
    gfxQueueDescriptor desc(typeMask, priorities, surfaceTargets);

    Push(std::move(desc));
}

void gfxQueueDescriptorList::Push(gfxQueueDescriptor&& desc)
{
    if (desc.GetTypeMask() == gfxQueueType{0})
    {
        epiLogError("Type mask shouldn't be equal to gfxQueueType{0}!");
        return;
    }

    if (desc.GetQueueCount() == 0)
    {
        epiLogError("Number of requested queue should be at least 1!");
        return;
    }

    m_QueueDescriptors.push_back(std::move(desc));
}

gfxQueueDescriptor& gfxQueueDescriptorList::At(epiU32 index)
{
    epiAssert(index < m_QueueDescriptors.size());
    return m_QueueDescriptors[index];
}

const gfxQueueDescriptor& gfxQueueDescriptorList::At(epiU32 index) const
{
    epiAssert(index < m_QueueDescriptors.size());
    return m_QueueDescriptors[index];
}

gfxQueueDescriptor& gfxQueueDescriptorList::operator[](epiU32 index)
{
    return At(index);
}

const gfxQueueDescriptor& gfxQueueDescriptorList::operator[](epiU32 index) const
{
    return At(index);
}

EPI_NAMESPACE_END()
