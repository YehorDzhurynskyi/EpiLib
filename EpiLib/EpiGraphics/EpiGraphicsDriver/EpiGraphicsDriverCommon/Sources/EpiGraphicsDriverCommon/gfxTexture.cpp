EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxTexture.h"
#include "EpiGraphicsDriverCommon/gfxTexture.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxTexture::gfxTexture(const std::shared_ptr<internalgfx::gfxTextureImpl>& impl)
    : m_Impl{impl}
{
}

EPI_NAMESPACE_END()
