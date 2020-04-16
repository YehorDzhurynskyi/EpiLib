#include "EpiGraphics/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxDrawer.h"
#include "EpiGraphics/gfxDrawer.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxContext.h"
#include "EpiGraphics/gfxVertexBuffer.h"
#include "EpiGraphics/gfxShaderProgram.h"
#include <glm/gtc/matrix_transform.hpp>

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

uniform float u_dimension;
uniform int u_nsteps;

void main()
{
    float half_dim = u_dimension / 2.0;

    {
        float y = -half_dim;
        float x = -half_dim;
        float dy = (half_dim - y) / (u_nsteps - 1);
        float dx = dy;
        for (int r = 0; r < u_nsteps; ++r)
        {
            gl_Position = u_mvp * vec4(x, y, 0.0, 1.0);
            EmitVertex();
            x += dx * (u_nsteps - 1);
            gl_Position = u_mvp * vec4(x, y, 0.0, 1.0);
            EmitVertex();
            dx = -dx;
            y += dy;
        }
        EndPrimitive();
    }
    {
        float y = -half_dim;
        float x = -half_dim;
        float dy = (half_dim - y) / (u_nsteps - 1);
        float dx = dy;
        for (int r = 0; r < u_nsteps; ++r)
        {
            gl_Position = u_mvp * vec4(x, y, 0.0, 1.0);
            EmitVertex();
            y += dy * (u_nsteps - 1);
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

void main(void)
{
    gl_Position = position;
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

EPI_NAMESPACE_BEGIN()

void gfxDrawer::DrawLine(gfxContext& ctx, const epiVec3f& p1, const epiVec3f& p2, Color color)
{
    static gfxShaderProgram staticProgram = CreateStaticProgram();

    gfxVertexArray vao;

    {
        const gfxBindableScoped scope(vao);

        gfxVertexBuffer vbo;

        vbo.Create(1024, gfxVertexBufferUsage::DynamicDraw);
        vbo.Bind();

        const GLint locationPosition = glGetAttribLocation(staticProgram.GetProgramID(), "position");
        glEnableVertexAttribArray(locationPosition);
        glVertexAttribPointer(locationPosition, 4, GL_FLOAT, false, 0, nullptr);

        epiVec4f* mapped = reinterpret_cast<epiVec4f*>(vbo.Map(gfxVertexBufferMapAccess::WriteOnly));
        mapped[0] = epiVec4f(-1.0f, 1.0f, 0.0f, 1.0f);
        mapped[1] = epiVec4f(-1.0f, -1.0f, 0.0f, 1.0f);
        mapped[2] = epiVec4f(1.0f, -1.0f, 0.0f, 1.0f);
        mapped[3] = epiVec4f(1.0f, -1.0f, 0.0f, 1.0f);
        mapped[4] = epiVec4f(1.0f, 1.0f, 0.0f, 1.0f);
        mapped[5] = epiVec4f(-1.0f, 1.0f, 0.0f, 1.0f);

        vbo.UnMap();
    }

    // TODO: repair
    // const gfxBindableScoped scope(staticProgram, vao);
    staticProgram.Bind();
    vao.Bind();

    glDrawArrays(GL_TRIANGLES, 0, 3);

    vao.UnBind();
    staticProgram.UnBind();
}

void gfxDrawer::DrawGrid(gfxContext& ctx, const epiVec3f& position, const epiVec2f& dimension, epiS32 nsteps)
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
    const epiMat4x4f& modelMat = epiMat4x4f();

    const epiMat4x4f& MVP = projMat * viewMat * modelMat;

    glUniformMatrix4fv(locationMVP, 1, GL_FALSE, &MVP[0][0]);
    glUniform1f(locationDimension, 0.5f);
    glUniform1i(locationNSteps, 50);
    glUniform4f(locationColorTint, 0.55f, 0.0f, 0.55f, 1.0f);

    glDrawArrays(GL_POINTS, 0, 1);
}

EPI_NAMESPACE_END()
