#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxDrawerPrimitive.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxDrawer.h"
#include "EpiGraphics/Text/gfxTextRenderedAtlas.h"
#include "EpiGraphics/Text/gfxTextRenderedGlyph.h"
#include "EpiGraphics/Text/gfxTextFace.h"
#include "EpiGraphicsDriverCommon/gfxShaderProgram.h"

#include "EpiCore/Color.h"

EPI_NAMESPACE_BEGIN()

// TODO: set as struct in epi file
class gfxDrawerPrimitive : public gfxDrawer
{
EPI_GENREGION_BEGIN(gfxDrawerPrimitive)

EPI_GENHIDDEN_gfxDrawerPrimitive()

public:
    constexpr static epiMetaTypeID TypeID{0x47f3f776};

    enum gfxDrawerPrimitive_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxDrawerPrimitive)

public:
    gfxDrawerPrimitive();

public:
    void DrawLine(const epiVec2f& p1, const epiVec2f& p2, const Color& color, epiFloat z = -100.0f);
    void DrawLine(const epiVec2f& p1, const epiVec2f& p2, const Color& color1, const Color& color2, epiFloat z = -100.0f);
    void DrawQuad(const epiRect2f& rect, const Color& color, epiFloat z = -100.0f);
    void DrawQuad(const epiRect2f& rect, const Color& color1, const Color& color2, epiFloat z = -100.0f);

    void SceneBegin();
    void SceneEnd(const gfxCamera& camera);

private:
    // TODO: repair
    //gfxVertexArray m_VertexArrayLines;
    //gfxVertexBuffer m_VertexBufferLines;
    //gfxShaderProgram m_ShaderProgramLines;

    //gfxVertexArray m_VertexArrayQuads;
    //gfxVertexBuffer m_VertexBufferQuads;
    //gfxShaderProgram m_ShaderProgramQuads;

private:
    //gfxVertexBufferMapping m_VertexBufferMappingLines;
    //gfxVertexBufferMapping m_VertexBufferMappingQuads;
};

EPI_NAMESPACE_END()
