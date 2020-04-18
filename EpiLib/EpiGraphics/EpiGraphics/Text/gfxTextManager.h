#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Text/gfxTextManager.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

EPI_NAMESPACE_BEGIN()

class gfxTextFont;
class gfxTextManager final : public Object
{
EPI_GENREGION_BEGIN(gfxTextManager)
public:
    EPI_GENHIDDEN_gfxTextManager()

    constexpr static MetaTypeID TypeID{0x80c6f2c9};

    enum gfxTextManager_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxTextManager)

public:
    gfxTextManager();
    gfxTextManager(const gfxTextManager& rhs) = delete;
    gfxTextManager& operator=(const gfxTextManager& rhs) = delete;
    gfxTextManager(gfxTextManager&& rhs) = delete;
    gfxTextManager& operator=(gfxTextManager&& rhs) = delete;
    ~gfxTextManager();

public:
    std::unique_ptr<gfxTextFont> CreateFont(const epiChar* ttf);

protected:
    FT_Library m_FTLibrary;
};

EPI_NAMESPACE_END()
