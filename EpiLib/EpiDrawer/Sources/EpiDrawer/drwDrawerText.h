#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDrawer/drwDrawerText.hxx"
EPI_GENREGION_END(include)

#include "EpiDrawer/drwDrawer.h"

#include "EpiDrawer/Camera/drwCamera.h"

#include "EpiDrawer/Text/drwTextRenderedAtlas.h"
#include "EpiDrawer/Text/drwTextFace.h"

#include "EpiGraphics/gfxShaderModule.h"

#include "EpiCore/Color.h"

EPI_NAMESPACE_BEGIN()

class gfxTextFace;
class drwDrawerText : public drwDrawer
{
EPI_GENREGION_BEGIN(drwDrawerText)

EPI_GENHIDDEN_drwDrawerText()

public:
    constexpr static epiMetaTypeID TypeID{0xc30a56fb};

    enum drwDrawerText_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(drwDrawerText)

public:
    drwDrawerText();

public:
    void DrawText(const epiWChar* text, const epiVec2f& position, epiFloat textHeight, const Color& color = Color::kDarkGray, epiFloat z = -15.0f);

    void SceneBegin();
    void SceneEnd(const drwCamera& camera);

    // TODO: move to proper place
    void CreateAtlas(const drwTextFace& face, epiU32 fontSize);
    void CreateAtlas(const drwTextFace& face, epiU32 fontSize, const epiWChar* abc);

protected:
    // TODO: move to proper place
    drwTextRenderedAtlas m_TextAtlas;

private:
    // TODO: repair
    //gfxVertexArray m_VertexArrayText;
    // gfxVertexBuffer m_VertexBufferText;
    //gfxShaderProgram m_ShaderProgramText;

private:
    // gfxVertexBufferMapping m_VertexBufferMappingText;
};

EPI_NAMESPACE_END()
