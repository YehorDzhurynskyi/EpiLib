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
public:
    EPI_GENHIDDEN_gfxTextFace()

    constexpr static MetaTypeID TypeID{0xe2497b35};

    enum gfxTextFace_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxTextFace)

private:
    gfxTextFace() = default;

public:
    gfxTextFace(const gfxTextFace& rhs) = default;
    gfxTextFace& operator=(const gfxTextFace& rhs) = default;
    gfxTextFace(gfxTextFace&& rhs) = default;
    gfxTextFace& operator=(gfxTextFace&& rhs) = default;
    ~gfxTextFace();

public:
    void CreateRenderedGlyph(gfxTextRenderedGlyph& target, const epiWChar ch, epiS32 fontSize) const;
    void CreateRenderedABC(gfxTextRenderedABC& target, const epiWChar* abc, epiS32 fontSize) const;
    void CreateRenderedAtlas(gfxTextRenderedAtlas& target, const epiWChar* atlasText, epiS32 fontSize) const;

protected:
    FT_Face m_Face;
};

EPI_NAMESPACE_END()
