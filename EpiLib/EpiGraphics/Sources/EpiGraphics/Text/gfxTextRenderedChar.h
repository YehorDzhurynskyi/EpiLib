#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Text/gfxTextRenderedGlyph.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/Text/gfxTextRendered.h"

EPI_NAMESPACE_BEGIN()

class gfxTextRenderedGlyph : public gfxTextRendered
{
EPI_GENREGION_BEGIN(gfxTextRenderedGlyph)
public:
    EPI_GENHIDDEN_gfxTextRenderedGlyph()

    constexpr static MetaTypeID TypeID{0xbb9ef44c};

    enum gfxTextRenderedGlyph_PIDs
    {
        PID_Bearing = 0x1c0b5150,
        PID_Size = 0x57f28b54,
        PID_Advance = 0x283c226f,
        PID_COUNT = 3
    };

protected:
    epiVec2u m_Bearing;
    epiVec2u m_Size;
    epiU32 m_Advance{0};

EPI_GENREGION_END(gfxTextRenderedGlyph)
};

class gfxTextRenderedABC : public Object
{
EPI_GENREGION_BEGIN(gfxTextRenderedABC)
public:
    EPI_GENHIDDEN_gfxTextRenderedABC()

    constexpr static MetaTypeID TypeID{0x23566643};

    enum gfxTextRenderedABC_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxTextRenderedABC)

public:
    const gfxTextRenderedGlyph* GlyphOf() const;

protected:
    // TODO: replace with epiMap
    std::map<epiWChar, gfxTextRenderedGlyph> m_ABC;
};

EPI_NAMESPACE_END()
