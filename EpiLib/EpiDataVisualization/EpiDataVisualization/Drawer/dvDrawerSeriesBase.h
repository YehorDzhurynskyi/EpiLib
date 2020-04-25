#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Drawer/dvDrawerSeriesBase.hxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/ViewModel/dvViewModelSeriesBase.h"
#include "EpiDataVisualization/ViewModel/dvViewModelPlotBase.h"

#include "EpiUI/uiContext.h"

#include "EpiGraphics/gfxDrawer.h"
#include "EpiGraphics/gfxVertexArray.h"
#include "EpiGraphics/gfxVertexBuffer.h"
#include "EpiGraphics/gfxShaderProgram.h"

EPI_NAMESPACE_BEGIN()

class dvDrawerSeriesBase : public gfxDrawer
{
EPI_GENREGION_BEGIN(dvDrawerSeriesBase)
public:
    EPI_GENHIDDEN_dvDrawerSeriesBase()

    constexpr static MetaTypeID TypeID{0xcf827047};

    enum dvDrawerSeriesBase_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(dvDrawerSeriesBase)

public:
    dvDrawerSeriesBase();
    // TODO: rule of 6

public:
    void Draw(uiContext& uiContext, const dvViewModelPlotBase& plot, const dvViewModelSeriesBase& series);

    void SceneBegin();
    void SceneEnd(const gfxCamera& camera);

protected:
    virtual void Draw_Internal(uiContext& uiContext, const dvViewModelPlotBase& plot, const dvViewModelSeriesBase& series) = 0;
    void DrawLineStrip(const epiVec2f& p, const Color& color);

private:
    gfxVertexArray m_VertexArrayLineStrip;
    gfxVertexBuffer m_VertexBufferLineStrip;
    gfxShaderProgram m_ShaderProgramLineStrip;

private:
    gfxVertexBufferMapping m_VertexBufferMappingLineStrip;
};

EPI_NAMESPACE_END()
