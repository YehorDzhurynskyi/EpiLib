EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/Synchronization/gfxFence.h"
#include "EpiGraphicsDriverCommon/Synchronization/gfxFence.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxFence::gfxFence(const std::shared_ptr<internalgfx::gfxFenceImpl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxFence::Reset()
{
    return m_Impl->Reset();
}

epiBool gfxFence::Wait(epiU64 timeout)
{
    return m_Impl->Wait(timeout);
}

EPI_NAMESPACE_END()
