EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxSampler.h"
#include "EpiGraphicsDriverCommon/gfxSampler.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

gfxSampler::gfxSampler(const std::shared_ptr<Impl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxSampler::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

EPI_NAMESPACE_END()
