EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxTextureView.h"
#include "EpiGraphicsDriverCommon/gfxTextureView.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

gfxTextureView::gfxTextureView(internalgfx::gfxTextureViewImpl* impl)
    : m_Impl{impl}
{
}

gfxTextureView::gfxTextureView(gfxTextureView&& rhs)
{
    m_Impl = rhs.m_Impl;

    rhs.m_Impl = nullptr;
}

gfxTextureView& gfxTextureView::operator=(gfxTextureView&& rhs)
{
    m_Impl = rhs.m_Impl;

    rhs.m_Impl = nullptr;

    return *this;
}

gfxTextureView::~gfxTextureView()
{
    delete m_Impl;
}

EPI_NAMESPACE_END()
