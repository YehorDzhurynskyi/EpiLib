#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Text/gfxTextFont.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

EPI_NAMESPACE_BEGIN()

class gfxTextFont : public Object
{
    friend class gfxTextManager;

EPI_GENREGION_BEGIN(gfxTextFont)
public:
    EPI_GENHIDDEN_gfxTextFont()

    constexpr static MetaTypeID TypeID{0x37c90880};

    enum gfxTextFont_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxTextFont)

private:
    gfxTextFont() = default;

public:
    gfxTextFont(const gfxTextFont& rhs) = default;
    gfxTextFont& operator=(const gfxTextFont& rhs) = default;
    gfxTextFont(gfxTextFont&& rhs) = default;
    gfxTextFont& operator=(gfxTextFont&& rhs) = default;
    ~gfxTextFont();

protected:
    FT_Face m_Face;
};

EPI_NAMESPACE_END()
