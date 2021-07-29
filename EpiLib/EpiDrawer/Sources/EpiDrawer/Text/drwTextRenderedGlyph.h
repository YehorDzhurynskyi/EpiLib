#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDrawer/Text/drwTextRenderedGlyph.hxx"
EPI_GENREGION_END(include)

#include "EpiDrawer/Text/drwTextRendered.h"

EPI_NAMESPACE_BEGIN()

class drwTextRenderedGlyph : public drwTextRendered
{
    friend class gfxTextFace;
EPI_GENREGION_BEGIN(drwTextRenderedGlyph)

EPI_GENHIDDEN_drwTextRenderedGlyph()

public:
    constexpr static epiMetaTypeID TypeID{0x17a7eb3f};

    enum drwTextRenderedGlyph_PIDs
    {
        PID_Bearing = 0x1c0b5150,
        PID_Size = 0x57f28b54,
        PID_Advance = 0x283c226f,
        PID_COUNT = 3
    };

protected:
    epiVec2u m_Bearing{};
    epiVec2u m_Size{};
    epiU32 m_Advance{0};

EPI_GENREGION_END(drwTextRenderedGlyph)
};

class drwTextRenderedABC : public Object
{
EPI_GENREGION_BEGIN(drwTextRenderedABC)

EPI_GENHIDDEN_drwTextRenderedABC()

public:
    constexpr static epiMetaTypeID TypeID{0x236362a9};

    enum drwTextRenderedABC_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(drwTextRenderedABC)

public:
    friend class drwTextFace; // TODO: refactor

public:
    drwTextRenderedGlyph* GlyphOf(epiWChar ch);

protected:
    // TODO: replace with epiMap
    std::map<epiWChar, drwTextRenderedGlyph> m_ABC;
};

EPI_NAMESPACE_END()
