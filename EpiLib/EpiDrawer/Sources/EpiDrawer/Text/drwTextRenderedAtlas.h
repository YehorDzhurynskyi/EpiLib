#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDrawer/Text/drwTextRenderedAtlas.hxx"
EPI_GENREGION_END(include)

#include "EpiDrawer/Text/drwTextRendered.h"

EPI_NAMESPACE_BEGIN()

class drwTextRenderedAtlasGlyph : public Object
{
EPI_GENREGION_BEGIN(drwTextRenderedAtlasGlyph)

EPI_GENHIDDEN_drwTextRenderedAtlasGlyph()

public:
    constexpr static epiMetaTypeID TypeID{0x172914e2};

    enum drwTextRenderedAtlasGlyph_PIDs
    {
        PID_UV = 0x41d4f2f,
        PID_AspectRatio = 0xd8f95d9b,
        PID_Height = 0xf2e1e039,
        PID_Advance = 0x283c226f,
        PID_Bearing = 0x1c0b5150,
        PID_COUNT = 5
    };

protected:
    epiRect2f m_UV{};
    epiFloat m_AspectRatio{0.0f};
    epiFloat m_Height{0.0f};
    epiVec2f m_Advance{};
    epiVec2f m_Bearing{};

EPI_GENREGION_END(drwTextRenderedAtlasGlyph)
};

class drwTextRenderedAtlas : public drwTextRendered
{
EPI_GENREGION_BEGIN(drwTextRenderedAtlas)

EPI_GENHIDDEN_drwTextRenderedAtlas()

public:
    constexpr static epiMetaTypeID TypeID{0xce1bea88};

    enum drwTextRenderedAtlas_PIDs
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

EPI_GENREGION_END(drwTextRenderedAtlas)

public:
    friend class drwTextFace; // TODO: refactor

public:
    const drwTextRenderedAtlasGlyph* GlyphOf(epiWChar ch) const;

private:
    std::map<epiWChar, drwTextRenderedAtlasGlyph> m_CharMap;
};

EPI_NAMESPACE_END()
