EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxTexture.h"
#include "EpiGraphicsDriverCommon/gfxTexture.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxTexture::gfxTexture(internalgfx::gfxTextureImpl* impl)
    : m_Impl{impl}
{
}

gfxTexture::gfxTexture(gfxTexture&& rhs)
{
    m_Impl = rhs.m_Impl;

    rhs.m_Impl = nullptr;
}

gfxTexture& gfxTexture::operator=(gfxTexture&& rhs)
{
    m_Impl = rhs.m_Impl;

    rhs.m_Impl = nullptr;

    return *this;
}

gfxTexture::~gfxTexture()
{
    delete m_Impl;
}

EPI_NAMESPACE_END()
