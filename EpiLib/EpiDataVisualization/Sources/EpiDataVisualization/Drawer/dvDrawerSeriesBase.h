#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Drawer/dvDrawerSeriesBase.hxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/ViewModel/dvViewModelSeriesBase.h"

#include "EpiGraphics/gfxContext.h"
#include "EpiGraphics/gfxDrawer.h"
#include "EpiGraphics/gfxVertexArray.h"
#include "EpiGraphics/gfxVertexBuffer.h"
#include "EpiGraphics/gfxShaderProgram.h"

EPI_NAMESPACE_BEGIN()

class dvDrawerSeriesBase : public gfxDrawer
{
EPI_GENREGION_BEGIN(dvDrawerSeriesBase)

EPI_GENHIDDEN_dvDrawerSeriesBase()

public:
    constexpr static epiMetaTypeID TypeID{0xcf827047};

    enum dvDrawerSeriesBase_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(dvDrawerSeriesBase)

public:
    dvDrawerSeriesBase();

public:
    void Draw(gfxContext& ctx, const dvViewModelSeriesBase& series, const epiRect2f& worldFrame, const epiRect2f& uiFrame, epiFloat z = -50.0f);

    void SceneBegin();
    void SceneEnd(const gfxCamera& camera);

protected:
    virtual void Draw_Internal(gfxContext& ctx, const dvViewModelSeriesBase& series, const epiRect2f& worldFrame, const epiRect2f& uiFrame, epiFloat z) = 0;
    void DrawLineStrip(const epiVec2f& p, const Color& color, epiFloat z);

private:
    gfxVertexArray m_VertexArrayLineStrip;
    gfxVertexBuffer m_VertexBufferLineStrip;
    gfxShaderProgram m_ShaderProgramLineStrip;

private:
    gfxVertexBufferMapping m_VertexBufferMappingLineStrip;
};

EPI_NAMESPACE_END()
