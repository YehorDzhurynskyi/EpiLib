#include "EpiGraphics/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxDrawerText.h"
#include "EpiGraphics/gfxDrawerText.cxx"
EPI_GENREGION_END(include)

namespace
{

using namespace epi;

#if 1
const epiChar kShaderSourceVertexText[] = R"(
#version 400 core

uniform mat4 u_view_projection;

layout(location = 0) in vec2 a_position;
layout(location = 1) in vec2 a_uv;
layout(location = 2) in vec4 a_color;

out vec2 uv;
out vec4 color;

void main()
{
    color = a_color;
    uv = a_uv;
    gl_Position = u_view_projection * vec4(a_position, 0.0, 1.0);
}
)";

const epiChar kShaderSourceTextPixel[] = R"(
#version 400 core

uniform sampler2D u_texture;
uniform vec2 u_pixel_size;
uniform float u_shift;
uniform float u_gamma;

in vec4 color;
in vec2 uv;

out vec4 fragcolor;

void main()
{
    vec4 current = texture2D(u_texture, uv);
    vec4 previous = texture2D(u_texture, uv + vec2(-1.0, 0.0) * u_pixel_size);
    // vec4 next = texture2D(u_texture, uv + vec2(1.0, 0.0) * u_pixel_size);

    current = pow(current, vec4(1.0 / u_gamma));
    previous = pow(previous, vec4(1.0 / u_gamma));

    float r = current.r;
    float g = current.g;
    float b = current.b;

    if (u_shift <= 0.333)
    {
        float z = u_shift / 0.333;
        r = mix(current.r, previous.b, z);
        g = mix(current.g, current.r,  z);
        b = mix(current.b, current.g,  z);
    }
    else if (u_shift <= 0.666)
    {
        float z = (u_shift - 0.33) / 0.333;
        r = mix(previous.b, previous.g, z);
        g = mix(current.r, previous.b, z);
        b = mix(current.g, current.r,  z);
    }
   else if (u_shift < 1.0)
    {
        float z = (u_shift - 0.66) / 0.334;
        r = mix(previous.g, previous.r, z);
        g = mix(previous.b, previous.g, z);
        b = mix(current.r, previous.b, z);
    }

   float t = max(max(r, g), b);

   vec4 col = vec4(color.rgb, (r + g + b) / 3.0);
   col = t * col + (1.0 - t) * vec4(r, g, b, min(min(r, g), b));

   fragcolor = vec4(col.rgb, color.a * col.a);
}
)";
#else
const epiChar kShaderSourceVertexText[] = R"(
#version 400 core

layout(location = 0) in vec2 a_position;
layout(location = 1) in vec2 a_uv;
layout(location = 2) in vec4 a_color;

uniform mat4 u_view_projection;

out vec2 uv;
out vec4 color;

void main(void)
{
    gl_Position = u_view_projection * vec4(a_position, 0.0, 1.0);
    uv = a_uv;
    color = a_color;
}
)";

const epiChar kShaderSourceTextPixel[] = R"(
#version 400 core

in vec2 uv;
in vec4 color;

out vec4 fragcolor;

uniform sampler2D u_texture;

void main(void)
{
    fragcolor = color * vec4(1.0, 1.0, 1.0, texture(u_texture, uv).r);
}
)";
#endif

gfxShaderProgram CreateTextProgram()
{
    gfxShader vertex;
    gfxShader pixel;

    vertex.CreateFromSource(kShaderSourceVertexText, gfxShaderType::Vertex);
    pixel.CreateFromSource(kShaderSourceTextPixel, gfxShaderType::Pixel);

    gfxShaderProgram program;

    program.ShaderAttach(vertex);
    program.ShaderAttach(pixel);

    program.Build();

    return program;
}

const epiU32 kMaxTextCount = 512;
struct VertexText
{
    epiVec2f Position;
    epiVec2f UV;
    epiVec4f ColorTint;
};

}

EPI_NAMESPACE_BEGIN()

gfxDrawerText::gfxDrawerText(const gfxCamera& camera, const gfxTextFace& face, const epiWChar* abc)
    : super(camera)
    , m_VertexBufferMappingText(m_VertexBufferText)
    , m_TextAtlas(face.CreateRenderedAtlas(abc, 12))
{
    m_VertexBufferText.Create(nullptr, sizeof(VertexText) * 6 * kMaxTextCount, gfxVertexBufferUsage::DynamicDraw);

    {
        gfxBindableScoped scope(m_VertexArrayText, m_VertexBufferText);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(VertexText), (void*)offsetof(VertexText, Position));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexText), (void*)offsetof(VertexText, UV));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 4, GL_FLOAT, false, sizeof(VertexText), (void*)offsetof(VertexText, ColorTint));
    }

    m_ShaderProgramText = CreateTextProgram();
}

void gfxDrawerText::DrawText(const epiWChar* text, const epiVec2f& position, epiFloat textHeight, const Color& color)
{
    epiVec2f pos = position;
    const epiSize_t textlen = wcslen(text);
    for (epiS32 i = 0; i < textlen; ++i)
    {
        const gfxTextRenderedAtlasGlyph* glyph = m_TextAtlas.GlyphOf(text[i]);
        if (glyph == nullptr)
        {
            continue;
        }

        const epiRect2f& uv = glyph->GetUV();
        const epiFloat w = glyph->GetAspectRatio() * textHeight;
        const epiFloat h = textHeight;

        {
            VertexText& vertex = m_VertexBufferMappingText.PushBack<VertexText>();
            vertex.Position = epiVec2f(pos.x, pos.y);
            vertex.UV = epiVec2f(uv.Left, uv.Bottom);
            vertex.ColorTint = color.GetColor();
        }

        {
            VertexText& vertex = m_VertexBufferMappingText.PushBack<VertexText>();
            vertex.Position = epiVec2f(pos.x + w, pos.y);
            vertex.UV = epiVec2f(uv.Right, uv.Bottom);
            vertex.ColorTint = color.GetColor();
        }

        {
            VertexText& vertex = m_VertexBufferMappingText.PushBack<VertexText>();
            vertex.Position = epiVec2f(pos.x + w, pos.y + h);
            vertex.UV = epiVec2f(uv.Right, uv.Top);
            vertex.ColorTint = color.GetColor();
        }

        {
            VertexText& vertex = m_VertexBufferMappingText.PushBack<VertexText>();
            vertex.Position = epiVec2f(pos.x + w, pos.y + h);
            vertex.UV = epiVec2f(uv.Right, uv.Top);
            vertex.ColorTint = color.GetColor();
        }

        {
            VertexText& vertex = m_VertexBufferMappingText.PushBack<VertexText>();
            vertex.Position = epiVec2f(pos.x, pos.y + h);
            vertex.UV = epiVec2f(uv.Left, uv.Top);
            vertex.ColorTint = color.GetColor();
        }

        {
            VertexText& vertex = m_VertexBufferMappingText.PushBack<VertexText>();
            vertex.Position = epiVec2f(pos.x, pos.y);
            vertex.UV = epiVec2f(uv.Left, uv.Bottom);
            vertex.ColorTint = color.GetColor();
        }

        pos.x += w;
    }
}

void gfxDrawerText::SceneBegin()
{
    super::SceneBegin();

    m_VertexBufferMappingText.Map(gfxVertexBufferMapAccess::WriteOnly);
}

void gfxDrawerText::SceneEnd()
{
    super::SceneEnd();

    const epiSize_t textVerticesCount = m_VertexBufferMappingText.UnMap() / sizeof(VertexText);

    {
        gfxBindableScoped scope(m_ShaderProgramText, m_VertexArrayText, m_TextAtlas);

        const epiS32 locationSampler = glGetUniformLocation(m_ShaderProgramText.GetProgramID(), "u_texture");
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(locationSampler, 0);

#if 1
        const epiS32 locationShift = glGetUniformLocation(m_ShaderProgramText.GetProgramID(), "u_shift");
        glUniform1f(locationShift, 0.0f);

        const epiS32 locationGamma = glGetUniformLocation(m_ShaderProgramText.GetProgramID(), "u_gamma");
        glUniform1f(locationGamma, 1.43f);

        const epiS32 locationPixelSize = glGetUniformLocation(m_ShaderProgramText.GetProgramID(), "u_pixel_size");
        const epiSize_t atlasW = m_TextAtlas.GetTexture().GetWidth();
        const epiSize_t atlasH = m_TextAtlas.GetTexture().GetHeight();
        const epiVec2f pixelSize(1.0f / atlasW, 1.0f / atlasH);
        glUniform2fv(locationPixelSize, 1, &pixelSize[0]);
#endif

        const epiS32 locationVP = glGetUniformLocation(m_ShaderProgramText.GetProgramID(), "u_view_projection");
        epiMat4x4f P = m_Camera.GetProjectionMatrix();
        P[0][0] *= m_Camera.GetAspectRatio();
        const epiMat4x4f& VP = P * m_Camera.GetViewMatrix();
        glUniformMatrix4fv(locationVP, 1, GL_FALSE, &VP[0][0]);

        glDrawArrays(GL_TRIANGLES, 0, 6 * textVerticesCount);
    }
}

EPI_NAMESPACE_END()
