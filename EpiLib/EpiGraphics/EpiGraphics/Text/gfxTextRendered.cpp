#include "EpiGraphics/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Text/gfxTextRendered.h"
#include "EpiGraphics/Text/gfxTextRendered.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

void gfxTextRendered::Bind()
{
    super::Bind();

    m_Texture.Bind();
}

void gfxTextRendered::UnBind()
{
    super::UnBind();

    m_Texture.UnBind();
}

EPI_NAMESPACE_END()
