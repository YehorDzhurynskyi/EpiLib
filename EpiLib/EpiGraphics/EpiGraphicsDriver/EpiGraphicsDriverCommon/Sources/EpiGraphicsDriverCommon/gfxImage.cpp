EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxImage.h"
#include "EpiGraphicsDriverCommon/gfxImage.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxImage::gfxImage(const std::shared_ptr<Impl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxImage::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

EPI_NAMESPACE_END()