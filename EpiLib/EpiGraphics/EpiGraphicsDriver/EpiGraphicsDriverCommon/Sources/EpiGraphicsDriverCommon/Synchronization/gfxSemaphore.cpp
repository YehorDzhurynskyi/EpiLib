EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/Synchronization/gfxSemaphore.h"
#include "EpiGraphicsDriverCommon/Synchronization/gfxSemaphore.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxSemaphore::gfxSemaphore(const std::shared_ptr<gfxSemaphore::Impl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxSemaphore::Wait(const gfxSemaphoreWaitInfo& info, epiU64 timeout)
{
    return m_Impl->Wait(info, timeout);
}

EPI_NAMESPACE_END()
