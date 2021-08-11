EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Synchronization/gfxFence.h"
#include "EpiGraphics/Synchronization/gfxFence.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsImpl/Synchronization/gfxFenceImpl.h"

EPI_NAMESPACE_BEGIN()

gfxFence::gfxFence(const std::shared_ptr<Impl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxFence::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

epiBool gfxFence::Reset()
{
    if (!HasImpl())
    {
        epiLogError("A calling object has no implementation!");
        return false;
    }

    return m_Impl->Reset();
}

epiBool gfxFence::Wait(epiU64 timeout)
{
    if (!HasImpl())
    {
        epiLogError("A calling object has no implementation!");
        return false;
    }

    return m_Impl->Wait(timeout);
}

EPI_NAMESPACE_END()
