EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxImageView.h"
#include "EpiGraphics/gfxImageView.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

gfxImageView::gfxImageView(const std::shared_ptr<Impl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxImageView::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

EPI_NAMESPACE_END()
