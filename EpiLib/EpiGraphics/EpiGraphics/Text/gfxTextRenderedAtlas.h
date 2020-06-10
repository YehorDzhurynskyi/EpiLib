#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Text/gfxTextRenderedAtlas.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/Text/gfxTextRendered.h"

EPI_NAMESPACE_BEGIN()

class gfxTextRenderedAtlasGlyph : public Object
{
EPI_GENREGION_BEGIN(gfxTextRenderedAtlasGlyph)

EPI_GENHIDDEN_gfxTextRenderedAtlasGlyph()

public:
    constexpr static MetaTypeID TypeID{0x42a9985b};

    enum gfxTextRenderedAtlasGlyph_PIDs
    {
        PID_UV = 0x41d4f2f,
        PID_AspectRatio = 0xd8f95d9b,
        PID_Height = 0xf2e1e039,
        PID_Advance = 0x283c226f,
        PID_Bearing = 0x1c0b5150,
        PID_COUNT = 5
    };

protected:
    epiRect2f m_UV;
    epiFloat m_AspectRatio{0.0f};
    epiFloat m_Height{0.0f};
    epiVec2f m_Advance;
    epiVec2f m_Bearing;

EPI_GENREGION_END(gfxTextRenderedAtlasGlyph)
};

class gfxTextRenderedAtlas : public gfxTextRendered
{
    friend class gfxTextFace;
EPI_GENREGION_BEGIN(gfxTextRenderedAtlas)

EPI_GENHIDDEN_gfxTextRenderedAtlas()

public:
    constexpr static MetaTypeID TypeID{0x6de735c2};

    enum gfxTextRenderedAtlas_PIDs
    {
        PID_Descender = 0xcde8cb3b,
        PID_Ascender = 0xb0813e5b,
        PID_Height = 0xf2e1e039,
        PID_COUNT = 3
    };

protected:
    epiFloat m_Descender{0.0f};
    epiFloat m_Ascender{0.0f};
    epiFloat m_Height{0.0f};

EPI_GENREGION_END(gfxTextRenderedAtlas)

public:
    const gfxTextRenderedAtlasGlyph* GlyphOf(epiWChar ch) const;

private:
    std::map<epiWChar, gfxTextRenderedAtlasGlyph> m_CharMap;
};

EPI_NAMESPACE_END()
