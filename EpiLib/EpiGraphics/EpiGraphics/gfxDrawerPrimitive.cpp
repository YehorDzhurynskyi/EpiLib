#include "EpiGraphics/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxDrawerPrimitive.h"
#include "EpiGraphics/gfxDrawerPrimitive.cxx"
EPI_GENREGION_END(include)

#if 0
namespace
{

const epiChar ShaderSourceGridVertex[] = R"(
#version 400

void main(void)
{
    gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
}
)";

const epiChar ShaderSourceGridGeometry[] = R"(
#version 400 core

layout (points) in;
layout (line_strip, max_vertices = 225) out;

uniform mat4 u_mvp;

uniform vec2 u_dimension;
uniform ivec2 u_nsteps;

void main()
{
    float half_dim_x = u_dimension.x / 2.0;
    float half_dim_y = u_dimension.y / 2.0;

/*
    {
        float y = -half_dim_y;
        float x = -half_dim_x;
        float dy = u_dimension.y / (u_nsteps.y - 1);
        float dx = u_dimension.x / (u_nsteps.x - 1);
        for (int r = 0; r < u_nsteps.x; ++r)
        {
            gl_Position = u_mvp * vec4(x, y, 0.0, 1.0);
            EmitVertex();
            x += dx * (u_nsteps.x - 1);
            gl_Position = u_mvp * vec4(x, y, 0.0, 1.0);
            EmitVertex();
            dx = -dx;
            y += dy;
        }
        EndPrimitive();
    }
*/
    {
        float y = -half_dim_y;
        float x = -half_dim_x;
        float dy = u_dimension.y / (u_nsteps.y - 1);
        float dx = u_dimension.x / (u_nsteps.x - 1);;
        for (int r = 0; r < u_nsteps.y; ++r)
        {
            gl_Position = u_mvp * vec4(x, y, 0.0, 1.0);
            EmitVertex();
            y += dy * (u_nsteps.y - 1);
            gl_Position = u_mvp * vec4(x, y, 0.0, 1.0);
            EmitVertex();
            dy = -dy;
            x += dx;
        }
        EndPrimitive();
    }
})";

const epiChar ShaderSourceGridPixel[] = R"(
#version 400 core

uniform vec4 u_color_tint;

out vec4 fragcolor;

void main(void)
{
    fragcolor = u_color_tint;
}
)";

const epiChar ShaderSourceStaticVertex[] = R"(
#version 400 core

in vec4 position;

uniform mat4 u_mvp;

void main(void)
{
    gl_Position = u_mvp * position;
}
)";

const epiChar ShaderSourceStaticPixel[] = R"(
#version 400 core

out vec4 fragcolor;

void main(void)
{
    fragcolor = vec4(0.0, 0.0, 1.0, 1.0);
}
)";

using namespace epi;
gfxShaderProgram CreateGridProgram()
{
    gfxShader vertex;
    gfxShader geometry;
    gfxShader pixel;

    vertex.CreateFromSource(ShaderSourceGridVertex, gfxShaderType::Vertex);
    geometry.CreateFromSource(ShaderSourceGridGeometry, gfxShaderType::Geometry);
    pixel.CreateFromSource(ShaderSourceGridPixel, gfxShaderType::Pixel);

    gfxShaderProgram program;

    program.ShaderAttach(vertex);
    program.ShaderAttach(geometry);
    program.ShaderAttach(pixel);

    program.Build();

    return program;
}

gfxShaderProgram CreateStaticProgram()
{
    gfxShader vertex;
    gfxShader pixel;

    vertex.CreateFromSource(ShaderSourceStaticVertex, gfxShaderType::Vertex);
    pixel.CreateFromSource(ShaderSourceStaticPixel, gfxShaderType::Pixel);

    gfxShaderProgram program;

    program.ShaderAttach(vertex);
    program.ShaderAttach(pixel);

    program.Build();

    return program;
}

}

void gfxDrawerPrimitive::DrawLine(gfxContext& ctx, const epiVec3f& p1, const epiVec3f& p2, Color color)
{
    static gfxShaderProgram staticProgram = CreateStaticProgram();

    gfxVertexArray vao;
    gfxVertexBuffer vbo;

    {
        const gfxBindableScoped scope(vao);

        vbo.Create(nullptr, 1024, gfxVertexBufferUsage::DynamicDraw);
        vbo.Bind();

        const GLint locationPosition = glGetAttribLocation(staticProgram.GetProgramID(), "position");
        glEnableVertexAttribArray(locationPosition);
        glVertexAttribPointer(locationPosition, 4, GL_FLOAT, false, 0, nullptr);

        epiVec4f* mapped = reinterpret_cast<epiVec4f*>(vbo.Map(gfxVertexBufferMapAccess::WriteOnly));
        mapped[0] = epiVec4f(-0.5f, 0.5f, 0.0f, 1.0f);
        mapped[1] = epiVec4f(-0.5f, -0.5f, 0.0f, 1.0f);
        mapped[2] = epiVec4f(0.5f, -0.5f, 0.0f, 1.0f);
        mapped[3] = epiVec4f(0.5f, -0.5f, 0.0f, 1.0f);
        mapped[4] = epiVec4f(0.5f, 0.5f, 0.0f, 1.0f);
        mapped[5] = epiVec4f(-0.5f, 0.5f, 0.0f, 1.0f);

        vbo.UnMap();
    }

    const gfxBindableScoped scope(staticProgram, vao);

    const epiS32 locationMVP = glGetUniformLocation(staticProgram.GetProgramID(), "u_mvp");
    const gfxCamera& camera = ctx.GetCamera();
    const epiMat4x4f& projMat = camera.GetProjectionMatrix();
    const epiMat4x4f& viewMat = camera.GetViewMatrix();

    const epiMat4x4f& MVP = projMat * viewMat;

    glUniformMatrix4fv(locationMVP, 1, GL_FALSE, &MVP[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void gfxDrawerPrimitive::DrawGrid(gfxContext& ctx, const epiVec3f& position, const epiVec2f& dimension, const epiVec2s& nsteps)
{
    static gfxShaderProgram gridProgram = CreateGridProgram();

    const gfxBindableScoped scope(gridProgram, ctx.GetNullVertexArray());

    const epiS32 locationMVP = glGetUniformLocation(gridProgram.GetProgramID(), "u_mvp");
    const epiS32 locationDimension = glGetUniformLocation(gridProgram.GetProgramID(), "u_dimension");
    const epiS32 locationNSteps = glGetUniformLocation(gridProgram.GetProgramID(), "u_nsteps");
    const epiS32 locationColorTint = glGetUniformLocation(gridProgram.GetProgramID(), "u_color_tint");

    const gfxCamera& camera = ctx.GetCamera();
    const epiMat4x4f& projMat = camera.GetProjectionMatrix();
    const epiMat4x4f& viewMat = camera.GetViewMatrix();

    const epiMat4x4f& MVP = projMat * viewMat;

    glUniformMatrix4fv(locationMVP, 1, GL_FALSE, &MVP[0][0]);
    glUniform2fv(locationDimension, 1, &dimension[0]);
    glUniform2iv(locationNSteps, 1, &nsteps[0]);
    glUniform4f(locationColorTint, 0.55f, 1.0f, 0.55f, 1.0f);

    glDrawArrays(GL_POINTS, 0, 1);
}

void gfxDrawerPrimitive::DrawText(gfxContext& ctx, gfxTextRenderedABC& abc, const epiWChar* text, const epiVec2f& position, epiFloat textHeight, const Color& color)
{
    // NOTE: this method is worse than Atlas
    epiAssert(false, "Use Atlas method instead");
    return;

    static gfxShaderProgram program = CreateTextProgram();

    epiVec2f pos{};
    pos.x = -0.5f;
    const epiSize_t textlen = wcslen(text);
    for (epiS32 i = 0; i < textlen; ++i)
    {
        gfxTextRenderedGlyph* glyph = abc.GlyphOf(text[i]);
        if (glyph == nullptr)
        {
            continue;
        }

        const epiVec2u& bearing = glyph->GetBearing();
        const epiVec2u& size = glyph->GetSize();

        const epiFloat x = pos.x;
        const epiFloat y = pos.y;

        const epiFloat w = (size.x / static_cast<epiFloat>(size.y)) * textHeight;
        const epiFloat h = textHeight;

        gfxVertexArray vao;
        gfxVertexBuffer vbo;

        const gfxBindableScoped scope(program, vao);

        const epiS32 sampler = glGetUniformLocation(program.GetProgramID(), "u_texture");
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(sampler, 0);

        const epiS32 locationMVP = glGetUniformLocation(program.GetProgramID(), "u_mvp");
        const gfxCamera& camera = ctx.GetCamera();
        const epiMat4x4f& projMat = camera.GetProjectionMatrix();
        const epiMat4x4f& viewMat = camera.GetViewMatrix();
        const epiMat4x4f& MVP = projMat * viewMat;
        glUniformMatrix4fv(locationMVP, 1, GL_FALSE, &MVP[0][0]);

        vbo.Create(nullptr, 1024, gfxVertexBufferUsage::DynamicDraw);
        vbo.Bind();

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(epiVec2f), nullptr);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, false, 2 * sizeof(epiVec2f), (void*)sizeof(epiVec2f));

        epiVec2f* mapped = reinterpret_cast<epiVec2f*>(vbo.Map(gfxVertexBufferMapAccess::WriteOnly));

        mapped[0] = epiVec2f(x, y + h);
        mapped[1] = epiVec2f(0.0f, 0.0f);
        mapped[2] = epiVec2f(x, y);
        mapped[3] = epiVec2f(0.0f, 1.0f);
        mapped[4] = epiVec2f(x + w, y);
        mapped[5] = epiVec2f(1.0f, 1.0f);

        mapped[6] = epiVec2f(x, y + h);
        mapped[7] = epiVec2f(0.0f, 0.0f);
        mapped[8] = epiVec2f(x + w, y);
        mapped[9] = epiVec2f(1.0f, 1.0f);
        mapped[10] = epiVec2f(x + w, y + h);
        mapped[11] = epiVec2f(1.0f, 0.0f);

        vbo.UnMap();

        gfxBindableScoped scoped(glyph->GetTexture());
        glDrawArrays(GL_TRIANGLES, 0, 6);

        pos.x += w;
    }
}
#endif

namespace
{

using namespace epi;

const epiChar kShaderSourceLinesVertex[] = R"(
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

const epiChar kShaderSourceLinesPixel[] = R"(
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

    vertex.CreateFromSource(kShaderSourceLinesVertex, gfxShaderType::Vertex);
    pixel.CreateFromSource(kShaderSourceLinesPixel, gfxShaderType::Pixel);

    gfxShaderProgram program;

    program.ShaderAttach(vertex);
    program.ShaderAttach(pixel);

    program.Build();

    return program;
}

const epiU32 kMaxLineCount = 512;
struct VertexLine
{
    epiVec2f Position;
    epiVec4f ColorTint;
};

}

EPI_NAMESPACE_BEGIN()

gfxDrawerPrimitive::gfxDrawerPrimitive()
    : m_VertexBufferMappingLines(m_VertexBufferLines)
{
    m_VertexBufferLines.Create(nullptr, sizeof(VertexLine) * 2 * kMaxLineCount, gfxVertexBufferUsage::DynamicDraw);

    {
        gfxBindableScoped scope(m_VertexArrayLines, m_VertexBufferLines);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(VertexLine), (void*)offsetof(VertexLine, Position));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(VertexLine), (void*)offsetof(VertexLine, ColorTint));
    }

    m_ShaderProgramLines = CreateLinesProgram();
}

void gfxDrawerPrimitive::DrawLine(const epiVec2f& p1, const epiVec2f& p2, const Color& color)
{
    VertexLine& vertex1 = m_VertexBufferMappingLines.PushBack<VertexLine>();
    vertex1.Position = p1;
    vertex1.ColorTint = color.GetColor();

    VertexLine& vertex2 = m_VertexBufferMappingLines.PushBack<VertexLine>();
    vertex2.Position = p2;
    vertex2.ColorTint = color.GetColor();
}

void gfxDrawerPrimitive::SceneBegin()
{
    m_VertexBufferMappingLines.Map(gfxVertexBufferMapAccess::WriteOnly);
}

void gfxDrawerPrimitive::SceneEnd(const gfxCamera& camera)
{
    const epiSize_t lineVerticesCount = m_VertexBufferMappingLines.UnMap() / sizeof(VertexLine);

    {
        gfxBindableScoped scope(m_ShaderProgramLines, m_VertexArrayLines);

        const GLint locationVP = glGetUniformLocation(m_ShaderProgramLines.GetProgramID(), "u_view_projection");
        const epiMat4x4f& VP = camera.GetProjectionMatrix() * camera.GetViewMatrix();
        glUniformMatrix4fv(locationVP, 1, GL_FALSE, &VP[0][0]);

        glDrawArrays(GL_LINES, 0, lineVerticesCount);
    }
}

EPI_NAMESPACE_END()
