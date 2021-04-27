EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxTextureView.h"
#include "EpiGraphicsDriverCommon/gfxTextureView.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

gfxTextureView::gfxTextureView(const std::shared_ptr<internalgfx::gfxTextureViewImpl>& impl)
    : m_Impl{impl}
{
}

EPI_NAMESPACE_END()
