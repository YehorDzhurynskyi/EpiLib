EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxSampler.h"
#include "EpiGraphicsDriverCommon/gfxSampler.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

gfxSampler::gfxSampler(const std::shared_ptr<internalgfx::gfxSamplerImpl>& impl)
    : m_Impl{impl}
{
}

EPI_NAMESPACE_END()
