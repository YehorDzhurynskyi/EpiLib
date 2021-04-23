EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxQueueFamily.h"
#include "EpiGraphicsDriverCommon/gfxQueueFamily.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxQueueFamilyDescriptor::gfxQueueFamilyDescriptor(internalgfx::gfxQueueFamilyDescriptorImpl* impl)
    : epiPimpl<internalgfx::gfxQueueFamilyDescriptorImpl>{impl}
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

epiSize_t gfxQueueFamilyDescriptor::GetQueueCount_Callback() const
{
    return m_Impl->GetQueueCount();
}

gfxQueueFamily::gfxQueueFamily(internalgfx::gfxQueueFamilyImpl* impl, epiBool isOwner)
    : epiPimpl<internalgfx::gfxQueueFamilyImpl>{impl, isOwner}
{
    epiArray<gfxQueue>& queues = GetQueues();
    queues.Reserve(impl->GetQueues().Size());

    // NOTE: filling gfxQueue with their implementations (gfxQueueFamilyImpl still owns these implementations)
    std::transform(impl->GetQueues().begin(),
                   impl->GetQueues().end(),
                   std::back_inserter(queues),
                   [](std::unique_ptr<internalgfx::gfxQueueImpl>& queueImpl)
    {
        constexpr epiBool kIsOwner = false;
        return gfxQueue(queueImpl.get(), kIsOwner);
    });
}

EPI_NAMESPACE_END()
