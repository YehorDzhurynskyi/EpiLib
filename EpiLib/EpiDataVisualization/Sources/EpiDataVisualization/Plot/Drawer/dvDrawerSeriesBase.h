#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Plot/Drawer/dvDrawerSeriesBase.hxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/Plot/ViewModel/dvVMSeriesBase.h"

#include "EpiGraphics/gfxContext.h"
#include "EpiGraphics/gfxDrawer.h"
#include "EpiGraphicsDriverCommon/gfxShaderProgram.h"

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
    void SceneBegin();
    void SceneEnd(const gfxCamera& camera);

protected:
    void DrawLineStrip(const epiVec2f& p, const Color& color, epiFloat z);

private:
    // TODO: maybe move it out from here
    // TODO: repair
    //gfxVertexArray m_VertexArrayLineStrip;
    // gfxVertexBuffer m_VertexBufferLineStrip;
    // gfxShaderProgram m_ShaderProgramLineStrip;

private:
    // gfxVertexBufferMapping m_VertexBufferMappingLineStrip;
};

EPI_NAMESPACE_END()
