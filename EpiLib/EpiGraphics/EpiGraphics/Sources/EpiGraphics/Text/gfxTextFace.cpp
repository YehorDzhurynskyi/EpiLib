EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Text/gfxTextFace.h"
#include "EpiGraphics/Text/gfxTextFace.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/Text/gfxTextRendered.h"
#include "EpiGraphics/Text/gfxTextRenderedAtlas.h"
#include "EpiGraphics/Text/gfxTextRenderedGlyph.h"

#include "EpiCore/Platform/epiPlatform.h"

EPI_NAMESPACE_BEGIN()

gfxTextFace::~gfxTextFace()
{
    FT_Done_Face(m_Face);
}

void gfxTextFace::PrepareFontMetrics(epiU32 fontSize) const
{
    const epiVec2u dpi = epiPlatform::GetInstance().GetDeviceDisplay().GetDPI();
    if (FT_Set_Char_Size(m_Face, 0, fontSize * 64, dpi.x, dpi.y))
    {
        epiLogFatal("FreeType `FT_Set_Char_Size` has failed!");
    }
}

gfxTextRenderedGlyph gfxTextFace::CreateRenderedGlyph(const epiWChar ch, epiU32 fontSize) const
{
    gfxTextRenderedGlyph target;

    PrepareFontMetrics(fontSize);

    const FT_Size_Metrics& metricsSize = m_Face->size->metrics;
    FT_GlyphSlot slot = m_Face->glyph;

    const FT_UInt glyphIndex = FT_Get_Char_Index(m_Face, ch);
    epiAssert(glyphIndex != 0, "Face doesn't support this char code!");

    if (FT_Load_Glyph(m_Face, glyphIndex, FT_LOAD_DEFAULT))
    {
        // TODO: replace with a log
        epiAssert(false, "FT_Load_Glyph failed!");
        return target;
    }

    if (slot->format != FT_GLYPH_FORMAT_BITMAP)
    {
        if (FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL))
        {
            // TODO: replace with a log
            epiAssert(false, "FT_Render_Glyph failed!");
            return target;
        }
    }

    gfxTexture& texture = target.GetTexture();
    texture.Create2D(slot->bitmap.buffer, slot->bitmap.width, slot->bitmap.rows, gfxTextureFormat::R, gfxTexturePixelType::UBYTE);

    epiVec2u bearing(slot->bitmap_left, slot->bitmap_top);
    target.SetBearing(bearing);

    epiVec2u size(slot->bitmap.width, slot->bitmap.rows);
    target.SetSize(size);

    target.SetAdvance(slot->advance.x >> 6);

    return target;
}

gfxTextRenderedABC gfxTextFace::CreateRenderedABC(const epiWChar* abc, epiU32 fontSize) const
{
    gfxTextRenderedABC target;

    // TODO: restore
    // glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // TODO: move to proper place
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
        glyph = CreateRenderedGlyph(abc[i], fontSize);
    }

    return target;
}

#if 1
gfxTextRenderedAtlas gfxTextFace::CreateRenderedAtlas(const epiWChar* atlasText, epiU32 fontSize) const
{
    gfxTextRenderedAtlas target;

    // TODO: restore
    // glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // TODO: move to proper place

    PrepareFontMetrics(fontSize);

    const FT_Size_Metrics& metricsSize = m_Face->size->metrics;
    FT_GlyphSlot slot = m_Face->glyph;

    const epiFloat maxHeight = (metricsSize.ascender >> 6) - (metricsSize.descender >> 6);
    const epiS32 texHeight = (metricsSize.ascender >> 6) - (metricsSize.descender >> 6);
    epiS32 texWidth = 0;
    const epiSize_t atlasTextLen = wcslen(atlasText);
    for (epiU32 i = 0; i < atlasTextLen; ++i)
    {
        const epiWChar ch = atlasText[i];
        const FT_UInt glyphIndex = FT_Get_Char_Index(m_Face, ch);
        epiAssert(glyphIndex != 0, "Face doesn't support this char code!");

        if (FT_Load_Glyph(m_Face, glyphIndex, FT_LOAD_RENDER | FT_LOAD_FORCE_AUTOHINT | FT_LOAD_TARGET_LCD))
        {
            // TODO: replace with a log
            epiAssert(false, "FT_Load_Glyph failed!");
            return target;
        }

        texWidth += slot->advance.x >> 6;
    }

    // TODO: check if should be divided by static_cast<epiFloat>(kDpiX);
    std::unique_ptr<epiByte[]> data = std::make_unique<epiByte[]>(texHeight * texWidth * 3);
    memset(data.get(), 0x0, texHeight * texWidth * 3);

    epiS32 pen = 0;
    for (epiU32 i = 0; i < atlasTextLen; ++i)
    {
        const epiWChar ch = atlasText[i];
        const FT_UInt glyphIndex = FT_Get_Char_Index(m_Face, ch);
        epiAssert(glyphIndex != 0, "Face doesn't support this char code!");

        if (FT_Load_Glyph(m_Face, glyphIndex, FT_LOAD_RENDER | FT_LOAD_FORCE_AUTOHINT | FT_LOAD_TARGET_LCD))
        {
            // TODO: replace with a log
            epiAssert(false, "FT_Load_Glyph failed!");
            return target;
        }

        const FT_Bitmap& bitmap = slot->bitmap;
        for (epiU32 y = 0; y < bitmap.rows; ++y)
        {
            const epiU32 coordY = slot->bitmap_top - y - (metricsSize.descender >> 6);

            for (epiU32 x = 0; x < bitmap.width / 3; ++x)
            {
                const epiU32 coordX = pen + slot->bitmap_left + x;

                const epiU32 coordSrc = y * bitmap.pitch + x * 3;
                const epiU32 coordDst = coordY * texWidth * 3 + coordX * 3;

                data[coordDst + 0] = bitmap.buffer[coordSrc + 0];
                data[coordDst + 1] = bitmap.buffer[coordSrc + 1];
                data[coordDst + 2] = bitmap.buffer[coordSrc + 2];
            }
        }

        gfxTextRenderedAtlasGlyph atlasGlyph;

        epiRect2f uv;
        uv.Left = (pen + slot->bitmap_left) / static_cast<epiFloat>(texWidth);
        uv.Top = (slot->bitmap_top + 1 - (metricsSize.descender >> 6)) / static_cast<epiFloat>(texHeight);
        uv.Right = (pen + slot->bitmap_left + bitmap.width / 3) / static_cast<epiFloat>(texWidth);
        uv.Bottom = (1 - (metricsSize.descender >> 6)) / static_cast<epiFloat>(texHeight);

        atlasGlyph.SetUV(uv);
        atlasGlyph.SetAspectRatio((bitmap.width / 3) / static_cast<epiFloat>(bitmap.rows));
        atlasGlyph.SetHeight(bitmap.rows / static_cast<epiFloat>(maxHeight));

        epiVec2f advance;
        advance.x = (slot->advance.x >> 6) / static_cast<epiFloat>(bitmap.width / 3);
        advance.y = 0.0f; // TODO: set

        atlasGlyph.SetAdvance(advance);

        epiVec2f bearing;
        bearing.x = slot->bitmap_left / static_cast<epiFloat>(bitmap.width / 3);
        bearing.y = slot->bitmap_top / static_cast<epiFloat>(bitmap.rows);

        atlasGlyph.SetBearing(bearing);

        target.m_CharMap.try_emplace(ch, atlasGlyph);

        pen += slot->advance.x >> 6;
    }

    target.SetDescender((metricsSize.descender >> 6) / maxHeight);
    target.SetAscender((metricsSize.ascender >> 6) / maxHeight);
    target.SetHeight(metricsSize.height >> 6);

    gfxTexture& texture = target.GetTexture();
    texture.Create2D(data.get(), texWidth, texHeight, gfxTextureFormat::RGB, gfxTexturePixelType::UBYTE);

    return target;
}
#else
gfxTextRenderedAtlas gfxTextFace::CreateRenderedAtlas(const epiWChar* atlasText, epiU32 fontSize) const
{
    gfxTextRenderedAtlas target;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // TODO: move to proper place

    PrepareFontMetrics(fontSize);

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
            return target;
        }

        if (slot->format != FT_GLYPH_FORMAT_BITMAP)
        {
            if (FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL))
            {
                // TODO: replace with a log
                epiAssert(false, "FT_Render_Glyph failed!");
                return target;
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
            return target;
        }

        if (slot->format != FT_GLYPH_FORMAT_BITMAP)
        {
            if (FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL))
            {
                // TODO: replace with a log
                epiAssert(false, "FT_Render_Glyph failed!");
                return target;
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

    return target;
}
#endif

EPI_NAMESPACE_END()
