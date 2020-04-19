#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Drawer/dvDrawerPlotBase.hxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/Plot/dvPlotBase.h"
#include "EpiGraphics/gfxDrawer.h"
#include "EpiGraphics/gfxVertexBuffer.h"
#include "EpiGraphics/gfxShaderProgram.h"

EPI_NAMESPACE_BEGIN()

struct dvDrawerPlotLineVertex
{
    epiVec2f Position;
    Color ColorTint;
};

class dvDrawerPlotBase : public gfxDrawer
{
EPI_GENREGION_BEGIN(dvDrawerPlotBase)
public:
    EPI_GENHIDDEN_dvDrawerPlotBase()

    constexpr static MetaTypeID TypeID{0x87a7d6ca};

    enum dvDrawerPlotBase_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(dvDrawerPlotBase)

public:
    dvDrawerPlotBase(const dvPlotBase& plot);

    void Draw(const gfxCameraOrtho& uiCamera);

protected:
    virtual void Draw_Internal(const gfxCameraOrtho& uiCamera);
    void DrawLine(const epiVec2f& p1, const epiVec2f& p2, const Color& color);

protected:
    const dvPlotBase& m_PlotBase; // TODO: move to epi

    gfxVertexArray m_VAO;
    gfxVertexBuffer m_VertexBufferLines;
    gfxShaderProgram m_ShaderProgram;

private:
    gfxVertexBufferMapping<dvDrawerPlotLineVertex> m_MappingLines;
};

EPI_NAMESPACE_END()
