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
    gfxDrawerPrimitive(const gfxCamera& camera);

public:
    void DrawLine(const epiVec2f& p1, const epiVec2f& p2, const Color& color = Color::kLightBlue);

    void SceneBegin() override;
    void SceneEnd() override;

private:
    gfxVertexArray m_VertexArrayLines;
    gfxVertexBuffer m_VertexBufferLines;
    gfxShaderProgram m_ShaderProgramLines;

private:
    gfxVertexBufferMapping m_VertexBufferMappingLines;
};

EPI_NAMESPACE_END()
