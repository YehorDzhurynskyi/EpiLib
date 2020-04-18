#include "EpiGraphics/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Text/gfxTextManager.h"
#include "EpiGraphics/Text/gfxTextManager.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/Text/gfxTextFace.h"

EPI_NAMESPACE_BEGIN()

gfxTextManager::gfxTextManager()
{
    if (FT_Init_FreeType(&m_FTLibrary))
    {
        // TODO: log
        epiAssert(false, "FreeType Library initialization failed!");
    }

    if (!CreateFace(m_DefaultFace, "C:\\Windows\\Fonts\\verdana.ttf"))
    {
        // TODO: log
        epiAssert(false, "FreeType Library Default FontFace initialization failed!");
    }
}

gfxTextManager::~gfxTextManager()
{
    FT_Done_FreeType(m_FTLibrary);
}

epiBool gfxTextManager::CreateFace(gfxTextFace& target, const epiChar* ttf) const
{
    const FT_Error error = FT_New_Face(m_FTLibrary, ttf, 0, &target.m_Face);
    return error == 0;
}

EPI_NAMESPACE_END()
