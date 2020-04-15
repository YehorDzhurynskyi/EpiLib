#include "EpiGraphics/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxDrawer.h"
#include "EpiGraphics/gfxDrawer.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxShaderProgram.h"

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
    vertex.CreateFromSource(ShaderSourceGeometry, gfxShaderType::Geometry);
    vertex.CreateFromSource(ShaderSourcePixel, gfxShaderType::Pixel);

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
    static gfxShaderProgram gridProgram = CreateGridProgram();

    gfxBindableScoped scope(gridProgram, ctx.GetNullVertexArray());

#if 0
    epiMat4x4f model;
    model = transform_rotate_x(&model, M_PI_2);
    mvp = mat4f_mat4f_mult(&model, vp);
    glUniformMatrix4fv(program->u_location_mvp, 1, GL_FALSE, &mvp.data[0][0]);
    glUniform1f(program->u_location_dimension, 50.0f);
    glUniform1i(program->u_location_nsteps, 50);
    glUniform4f(program->u_location_color_tint, 0.55f, 0.55f, 0.55f, 1.0f);
    glDrawArrays(GL_POINTS, 0, 1);
#endif
}

EPI_NAMESPACE_END()
