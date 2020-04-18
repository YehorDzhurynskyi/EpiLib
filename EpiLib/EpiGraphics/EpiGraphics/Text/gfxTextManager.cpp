#include "EpiGraphics/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Text/gfxTextManager.h"
#include "EpiGraphics/Text/gfxTextManager.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/Text/gfxTextFont.h"

EPI_NAMESPACE_BEGIN()

gfxTextManager::gfxTextManager()
{
    FT_Init_FreeType(&m_FTLibrary);
}

gfxTextManager::~gfxTextManager()
{
    FT_Done_FreeType(m_FTLibrary);
}

std::unique_ptr<gfxTextFont> gfxTextManager::CreateFont(const epiChar* ttf)
{
    auto font = std::make_unique<gfxTextFont>();

    const FT_Error error = FT_New_Face(m_FTLibrary, ttf, 0, &font->m_Face);
    if (error != 0)
    {
        font.release();
    }

    return font;
}

EPI_NAMESPACE_END()
