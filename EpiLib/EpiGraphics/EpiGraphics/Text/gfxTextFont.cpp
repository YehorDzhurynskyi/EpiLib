#include "EpiGraphics/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Text/gfxTextFont.h"
#include "EpiGraphics/Text/gfxTextFont.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

gfxTextFont::~gfxTextFont()
{
    FT_Done_Face(m_Face);
}

EPI_NAMESPACE_END()
