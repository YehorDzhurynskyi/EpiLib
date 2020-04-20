#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxDrawer.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"
#include "EpiCore/Color.h"
#include "EpiGraphics/gfxContext.h"
#include "EpiGraphics/Text/gfxTextRenderedAtlas.h"
#include "EpiGraphics/Text/gfxTextRenderedGlyph.h"
#include "EpiGraphics/Text/gfxTextFace.h"
#include "EpiGraphics/gfxVertexArray.h"
#include "EpiGraphics/gfxVertexBuffer.h"
#include "EpiGraphics/gfxShaderProgram.h"

EPI_NAMESPACE_BEGIN()

// TODO: set as struct in epi file
class gfxDrawer : public Object
{
EPI_GENREGION_BEGIN(gfxDrawer)
public:
    EPI_GENHIDDEN_gfxDrawer()

    constexpr static MetaTypeID TypeID{0x74765527};

    enum gfxDrawer_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxDrawer)

public:
    gfxDrawer(const gfxTextFace& face, const epiWChar* abc, const gfxCamera& camera);

public:
    void DrawText(const epiWChar* text, const epiVec2f& position, epiFloat textHeight, const Color& color = Color::kDarkGray);
    void DrawLine(const epiVec2f& p1, const epiVec2f& p2, const Color& color = Color::kLightBlue);

    void SceneBegin();
    void SceneEnd();

private:
    gfxVertexArray m_VertexArrayText;
    gfxVertexArray m_VertexArrayLines;

    gfxVertexBuffer m_VertexBufferText;
    gfxVertexBuffer m_VertexBufferLines;

    gfxShaderProgram m_ShaderProgramText;
    gfxShaderProgram m_ShaderProgramLines;

private:
    gfxVertexBufferMapping m_VertexBufferMappingText;
    gfxVertexBufferMapping m_VertexBufferMappingLines;

private:
    gfxTextRenderedAtlas m_TextAtlas;

private:
    const gfxCamera& m_Camera;
};

EPI_NAMESPACE_END()
