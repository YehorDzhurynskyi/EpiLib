#include "EpiDataVisualization/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Drawer/dvDrawerSeriesBase.h"
#include "EpiDataVisualization/Drawer/dvDrawerSeriesBase.cxx"
EPI_GENREGION_END(include)

#include "EpiCore/Color.h"

#include <glad/glad.h> // TODO: remove (should be visible only for gfx)

namespace
{

using namespace epi;

const epiChar kShaderSourceLineStripVertex[] = R"(
#version 400 core

layout(location = 0) in vec2 a_position;
layout(location = 1) in vec4 a_color_tint;

out vec4 color_tint;

uniform mat4 u_view_projection;

void main(void)
{
    gl_Position = u_view_projection * vec4(a_position, 0.0, 1.0);
    color_tint = a_color_tint;
}
)";

const epiChar kShaderSourceLineStripPixel[] = R"(
#version 400 core

in vec4 color_tint;

out vec4 fragcolor;

void main(void)
{
    fragcolor = color_tint;
}
)";

gfxShaderProgram CreateLinesProgram()
{
    gfxShader vertex;
    gfxShader pixel;

    vertex.CreateFromSource(kShaderSourceLineStripVertex, gfxShaderType::Vertex);
    pixel.CreateFromSource(kShaderSourceLineStripPixel, gfxShaderType::Pixel);

    gfxShaderProgram program;

    program.ShaderAttach(vertex);
    program.ShaderAttach(pixel);

    program.Build();

    return program;
}

const epiU32 kMaxLineVerticesCount = 4096;
struct VertexLine
{
    epiVec2f Position;
    Color ColorTint;
};

}

EPI_NAMESPACE_BEGIN()

dvDrawerSeriesBase::dvDrawerSeriesBase(const gfxCamera& camera)
    : super(camera)
    , m_VertexBufferMappingLineStrip(m_VertexBufferLineStrip)
{
    m_VertexBufferLineStrip.Create(nullptr, sizeof(VertexLine) * kMaxLineVerticesCount, gfxVertexBufferUsage::DynamicDraw);

    {
        gfxBindableScoped scope(m_VertexArrayLineStrip, m_VertexBufferLineStrip);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(VertexLine), (void*)offsetof(VertexLine, Position));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(VertexLine), (void*)offsetof(VertexLine, ColorTint));
    }

    m_ShaderProgramLineStrip = CreateLinesProgram();
}

void dvDrawerSeriesBase::Draw(const dvPlotBase& plot, const dvSeriesBase& series)
{
    Draw_Internal(plot, series);
}

void dvDrawerSeriesBase::Draw_Internal(const dvPlotBase& plot, const dvSeriesBase& series)
{
}

void dvDrawerSeriesBase::SceneBegin()
{
    super::SceneBegin();

    m_VertexBufferMappingLineStrip.Map(gfxVertexBufferMapAccess::WriteOnly);
}

void dvDrawerSeriesBase::SceneEnd()
{
    super::SceneEnd();

    const epiSize_t lineStripVerticesCount = m_VertexBufferMappingLineStrip.UnMap() / sizeof(VertexLine);

    {
        gfxBindableScoped scope(m_ShaderProgramLineStrip, m_VertexArrayLineStrip);

        const GLint locationVP = glGetUniformLocation(m_ShaderProgramLineStrip.GetProgramID(), "u_view_projection");
        const epiMat4x4f& VP = m_Camera.GetProjectionMatrix() * m_Camera.GetViewMatrix();
        glUniformMatrix4fv(locationVP, 1, GL_FALSE, &VP[0][0]);

        glDrawArrays(GL_LINE_STRIP, 0, lineStripVerticesCount);
    }
}

EPI_NAMESPACE_END()
