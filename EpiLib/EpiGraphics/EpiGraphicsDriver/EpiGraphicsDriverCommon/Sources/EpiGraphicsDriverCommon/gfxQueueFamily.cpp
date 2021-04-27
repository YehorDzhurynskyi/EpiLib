EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxQueueFamily.h"
#include "EpiGraphicsDriverCommon/gfxQueueFamily.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxQueueFamilyDescriptor::gfxQueueFamilyDescriptor(const std::shared_ptr<internalgfx::gfxQueueFamilyDescriptorImpl>& impl)
    : m_Impl{impl}
{
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

gfxQueueFamily::gfxQueueFamily(const std::shared_ptr<internalgfx::gfxQueueFamilyImpl>& impl)
    : m_Impl{impl}
{
    epiArray<gfxQueue>& queues = GetQueues();
    queues.Reserve(impl->GetQueues().Size());

    // NOTE: filling gfxQueue with their implementations (gfxQueueFamilyImpl still owns these implementations)
    std::transform(impl->GetQueues().begin(),
                   impl->GetQueues().end(),
                   std::back_inserter(queues),
                   [](const std::shared_ptr<internalgfx::gfxQueueImpl>& queueImpl)
    {
        return gfxQueue(queueImpl);
    });
}

gfxQueueType gfxQueueFamily::GetQueueTypeSupportedMask_Callback() const
{
    return m_Impl->GetQueueTypeMask();
}

epiU32 gfxQueueFamily::GetQueueCount_Callback() const
{
    return m_Impl->GetQueueCount();
}

EPI_NAMESPACE_END()
