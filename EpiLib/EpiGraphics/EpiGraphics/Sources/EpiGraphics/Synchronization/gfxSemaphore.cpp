EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Synchronization/gfxSemaphore.h"
#include "EpiGraphics/Synchronization/gfxSemaphore.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxSemaphore::gfxSemaphore(const std::shared_ptr<Impl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxSemaphore::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

epiBool gfxSemaphore::Wait(const gfxSemaphoreWaitInfo& info, epiU64 timeout)
{
    return m_Impl->Wait(info, timeout);
}

EPI_NAMESPACE_END()
