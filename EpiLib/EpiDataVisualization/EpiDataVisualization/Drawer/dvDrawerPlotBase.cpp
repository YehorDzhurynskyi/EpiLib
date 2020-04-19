#include "EpiDataVisualization/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Drawer/dvDrawerPlotBase.h"
#include "EpiDataVisualization/Drawer/dvDrawerPlotBase.cxx"
EPI_GENREGION_END(include)

#include <glad/glad.h> // TODO: remove (should be available only from gfx)

namespace
{

const epiChar kShaderSourceLineVertex[] = R"(
#version 400 core

layout(location = 0) in vec2 a_position;
layout(location = 1) in vec4 a_color_tint;

out vec4 color_tint;

uniform mat4 u_view_projection;

void main(void)
{
    gl_Position = u_mvp * vec4(a_position, 0.0, 1.0);
    color_tint = a_color_tint;
}
)";

const epiChar kShaderSourceLinePixel[] = R"(
#version 400 core

in vec4 color_tint;

out vec4 fragcolor;

void main(void)
{
    fragcolor = color_tint;
}
)";

const epiSize_t kMaxLineCount = 512;
const epiU32 kMinGridLineCount = 6;
const epiU32 kMaxGridLineCount = 10;

}

EPI_NAMESPACE_BEGIN()

dvDrawerPlotBase::dvDrawerPlotBase(const dvPlotBase& plot)
    : m_PlotBase(plot)
    , m_MappingLines(m_VertexBufferLines)
{
    m_VertexBufferLines.Create(nullptr, sizeof(dvDrawerPlotLineVertex) * 2 * kMaxLineCount, gfxVertexBufferUsage::DynamicDraw);

    gfxBindableScoped scope(m_VAO, m_VertexBufferLines);

    // TODO: move to gfx
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(dvDrawerPlotLineVertex), (void*)offsetof(dvDrawerPlotLineVertex, Position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(dvDrawerPlotLineVertex), (void*)offsetof(dvDrawerPlotLineVertex, ColorTint));

    gfxShader vertex;
    gfxShader pixel;

    vertex.CreateFromSource(kShaderSourceLineVertex, gfxShaderType::Vertex);
    pixel.CreateFromSource(kShaderSourceLinePixel, gfxShaderType::Pixel);

    m_ShaderProgram.ShaderAttach(vertex);
    m_ShaderProgram.ShaderAttach(pixel);

    m_ShaderProgram.Build();
}

void dvDrawerPlotBase::Draw(const gfxCameraOrtho& uiCamera)
{
    m_MappingLines.Map(gfxVertexBufferMapAccess::WriteOnly);
    Draw_Internal(uiCamera);
    const epiSize_t size = m_MappingLines.UnMap();

    const epiMat4x4f& projMat = uiCamera.GetProjectionMatrix();
    const epiMat4x4f& viewMat = uiCamera.GetViewMatrix();
    const epiMat4x4f& VP = projMat * viewMat;

    gfxBindableScoped scope(m_VAO, m_ShaderProgram);

    glUniformMatrix4fv(glGetUniformLocation(m_ShaderProgram.GetProgramID(), "u_view_projection"), 1, GL_FALSE, &VP[0][0]);

    glDrawArrays(GL_LINES, 0, size);
}

void dvDrawerPlotBase::Draw_Internal(const gfxCameraOrtho& uiCamera)
{
    const epiRect2f& clipbox = m_PlotBase.GetClipBox();

    const epiFloat h = clipbox.Top - clipbox.Bottom;
    const epiFloat w = clipbox.Right - clipbox.Left;
    const epiS32 order = static_cast<epiS32>(std::log10f(w));

    epiU32 nLines = w / std::powf(10.0f, order);
    while (nLines < kMaxGridLineCount)
    {
        if (nLines >= kMinGridLineCount)
        {
            break;
        }
        nLines *= 2;
    }
    nLines = std::clamp(nLines, kMinGridLineCount, kMaxGridLineCount);

    const epiFloat xOffset = 0.0f;
    const epiFloat stride = w / nLines;
    epiFloat x = xOffset;

    for (epiU32 i = 0; i < nLines; ++i)
    {
        epiVec2f p(x, 0.0f);

        DrawLine(p, p + epiVec2f(0.0f, h), Color::kDarkGray);
        x += stride;
    }
}

void dvDrawerPlotBase::DrawLine(const epiVec2f& p1, const epiVec2f& p2, const Color& color)
{
    dvDrawerPlotLineVertex& vertex1 = m_MappingLines.Push();
    vertex1.Position = p1;
    vertex1.ColorTint = color;

    dvDrawerPlotLineVertex& vertex2 = m_MappingLines.Push();
    vertex2.Position = p2;
    vertex2.ColorTint = color;
}

EPI_NAMESPACE_END()
