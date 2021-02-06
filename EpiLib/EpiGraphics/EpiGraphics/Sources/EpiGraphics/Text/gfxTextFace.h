#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Text/gfxTextFace.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"
#include "EpiCore/Color.h"

#include <ft2build.h>
#include FT_FREETYPE_H

EPI_NAMESPACE_BEGIN()

class gfxTextRenderedGlyph;
class gfxTextRenderedABC;
class gfxTextRenderedAtlas;
class gfxTextFace : public Object
{
    friend class gfxTextManager;
EPI_GENREGION_BEGIN(gfxTextFace)

EPI_GENHIDDEN_gfxTextFace()

public:
    constexpr static epiMetaTypeID TypeID{0xe2497b35};

    enum gfxTextFace_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxTextFace)

private:
    gfxTextFace() = default;

public:
    gfxTextFace(const gfxTextFace& rhs) = delete;
    gfxTextFace& operator=(const gfxTextFace& rhs) = delete;
    gfxTextFace(gfxTextFace&& rhs) = default;
    gfxTextFace& operator=(gfxTextFace&& rhs) = default;
    ~gfxTextFace();

public:
    gfxTextRenderedGlyph CreateRenderedGlyph(const epiWChar ch, epiU32 fontSize) const;
    gfxTextRenderedABC CreateRenderedABC(const epiWChar* abc, epiU32 fontSize) const;
    gfxTextRenderedAtlas CreateRenderedAtlas(const epiWChar* atlasText, epiU32 fontSize) const;

protected:
    void PrepareFontMetrics(epiU32 fontSize) const;

protected:
    FT_Face m_Face;
};

EPI_NAMESPACE_END()
