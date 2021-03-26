#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxDrawerText.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxDrawer.h"

#include "EpiGraphics/Text/gfxTextRenderedAtlas.h"
#include "EpiGraphics/Text/gfxTextFace.h"

#include "EpiGraphicsDriverCommon/gfxVertexArray.h"
#include "EpiGraphicsDriverCommon/gfxVertexBuffer.h"
#include "EpiGraphicsDriverCommon/gfxShaderProgram.h"

#include "EpiCore/Color.h"

EPI_NAMESPACE_BEGIN()

class gfxTextFace;
class gfxDrawerText : public gfxDrawer
{
EPI_GENREGION_BEGIN(gfxDrawerText)

EPI_GENHIDDEN_gfxDrawerText()

public:
    constexpr static epiMetaTypeID TypeID{0xe2261870};

    enum gfxDrawerText_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxDrawerText)

public:
    gfxDrawerText();

public:
    void DrawText(const epiWChar* text, const epiVec2f& position, epiFloat textHeight, const Color& color = Color::kDarkGray, epiFloat z = -15.0f);

    void SceneBegin();
    void SceneEnd(const gfxCamera& camera);

    // TODO: move to proper place
    void CreateAtlas(const gfxTextFace& face, epiU32 fontSize);
    void CreateAtlas(const gfxTextFace& face, epiU32 fontSize, const epiWChar* abc);

protected:
    // TODO: move to proper place
    gfxTextRenderedAtlas m_TextAtlas;

private:
    gfxVertexArray m_VertexArrayText;
    gfxVertexBuffer m_VertexBufferText;
    gfxShaderProgram m_ShaderProgramText;

private:
    gfxVertexBufferMapping m_VertexBufferMappingText;
};

EPI_NAMESPACE_END()
