#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxDrawerPrimitive.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxDrawer.h"
#include "EpiGraphics/Text/gfxTextRenderedAtlas.h"
#include "EpiGraphics/Text/gfxTextRenderedGlyph.h"
#include "EpiGraphics/Text/gfxTextFace.h"
#include "EpiGraphics/gfxVertexArray.h"
#include "EpiGraphics/gfxVertexBuffer.h"
#include "EpiGraphics/gfxShaderProgram.h"

#include "EpiCore/Color.h"

EPI_NAMESPACE_BEGIN()

// TODO: set as struct in epi file
class gfxDrawerPrimitive : public gfxDrawer
{
EPI_GENREGION_BEGIN(gfxDrawerPrimitive)
public:
    EPI_GENHIDDEN_gfxDrawerPrimitive()

    constexpr static MetaTypeID TypeID{0x47f3f776};

    enum gfxDrawerPrimitive_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxDrawerPrimitive)

public:
    gfxDrawerPrimitive();
    // TODO: rule of 6

public:
    void DrawLine(const epiVec2f& p1, const epiVec2f& p2, const Color& color = Color::kLightBlue, epiFloat z = -100.0f);
    void DrawQuad(const epiRect2f& rect, const Color& color = Color::kLightBlue, epiFloat z = -100.0f);

    void SceneBegin();
    void SceneEnd(const gfxCamera& camera);

private:
    gfxVertexArray m_VertexArrayLines;
    gfxVertexBuffer m_VertexBufferLines;
    gfxShaderProgram m_ShaderProgramLines;

    gfxVertexArray m_VertexArrayQuads;
    gfxVertexBuffer m_VertexBufferQuads;
    gfxShaderProgram m_ShaderProgramQuads;

private:
    gfxVertexBufferMapping m_VertexBufferMappingLines;
    gfxVertexBufferMapping m_VertexBufferMappingQuads;
};

EPI_NAMESPACE_END()
