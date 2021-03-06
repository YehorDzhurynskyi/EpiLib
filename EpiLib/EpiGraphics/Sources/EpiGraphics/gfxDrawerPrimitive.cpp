EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxDrawerPrimitive.h"
#include "EpiGraphics/gfxDrawerPrimitive.cxx"
EPI_GENREGION_END(include)

#include <glad/glad.h>

namespace
{

EPI_NAMESPACE_USING()

const epiChar kShaderSourceLinesVertex[] = R"(
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

const epiChar kShaderSourceLinesPixel[] = R"(
#version 400 core

in vec4 color_tint;

out vec4 fragcolor;

void main(void)
{
    fragcolor = color_tint;
}
)";

gfxShaderProgram CreateProgramLines()
{
    gfxShader vertex;
    gfxShader pixel;

    vertex.CreateFromSource(kShaderSourceLinesVertex, gfxShaderType::Vertex);
    pixel.CreateFromSource(kShaderSourceLinesPixel, gfxShaderType::Pixel);

    gfxShaderProgram program;

    program.ShaderAttach(vertex);
    program.ShaderAttach(pixel);

    program.Build();

    return program;
}

const epiU32 kMaxLineCount = 6'000'000u; // TODO: =) reduce
struct VertexLine
{
    epiVec3f Position;
    epiVec4f ColorTint;
};

const epiChar kShaderSourceQuadVertex[] = R"(
#version 400 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;

uniform mat4 u_view_projection;

out vec4 color;

void main(void)
{
    gl_Position = u_view_projection * vec4(a_position, 1.0);
    color = a_color;
}
)";

const epiChar kShaderSourceQuadPixel[] = R"(
#version 400 core

in vec4 color;

out vec4 fragcolor;

void main(void)
{
    fragcolor = color;
}
)";

gfxShaderProgram CreateProgramQuad()
{
    gfxShader vertex;
    gfxShader pixel;

    vertex.CreateFromSource(kShaderSourceQuadVertex, gfxShaderType::Vertex);
    pixel.CreateFromSource(kShaderSourceQuadPixel, gfxShaderType::Pixel);

    gfxShaderProgram program;

    program.ShaderAttach(vertex);
    program.ShaderAttach(pixel);

    program.Build();

    return program;
}

const epiU32 kMaxQuadCount = 1'000'000u; // TODO: =) reduce
struct VertexQuad
{
    epiVec3f Position;
    epiVec4f ColorTint;
};

}

EPI_NAMESPACE_BEGIN()

gfxDrawerPrimitive::gfxDrawerPrimitive()
    : m_VertexBufferMappingLines(m_VertexBufferLines)
    , m_VertexBufferMappingQuads(m_VertexBufferQuads)
{
    m_VertexBufferLines.Create(nullptr, sizeof(VertexLine) * 2 * kMaxLineCount, gfxVertexBufferUsage::DynamicDraw);

    {
        gfxBindableScoped scope(m_VertexArrayLines, m_VertexBufferLines);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexLine), (void*)offsetof(VertexLine, Position));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(VertexLine), (void*)offsetof(VertexLine, ColorTint));
    }

    m_ShaderProgramLines = CreateProgramLines();

    m_VertexBufferQuads.Create(nullptr, sizeof(VertexQuad) * 6 * kMaxQuadCount, gfxVertexBufferUsage::DynamicDraw);

    {
        gfxBindableScoped scope(m_VertexArrayQuads, m_VertexBufferQuads);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexQuad), (void*)offsetof(VertexQuad, Position));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(VertexQuad), (void*)offsetof(VertexQuad, ColorTint));
    }

    m_ShaderProgramQuads = CreateProgramQuad();
}

void gfxDrawerPrimitive::DrawLine(const epiVec2f& p1, const epiVec2f& p2, const Color& color, epiFloat z)
{
    DrawLine(p1, p2, color, color, z);
}

void gfxDrawerPrimitive::DrawLine(const epiVec2f& p1, const epiVec2f& p2, const Color& color1, const Color& color2, epiFloat z)
{
    VertexLine& vertex1 = m_VertexBufferMappingLines.PushBack<VertexLine>();
    vertex1.Position.x = p1.x;
    vertex1.Position.y = p1.y;
    vertex1.Position.z = z;
    vertex1.ColorTint = color1.GetColor();

    VertexLine& vertex2 = m_VertexBufferMappingLines.PushBack<VertexLine>();
    vertex2.Position.x = p2.x;
    vertex2.Position.y = p2.y;
    vertex2.Position.z = z;
    vertex2.ColorTint = color2.GetColor();
}

void gfxDrawerPrimitive::DrawQuad(const epiRect2f& rect, const Color& color, epiFloat z)
{
    DrawQuad(rect, color, color, z);
}

void gfxDrawerPrimitive::DrawQuad(const epiRect2f& rect, const Color& color1, const Color& color2, epiFloat z)
{
    VertexQuad& vertex1 = m_VertexBufferMappingQuads.PushBack<VertexQuad>();
    VertexQuad& vertex2 = m_VertexBufferMappingQuads.PushBack<VertexQuad>();
    VertexQuad& vertex3 = m_VertexBufferMappingQuads.PushBack<VertexQuad>();
    VertexQuad& vertex4 = m_VertexBufferMappingQuads.PushBack<VertexQuad>();
    VertexQuad& vertex5 = m_VertexBufferMappingQuads.PushBack<VertexQuad>();
    VertexQuad& vertex6 = m_VertexBufferMappingQuads.PushBack<VertexQuad>();

    const epiVec2f& lb = rect.LeftBottom();
    const epiVec2f& rt = rect.RightTop();
    const epiVec2f& lt = rect.LeftTop();
    const epiVec2f& rb = rect.RightBottom();

    vertex1.Position.x = rt.x;
    vertex1.Position.y = rt.y;
    vertex1.Position.z = z;

    vertex2.Position.x = lt.x;
    vertex2.Position.y = lt.y;
    vertex2.Position.z = z;

    vertex3.Position.x = lb.x;
    vertex3.Position.y = lb.y;
    vertex3.Position.z = z;

    vertex4 = vertex3;

    vertex5.Position.x = rb.x;
    vertex5.Position.y = rb.y;
    vertex5.Position.z = z;

    vertex6 = vertex1;

    vertex1.ColorTint = color2.GetColor();
    vertex2.ColorTint = color2.GetColor();
    vertex3.ColorTint = color1.GetColor();
    vertex4.ColorTint = color1.GetColor();
    vertex5.ColorTint = color1.GetColor();
    vertex6.ColorTint = color2.GetColor();
}

void gfxDrawerPrimitive::SceneBegin()
{
    m_VertexBufferMappingLines.Map(gfxVertexBufferMapAccess::Write);
    m_VertexBufferMappingQuads.Map(gfxVertexBufferMapAccess::Write);
}

void gfxDrawerPrimitive::SceneEnd(const gfxCamera& camera)
{
    {
        const epiSize_t lineVerticesCount = m_VertexBufferMappingLines.UnMap() / sizeof(VertexLine);
        gfxBindableScoped scope(m_ShaderProgramLines, m_VertexArrayLines);

        const GLint locationVP = glGetUniformLocation(m_ShaderProgramLines.GetProgramID(), "u_view_projection");
        const epiMat4x4f& VP = camera.GetProjectionMatrix() * camera.GetViewMatrix();
        glUniformMatrix4fv(locationVP, 1, GL_FALSE, &VP[0][0]);

        glDrawArrays(GL_LINES, 0, lineVerticesCount);
    }

    {
        const epiSize_t quadVerticesCount = m_VertexBufferMappingQuads.UnMap() / sizeof(VertexQuad);
        gfxBindableScoped scope(m_ShaderProgramQuads, m_VertexArrayQuads);

        const GLint locationVP = glGetUniformLocation(m_ShaderProgramQuads.GetProgramID(), "u_view_projection");
        const epiMat4x4f& VP = camera.GetProjectionMatrix() * camera.GetViewMatrix();
        glUniformMatrix4fv(locationVP, 1, GL_FALSE, &VP[0][0]);

        glDrawArrays(GL_TRIANGLES, 0, quadVerticesCount);
    }
}

EPI_NAMESPACE_END()
