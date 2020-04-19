#include "EpiGraphics/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Text/gfxTextFace.h"
#include "EpiGraphics/Text/gfxTextFace.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/Text/gfxTextRendered.h"
#include "EpiGraphics/Text/gfxTextRenderedAtlas.h"
#include "EpiGraphics/Text/gfxTextRenderedGlyph.h"

#include FT_GLYPH_H

EPI_NAMESPACE_BEGIN()

gfxTextFace::~gfxTextFace()
{
    FT_Done_Face(m_Face);
}

void gfxTextFace::CreateRenderedGlyph(gfxTextRenderedGlyph& target, const epiWChar ch, epiS32 fontSize) const
{
    // TODO: determine dpi from platform call
    const FT_UInt dpiX = 282;
    const FT_UInt dpiY = 282;

    if (FT_Set_Char_Size(m_Face, 0, fontSize * 64, dpiX, dpiY))
    {
        // TODO: replace with a log
        epiAssert(false, "FT_Set_Char_Size failed!");
        return;
    }

    const FT_Size_Metrics& metricsSize = m_Face->size->metrics;
    FT_GlyphSlot slot = m_Face->glyph;

    const FT_UInt glyphIndex = FT_Get_Char_Index(m_Face, ch);
    epiAssert(glyphIndex != 0, "Face doesn't support this char code!");

    if (FT_Load_Glyph(m_Face, glyphIndex, FT_LOAD_DEFAULT))
    {
        // TODO: replace with a log
        epiAssert(false, "FT_Load_Glyph failed!");
        return;
    }

    if (slot->format != FT_GLYPH_FORMAT_BITMAP)
    {
        if (FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL))
        {
            // TODO: replace with a log
            epiAssert(false, "FT_Render_Glyph failed!");
            return;
        }
    }

    gfxTexture& texture = target.GetTexture();
    texture.Create2D(slot->bitmap.buffer, slot->bitmap.width, slot->bitmap.rows, gfxTextureFormat::R, gfxTexturePixelType::UBYTE);

    epiVec2u bearing(slot->bitmap_left, slot->bitmap_top);
    target.SetBearing(bearing);

    epiVec2u size(slot->bitmap.width, slot->bitmap.rows);
    target.SetSize(size);

    target.SetAdvance(slot->advance.x >> 6);
}

void gfxTextFace::CreateRenderedABC(gfxTextRenderedABC& target, const epiWChar* abc, epiS32 fontSize) const
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // TODO: move to proper place
    const epiSize_t abclen = wcslen(abc); // TODO: replace all wcslen with safe version
    for (epiU32 i = 0; i < abclen; ++i)
    {
        auto& [it, inserted] = target.m_ABC.try_emplace(abc[i]);
        if (!inserted)
        {
            epiAssert(inserted, "abc items should be unique");
            continue;
        }

        gfxTextRenderedGlyph& glyph = it->second;
        CreateRenderedGlyph(glyph, abc[i], fontSize);
    }
}

void gfxTextFace::CreateRenderedAtlas(gfxTextRenderedAtlas& target, const epiWChar* atlasText, epiS32 fontSize) const
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // TODO: move to proper place
    // TODO: determine dpi from platform call
    const FT_UInt dpiX = 282;
    const FT_UInt dpiY = 282;

    if (FT_Set_Char_Size(m_Face, 0, fontSize * 64, dpiX, dpiY))
    {
        // TODO: replace with a log
        epiAssert(false, "FT_Set_Char_Size failed!");
        return;
    }

    const FT_Size_Metrics& metricsSize = m_Face->size->metrics;
    FT_GlyphSlot slot = m_Face->glyph;

    epiS32 texWidth = 0;
    const epiSize_t atlasTextLen = wcslen(atlasText);
    for (epiU32 i = 0; i < atlasTextLen; ++i)
    {
        const epiWChar ch = atlasText[i];
        const FT_UInt glyphIndex = FT_Get_Char_Index(m_Face, ch);
        epiAssert(glyphIndex != 0, "Face doesn't support this char code!");

        if (FT_Load_Glyph(m_Face, glyphIndex, FT_LOAD_DEFAULT))
        {
            // TODO: replace with a log
            epiAssert(false, "FT_Load_Glyph failed!");
            return;
        }

        if (slot->format != FT_GLYPH_FORMAT_BITMAP)
        {
            if (FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL))
            {
                // TODO: replace with a log
                epiAssert(false, "FT_Render_Glyph failed!");
                return;
            }
        }

        const FT_Glyph_Metrics& metricsGlyph = slot->metrics;
        const FT_Bitmap& bitmap = slot->bitmap;

        epiAssert(bitmap.width == metricsGlyph.width >> 6, "same things");

        texWidth += slot->advance.x >>  6;
    }

    const epiS32 texHeight = (metricsSize.ascender >> 6) - (metricsSize.descender >> 6);
    std::unique_ptr<epiByte[]> data = std::make_unique<epiByte[]>(texHeight * texWidth);

    epiS32 pen = 0;
    for (epiU32 i = 0; i < atlasTextLen; ++i)
    {
        const epiWChar ch = atlasText[i];
        const FT_UInt glyphIndex = FT_Get_Char_Index(m_Face, ch);
        epiAssert(glyphIndex != 0, "Face doesn't support this char code!");

        if (FT_Load_Glyph(m_Face, glyphIndex, FT_LOAD_DEFAULT))
        {
            // TODO: replace with a log
            epiAssert(false, "FT_Load_Glyph failed!");
            return;
        }

        if (slot->format != FT_GLYPH_FORMAT_BITMAP)
        {
            if (FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL))
            {
                // TODO: replace with a log
                epiAssert(false, "FT_Render_Glyph failed!");
                return;
            }
        }

        const FT_Glyph_Metrics& metricsGlyph = slot->metrics;
        const FT_Bitmap& bitmap = slot->bitmap;

        for (epiU32 y = 0, i = 0; y < bitmap.rows; ++y)
        {
            const epiU32 offset = slot->bitmap_top - (bitmap.rows - 1);
            const epiU32 coordY = (bitmap.rows - 1) - y - (metricsSize.descender >> 6) + offset;

            for (epiU32 x = 0; x < bitmap.width; ++x, ++i)
            {
                const epiU32 coordX = pen + slot->bitmap_left + x;
                const epiU32 coord = coordY * texWidth + coordX;

                data[coord] = bitmap.buffer[i];
            }
        }

        gfxTextRenderedAtlasGlyph atlasGlyph;

        epiRect2f uv;
        uv.Left = (pen + slot->bitmap_left) / static_cast<epiFloat>(texWidth);
        uv.Top = (slot->bitmap_top + 1 - (metricsSize.descender >> 6)) / static_cast<epiFloat>(texHeight);
        uv.Right = (pen + slot->bitmap_left + bitmap.width) / static_cast<epiFloat>(texWidth);
        uv.Bottom = (1 - (metricsSize.descender >> 6)) / static_cast<epiFloat>(texHeight);

        atlasGlyph.SetUV(uv);
        atlasGlyph.SetAspectRatio(bitmap.width / static_cast<epiFloat>(bitmap.rows));

        target.m_CharMap.try_emplace(ch, atlasGlyph);

        pen += slot->advance.x >> 6;
    }

    gfxTexture& texture = target.GetTexture();
    texture.Create2D(data.get(), texWidth, texHeight, gfxTextureFormat::R, gfxTexturePixelType::UBYTE);
}


EPI_NAMESPACE_END()
