#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Text/gfxTextRenderedAtlas.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/Text/gfxTextRendered.h"

EPI_NAMESPACE_BEGIN()

class gfxTextRenderedAtlasGlyph : public Object
{
EPI_GENREGION_BEGIN(gfxTextRenderedAtlasGlyph)
public:
    EPI_GENHIDDEN_gfxTextRenderedAtlasGlyph()

    constexpr static MetaTypeID TypeID{0x42a9985b};

    enum gfxTextRenderedAtlasGlyph_PIDs
    {
        PID_UV = 0x41d4f2f,
        PID_AspectRatio = 0xd8f95d9b,
        PID_COUNT = 2
    };

protected:
    epiRect2f m_UV;
    epiFloat m_AspectRatio{0.0f};

EPI_GENREGION_END(gfxTextRenderedAtlasGlyph)
};

class gfxTextRenderedAtlas : public gfxTextRendered
{
    friend class gfxTextFace;
EPI_GENREGION_BEGIN(gfxTextRenderedAtlas)
public:
    EPI_GENHIDDEN_gfxTextRenderedAtlas()

    constexpr static MetaTypeID TypeID{0x6de735c2};

    enum gfxTextRenderedAtlas_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxTextRenderedAtlas)

public:
    const gfxTextRenderedAtlasGlyph* GlyphOf(epiWChar ch) const;

private:
    std::map<epiWChar, gfxTextRenderedAtlasGlyph> m_CharMap;
};

EPI_NAMESPACE_END()
