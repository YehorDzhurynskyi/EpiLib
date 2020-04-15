#include "EpiGraphics/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxDrawer.h"
#include "EpiGraphics/gfxDrawer.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxShaderProgram.h"
#include <glm/gtc/matrix_transform.hpp>

namespace
{
const epiChar ShaderSourceVertex[] = R"(
#version 400

void main(void)
{
    gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
}
)";

const epiChar ShaderSourceGeometry[] = R"(
#version 400

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

const epiChar ShaderSourcePixel[] = R"(
#version 400

uniform vec4 u_color_tint;

out vec4 fragcolor;

void main(void)
{
    fragcolor = u_color_tint;
}
)";

using namespace epi;
gfxShaderProgram CreateGridProgram()
{
    gfxShader vertex;
    gfxShader geometry;
    gfxShader pixel;

    vertex.CreateFromSource(ShaderSourceVertex, gfxShaderType::Vertex);
    geometry.CreateFromSource(ShaderSourceGeometry, gfxShaderType::Geometry);
    pixel.CreateFromSource(ShaderSourcePixel, gfxShaderType::Pixel);

    gfxShaderProgram program;

    program.ShaderAttach(vertex);
    program.ShaderAttach(geometry);
    program.ShaderAttach(pixel);

    return program;
}
}

EPI_NAMESPACE_BEGIN()

void gfxDrawer::DrawGrid(gfxContext& ctx, const epiVec3f position, const epiVec2f& dimension, epiS32 nsteps)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

    static gfxShaderProgram gridProgram = CreateGridProgram();

    const gfxBindableScoped scope(gridProgram, ctx.GetNullVertexArray());

    const epiS32 locationMVP = glGetUniformLocation(gridProgram.GetProgramID(), "u_mvp");
    const epiS32 locationDimension = glGetUniformLocation(gridProgram.GetProgramID(), "u_dimension");
    const epiS32 locationNSteps = glGetUniformLocation(gridProgram.GetProgramID(), "u_nsteps");
    const epiS32 locationColorTint = glGetUniformLocation(gridProgram.GetProgramID(), "u_color_tint");

    epiMat4x4f mvp = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f, 0.1f, 100.0f);
    glUniformMatrix4fv(locationMVP, 1, GL_FALSE, &mvp[0][0]);
    glUniform1f(locationDimension, 0.5f);
    glUniform1i(locationNSteps, 50);
    glUniform4f(locationColorTint, 0.55f, 0.0f, 0.55f, 1.0f);
    glDrawArrays(GL_POINTS, 0, 1);
}

EPI_NAMESPACE_END()
