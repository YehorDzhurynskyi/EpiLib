#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDrawer/drwDrawerPrimitive.hxx"
EPI_GENREGION_END(include)

#include "EpiDrawer/drwDrawer.h"

#include "EpiDrawer/Camera/drwCamera.h"

#include "EpiDrawer/Text/drwTextRenderedAtlas.h"
#include "EpiDrawer/Text/drwTextRenderedGlyph.h"
#include "EpiDrawer/Text/drwTextFace.h"

#include "EpiGraphicsDriverCommon/gfxShaderModule.h"

#include "EpiCore/Color.h"

EPI_NAMESPACE_BEGIN()

// TODO: set as struct in epi file
class drwDrawerPrimitive : public drwDrawer
{
EPI_GENREGION_BEGIN(drwDrawerPrimitive)

EPI_GENHIDDEN_drwDrawerPrimitive()

public:
    constexpr static epiMetaTypeID TypeID{0x47c6f39c};

    enum drwDrawerPrimitive_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(drwDrawerPrimitive)

public:
    drwDrawerPrimitive();

public:
    void DrawLine(const epiVec2f& p1, const epiVec2f& p2, const Color& color, epiFloat z = -100.0f);
    void DrawLine(const epiVec2f& p1, const epiVec2f& p2, const Color& color1, const Color& color2, epiFloat z = -100.0f);
    void DrawQuad(const epiRect2f& rect, const Color& color, epiFloat z = -100.0f);
    void DrawQuad(const epiRect2f& rect, const Color& color1, const Color& color2, epiFloat z = -100.0f);

    void SceneBegin();
    void SceneEnd(const drwCamera& camera);

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
