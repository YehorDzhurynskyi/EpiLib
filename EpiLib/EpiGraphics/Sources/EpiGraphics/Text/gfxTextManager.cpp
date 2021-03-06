EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Text/gfxTextManager.h"
#include "EpiGraphics/Text/gfxTextManager.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/Text/gfxTextFace.h"

#include FT_LCD_FILTER_H

EPI_NAMESPACE_BEGIN()

// TODO: https://stackoverflow.com/questions/5262951/what-is-state-of-the-art-for-text-rendering-in-opengl-as-of-version-4-1

gfxTextManager::gfxTextManager()
{
    if (FT_Init_FreeType(&m_FTLibrary))
    {
        epiLogFatal("FreeType `FT_Init_FreeType` has failed!");
    }

    CreateFace(m_DefaultFace, "C:\\Windows\\Fonts\\arial.ttf");

    FT_Library_SetLcdFilter(m_FTLibrary, FT_LCD_FILTER_LIGHT);
}

gfxTextManager::~gfxTextManager()
{
    FT_Done_FreeType(m_FTLibrary);
}

// TODO: refactor signature
void gfxTextManager::CreateFace(gfxTextFace& target, const epiChar* ttf) const
{
    if (FT_New_Face(m_FTLibrary, ttf, 0, &target.m_Face))
    {
        epiLogFatal("FreeType `FT_New_Face` has failed!");
    }

    if (FT_Select_Charmap(target.m_Face, FT_ENCODING_UNICODE))
    {
        epiLogFatal("FreeType `FT_Select_Charmap` has failed!");
    }
}

EPI_NAMESPACE_END()
