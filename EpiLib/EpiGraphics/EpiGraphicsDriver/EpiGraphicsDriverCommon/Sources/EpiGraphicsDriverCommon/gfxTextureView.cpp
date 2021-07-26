EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxTextureView.h"
#include "EpiGraphicsDriverCommon/gfxTextureView.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

gfxTextureView::gfxTextureView(const std::shared_ptr<Impl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxTextureView::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

EPI_NAMESPACE_END()
