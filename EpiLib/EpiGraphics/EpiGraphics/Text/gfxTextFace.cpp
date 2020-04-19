#include "EpiGraphics/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Text/gfxTextFace.h"
#include "EpiGraphics/Text/gfxTextFace.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/Text/gfxTextRendered.h"
#include "EpiGraphics/Text/gfxTextRenderedAtlas.h"

#include FT_GLYPH_H

EPI_NAMESPACE_BEGIN()

gfxTextFace::~gfxTextFace()
{
    FT_Done_Face(m_Face);
}

#if 0
epiBool gfxTextFace::CreateRendered(gfxTextRendered& target,
                                    const epiWChar* text,
                                    epiS32 fontSize,
                                    epiS32 spacingX,
                                    epiS32 spacingY,
                                    epiS32 spaceSize,
                                    Color color)
{
    FT_Set_Pixel_Sizes(m_Face, 0, fontSize);

    epiS32 texW = 0;
    epiU32 texH = 0;
    epiU32 maxh = 0;
    epiU32 toprow = 0;

    const epiSize_t len = wcslen(text);

    for (epiS32 i = 0; i < len; i++)
    {
        const epiWChar charcode = text[i];
        FT_Load_Char(m_Face, charcode, FT_LOAD_RENDER);

        const FT_UInt glyph_index = FT_Get_Char_Index(m_Face, charcode);
        FT_Load_Glyph(m_Face, glyph_index, FT_LOAD_DEFAULT);
        FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL);

        FT_Glyph glyph;
        FT_Get_Glyph(slot, &glyph);
        FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, 0, 1);

        FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;
        texW += bitmap_glyph->bitmap.width;

        const epiS32 resize = bitmap_glyph->bitmap.rows > bitmap_glyph->top ?
                              bitmap_glyph->bitmap.rows - bitmap_glyph->top :
                              bitmap_glyph->top - bitmap_glyph->bitmap.rows;

        if (texH < bitmap_glyph->bitmap.rows + resize)
        {
            texH = bitmap_glyph->bitmap.rows + resize;
        }

        if (toprow < bitmap_glyph->bitmap.rows)
        {
            toprow = bitmap_glyph->bitmap.rows;
        }

        if (maxh < bitmap_glyph->bitmap.rows + bitmap_glyph->top)
        {
            maxh = bitmap_glyph->bitmap.rows + bitmap_glyph->top;
        }

        if (charcode == ' ')
        {
            texW += spaceSize;
        }

        if (charcode == '\n')
        {
            texH += spacingY + maxh;
            FT_Done_Glyph(glyph);
            continue;
        }

        texW += spacingX;

        FT_Done_Glyph(glyph);
    }

    if (texH <= 0)
    {
        texH = maxh;
    }

    uint8_t im[texH][texW];
    memset(&im[0][0], 0, texW * texH * sizeof(uint8_t));

    epiS32 ih = 0;
    epiS32 iw = 0;
    epiS32 posy = 0;
    epiS32 topy = 0;
    epiS32 maxwidth = 0;
    for (epiS32 i = 0; i < len; i++)
    {
        const epiWChar charcode = text[i];
        FT_Load_Char(m_Face, charcode, FT_LOAD_RENDER);

        const FT_UInt glyph_index = FT_Get_Char_Index(m_Face, charcode);
        FT_Load_Glyph(m_Face, glyph_index, FT_LOAD_DEFAULT);
        FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL);

        FT_Glyph glyph;
        FT_Get_Glyph(slot, &glyph);
        FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, 0, 1);

        FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

        posy = bitmap_glyph->top;
        posy = bitmap_glyph->bitmap.rows - posy;
        topy = toprow - bitmap_glyph->bitmap.rows;

        if (charcode == '\n')
        {
            ih += maxh;
            iw = 0;
            FT_Done_Glyph(glyph);
            continue;
        }
        for (unsigned int y = 0, i = 0; y < bitmap_glyph->bitmap.rows; y++)
        {
            for (unsigned int x = 0; x < bitmap_glyph->bitmap.width; x++, i++)
            {
                posy = abs(posy);
                im[ih + posy + y + topy][iw + x] = bitmap_glyph->bitmap.buffer[i];
            }
        }
        iw += bitmap_glyph->bitmap.width;
        iw += spacingX;
        if (maxwidth < iw)
        {
            maxwidth = iw;
        }

        if (charcode == ' ')
        {
            iw += spacingX;
        }

        FT_Done_Glyph(glyph);
    }

    iw = maxwidth;
    const epiSize_t width = iw;
    const epiSize_t height = texH;
    const epiSize_t size = width * height;

    std::unique_ptr<epiByte[]> data = std::make_unique<epiByte[]>(size * 4);
    memset(data.get(), 0xff, size * 4 * sizeof(epiByte));

    for (epiS32 i = 0, y = 0; i < size; ++y)
    {
        for (epiS32 x = 0; x < width; ++x, ++i)
        {
            data[4 * i + 0] = color.GetRu();
            data[4 * i + 1] = color.GetGu();
            data[4 * i + 2] = color.GetBu();
            data[4 * i + 3] = im[y][x];
        }
    }

    gfxTexture& texture = target.GetTexture();
    texture.Create2D(data.get(), width, height, gfxTextureFormat::RGBA, gfxTexturePixelType::UBYTE);
}
#endif

epiBool gfxTextFace::CreateRendered(gfxTextRendered& target,
                                    const epiWChar* text,
                                    epiS32 fontSize,
                                    Color color) const
{
    // TODO: determine dpi from platform call
    const FT_UInt dpiX = 300;
    const FT_UInt dpiY = 300;

    FT_Set_Char_Size(m_Face, 0, 16 * 64, dpiX, dpiY);
    return false;
}

epiBool gfxTextFace::CreateRenderedAtlas(gfxTextRenderedAtlas& target,
                                         const epiWChar* atlasText,
                                         epiS32 fontSize,
                                         Color color) const
{
    // TODO: determine dpi from platform call
    const FT_UInt dpiX = 96;
    const FT_UInt dpiY = 96;

    if (FT_Set_Char_Size(m_Face, 0, fontSize * 64, dpiX, dpiY))
    {
        // TODO: replace with a log
        epiAssert(false, "FT_Set_Char_Size failed!");
        return false;
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
            return false;
        }

        if (slot->format != FT_GLYPH_FORMAT_BITMAP)
        {
            if (FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL))
            {
                // TODO: replace with a log
                epiAssert(false, "FT_Render_Glyph failed!");
                return false;
            }
        }

        const FT_Glyph_Metrics& metricsGlyph = slot->metrics;
        const FT_Bitmap& bitmap = slot->bitmap;

        epiAssert(bitmap.width == metricsGlyph.width >> 6, "same things");

        texWidth += slot->advance.x >>  6;
    }

    const epiS32 texHeight = (metricsSize.ascender >> 6) - (metricsSize.descender >> 6);
    std::unique_ptr<epiByte[]> data = std::make_unique<epiByte[]>(texHeight * texWidth * 4);

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
            return false;
        }

        if (slot->format != FT_GLYPH_FORMAT_BITMAP)
        {
            if (FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL))
            {
                // TODO: replace with a log
                epiAssert(false, "FT_Render_Glyph failed!");
                return false;
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
                const epiU32 coordX = slot->bitmap_left + pen + x;
                const epiU32 coord = 4 * (coordY * texWidth + coordX);

                data[coord + 0] = color.GetRu();
                data[coord + 1] = color.GetGu();
                data[coord + 2] = color.GetBu();
                data[coord + 3] = bitmap.buffer[i];
            }
        }
        epiRect2f uv;
        uv.Left = pen / static_cast<epiFloat>(texWidth);
        uv.Top = bitmap.rows / static_cast<epiFloat>(texHeight);
        uv.Bottom = 0.0f;
        uv.Right = (pen + slot->advance.x >> 6) / static_cast<epiFloat>(texWidth);

        target.m_CharMap.try_emplace(ch, uv);

        pen += slot->advance.x >> 6;
    }

    gfxTexture& texture = target.GetTexture();
    texture.Create2D(data.get(), texWidth, texHeight, gfxTextureFormat::RGBA, gfxTexturePixelType::UBYTE);
}


EPI_NAMESPACE_END()
