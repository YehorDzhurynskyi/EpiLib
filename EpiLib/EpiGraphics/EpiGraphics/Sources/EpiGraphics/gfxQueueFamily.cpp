EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxQueueFamily.h"
#include "EpiGraphics/gfxQueueFamily.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxQueueFamilyDescriptor::gfxQueueFamilyDescriptor(const std::shared_ptr<Impl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxQueueFamilyDescriptor::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

epiBool gfxQueueFamilyDescriptor::IsQueueTypeSupported(gfxQueueType mask) const
{
    return m_Impl->IsQueueTypeSupported(mask);
}

gfxQueueType gfxQueueFamilyDescriptor::GetQueueTypeSupportedMask_Callback() const
{
    return m_Impl->GetQueueTypeSupportedMask();
}

epiU32 gfxQueueFamilyDescriptor::GetQueueCount_Callback() const
{
    return m_Impl->GetQueueCount();
}

gfxQueueFamily::gfxQueueFamily(const std::shared_ptr<Impl>& impl)
    : m_Impl{impl}
{
    epiArray<gfxQueue>& queues = GetQueues();
    queues.Reserve(m_Impl->GetQueues().Size());

    // NOTE: filling gfxQueue with their implementations (gfxQueueFamilyImpl still owns these implementations)
    std::transform(m_Impl->GetQueues().begin(),
                   m_Impl->GetQueues().end(),
                   std::back_inserter(queues),
                   [](const std::shared_ptr<gfxQueue::Impl>& queueImpl)
    {
        return gfxQueue(queueImpl);
    });
}

epiBool gfxQueueFamily::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

gfxQueueType gfxQueueFamily::GetQueueTypeSupportedMask_Callback() const
{
    return m_Impl->GetQueueTypeMask();
}

epiU32 gfxQueueFamily::GetQueueCount_Callback() const
{
    return m_Impl->GetQueueCount();
}

const gfxQueue& gfxQueueFamily::At(epiU32 index) const
{
    return GetQueues()[index];
}

gfxQueue& gfxQueueFamily::At(epiU32 index)
{
    return GetQueues()[index];
}

const gfxQueue& gfxQueueFamily::operator[](epiU32 index) const
{
    return At(index);
}

gfxQueue& gfxQueueFamily::operator[](epiU32 index)
{
    return At(index);
}

EPI_NAMESPACE_END()
