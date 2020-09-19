EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Plot/Drawer/dvDrawerSeriesBase.h"
#include "EpiDataVisualization/Plot/Drawer/dvDrawerSeriesBase.cxx"
EPI_GENREGION_END(include)

#include "EpiCore/Color.h"

#include <glad/glad.h> // TODO: remove (should be visible only for gfx)

namespace
{

EPI_NAMESPACE_USING()

const epiChar kShaderSourceLineStripVertex[] = R"(
#version 400 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color_tint;

out vec4 color_tint;

uniform mat4 u_view_projection;

void main(void)
{
    gl_Position = u_view_projection * vec4(a_position, 1.0);
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

gfxShaderProgram CreateProgramLineStrip()
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

const epiU32 kMaxLineStripVerticesCount = 16 * 1024;
struct VertexLineStip
{
    epiVec3f Position;
    epiVec4f ColorTint;
};

}

EPI_NAMESPACE_BEGIN()

dvDrawerSeriesBase::dvDrawerSeriesBase()
    : m_VertexBufferMappingLineStrip(m_VertexBufferLineStrip)
{
    m_VertexBufferLineStrip.Create(nullptr, sizeof(VertexLineStip) * kMaxLineStripVerticesCount, gfxVertexBufferUsage::DynamicDraw);

    {
        gfxBindableScoped scope(m_VertexArrayLineStrip, m_VertexBufferLineStrip);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexLineStip), (void*)offsetof(VertexLineStip, Position));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(VertexLineStip), (void*)offsetof(VertexLineStip, ColorTint));
    }

    m_ShaderProgramLineStrip = CreateProgramLineStrip();
}

void dvDrawerSeriesBase::Draw(gfxContext& ctx, const dvVMSeriesBase& series, const epiRect2f& worldFrame, const epiRect2f& uiFrame, epiFloat z)
{
    Draw_Internal(ctx, series, worldFrame, uiFrame, z);
}

void dvDrawerSeriesBase::DrawLineStrip(const epiVec2f& p, const Color& color, epiFloat z)
{
    VertexLineStip& v = m_VertexBufferMappingLineStrip.PushBack<VertexLineStip>();
    v.Position.x = p.x;
    v.Position.y = p.y;
    v.Position.z = z;
    v.ColorTint = color.GetColor();
}

void dvDrawerSeriesBase::SceneBegin()
{
    m_VertexBufferMappingLineStrip.Map(gfxVertexBufferMapAccess::Write);
}

void dvDrawerSeriesBase::SceneEnd(const gfxCamera& camera)
{
    const epiSize_t lineStripVerticesCount = m_VertexBufferMappingLineStrip.UnMap() / sizeof(VertexLineStip);

    {
        gfxBindableScoped scope(m_ShaderProgramLineStrip, m_VertexArrayLineStrip);

        const GLint locationVP = glGetUniformLocation(m_ShaderProgramLineStrip.GetProgramID(), "u_view_projection");
        const epiMat4x4f& VP = camera.GetProjectionMatrix() * camera.GetViewMatrix();
        glUniformMatrix4fv(locationVP, 1, GL_FALSE, &VP[0][0]);

        glLineWidth(2.0f);
        glDrawArrays(GL_LINE_STRIP, 0, lineStripVerticesCount);
        glLineWidth(1.0f);
    }
}

EPI_NAMESPACE_END()
