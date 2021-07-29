#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDrawer/Text/drwTextFace.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"
#include "EpiCore/Color.h"

#include <ft2build.h>
#include FT_FREETYPE_H

EPI_NAMESPACE_BEGIN()

class drwTextRenderedGlyph;
class drwTextRenderedABC;
class drwTextRenderedAtlas;
class drwTextFace : public Object
{
EPI_GENREGION_BEGIN(drwTextFace)

EPI_GENHIDDEN_drwTextFace()

public:
    constexpr static epiMetaTypeID TypeID{0x8a57f377};

    enum drwTextFace_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(drwTextFace)

public:
    friend class drwTextManager; // TODO: refactor

private:
    drwTextFace() = default;

public:
    drwTextFace(const drwTextFace& rhs) = delete;
    drwTextFace& operator=(const drwTextFace& rhs) = delete;
    drwTextFace(drwTextFace&& rhs) = default;
    drwTextFace& operator=(drwTextFace&& rhs) = default;
    ~drwTextFace();

public:
    drwTextRenderedGlyph CreateRenderedGlyph(const epiWChar ch, epiU32 fontSize) const;
    drwTextRenderedABC CreateRenderedABC(const epiWChar* abc, epiU32 fontSize) const;
    drwTextRenderedAtlas CreateRenderedAtlas(const epiWChar* atlasText, epiU32 fontSize) const;

protected:
    void PrepareFontMetrics(epiU32 fontSize) const;

protected:
    FT_Face m_Face;
};

EPI_NAMESPACE_END()
