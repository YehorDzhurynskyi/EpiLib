#include "EpiGraphics/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxDrawerText.h"
#include "EpiGraphics/gfxDrawerText.cxx"
EPI_GENREGION_END(include)

namespace
{

using namespace epi;

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
    Color ColorTint;
};

}

EPI_NAMESPACE_BEGIN()

gfxDrawerText::gfxDrawerText(const gfxCamera& camera, const gfxTextFace& face, const epiWChar* abc)
    : super(camera)
    , m_VertexBufferMappingText(m_VertexBufferText)
    , m_TextAtlas(face.CreateRenderedAtlas(abc, 72))
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
            vertex.ColorTint = color;
        }

        {
            VertexText& vertex = m_VertexBufferMappingText.PushBack<VertexText>();
            vertex.Position = epiVec2f(pos.x + w, pos.y);
            vertex.UV = epiVec2f(uv.Right, uv.Bottom);
            vertex.ColorTint = color;
        }

        {
            VertexText& vertex = m_VertexBufferMappingText.PushBack<VertexText>();
            vertex.Position = epiVec2f(pos.x + w, pos.y + h);
            vertex.UV = epiVec2f(uv.Right, uv.Top);
            vertex.ColorTint = color;
        }

        {
            VertexText& vertex = m_VertexBufferMappingText.PushBack<VertexText>();
            vertex.Position = epiVec2f(pos.x + w, pos.y + h);
            vertex.UV = epiVec2f(uv.Right, uv.Top);
            vertex.ColorTint = color;
        }

        {
            VertexText& vertex = m_VertexBufferMappingText.PushBack<VertexText>();
            vertex.Position = epiVec2f(pos.x, pos.y + h);
            vertex.UV = epiVec2f(uv.Left, uv.Top);
            vertex.ColorTint = color;
        }

        {
            VertexText& vertex = m_VertexBufferMappingText.PushBack<VertexText>();
            vertex.Position = epiVec2f(pos.x, pos.y);
            vertex.UV = epiVec2f(uv.Left, uv.Bottom);
            vertex.ColorTint = color;
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

        const epiS32 locationVP = glGetUniformLocation(m_ShaderProgramText.GetProgramID(), "u_view_projection");
        const epiMat4x4f& VP = m_Camera.GetProjectionMatrix() * m_Camera.GetViewMatrix();
        glUniformMatrix4fv(locationVP, 1, GL_FALSE, &VP[0][0]);

        glDrawArrays(GL_TRIANGLES, 0, 6 * textVerticesCount);
    }
}

EPI_NAMESPACE_END()
