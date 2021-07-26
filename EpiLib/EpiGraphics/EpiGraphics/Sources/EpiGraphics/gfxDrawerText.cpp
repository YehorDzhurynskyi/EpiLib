EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxDrawerText.h"
#include "EpiGraphics/gfxDrawerText.cxx"
EPI_GENREGION_END(include)

namespace
{

EPI_NAMESPACE_USING()

const epiChar kShaderSourceVertexText[] = R"(
#version 400 core

uniform mat4 u_view_projection;

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_uv;
layout(location = 2) in vec4 a_color;

out vec2 uv;
out vec4 color;

void main()
{
    color = a_color;
    uv = a_uv;
    gl_Position = u_view_projection * vec4(a_position, 1.0);
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

#if 0
gfxShaderProgram CreateProgramText()
{
    gfxShader vertex;
    gfxShader pixel;

    // TODO: restore
    // vertex.CreateFromSource(kShaderSourceVertexText, gfxShaderType::Vertex);
    // pixel.CreateFromSource(kShaderSourceTextPixel, gfxShaderType::Pixel);

    gfxShaderProgram program;

    // program.ShaderAttach(vertex);
    // program.ShaderAttach(pixel);

    // program.Build();

    return program;
}
#endif

const epiU32 kMaxTextCount = 512;
struct VertexText
{
    epiVec3f Position;
    epiVec2f UV;
    epiVec4f ColorTint;
};

}

EPI_NAMESPACE_BEGIN()

gfxDrawerText::gfxDrawerText()
    //: m_VertexBufferMappingText(m_VertexBufferText)
{
    {
        // TODO: restore
        // gfxBindableScoped scope(m_VertexArrayText);

        //gfxVertexBufferLayout layout;
        // layout.Add(3, gfxVertexBufferLayoutAttributeType::FLOAT, false, sizeof(VertexText), offsetof(VertexText, Position));
        // layout.Add(2, gfxVertexBufferLayoutAttributeType::FLOAT, false, sizeof(VertexText), offsetof(VertexText, UV));
        // layout.Add(4, gfxVertexBufferLayoutAttributeType::FLOAT, false, sizeof(VertexText), offsetof(VertexText, ColorTint));

        // m_VertexBufferText.Create(nullptr, sizeof(VertexText) * 6 * kMaxTextCount, gfxVertexBufferUsage::DynamicDraw, layout);
    }

    //m_ShaderProgramText = CreateProgramText();
}

void gfxDrawerText::CreateAtlas(const gfxTextFace& face, epiU32 fontSize)
{
    constexpr epiU32 abcLen = 256;

    epiWString abc;

    abc.reserve(abcLen);
    for (epiU32 i = 0; i < abcLen; ++i)
    {
        if (epiWChar ch = static_cast<epiWChar>(i); isprint(ch))
        {
            abc.push_back(ch);
        }
    }

    CreateAtlas(face, fontSize, abc.c_str());
}

void gfxDrawerText::CreateAtlas(const gfxTextFace& face, epiU32 fontSize, const epiWChar* abc)
{
    m_TextAtlas = face.CreateRenderedAtlas(abc, fontSize);
}

void gfxDrawerText::DrawText(const epiWChar* text, const epiVec2f& position, epiFloat textHeight, const Color& color, epiFloat z)
{
    const epiFloat descender = m_TextAtlas.GetDescender() * textHeight;

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

        const epiFloat h = textHeight * glyph->GetHeight();
        const epiFloat w = glyph->GetAspectRatio() * h;

        const epiFloat advanceX = glyph->GetAdvance().x * w;

        const epiFloat bearingX = glyph->GetBearing().x * w;
        const epiFloat bearingY = glyph->GetBearing().y * h;

        const epiVec2f pen(pos.x + bearingX, pos.y + bearingY - h - descender);

#if 0
        {
            VertexText& vertex = m_VertexBufferMappingText.PushBack<VertexText>();
            vertex.Position = epiVec3f(pen.x, pen.y, z);
            vertex.UV = epiVec2f(uv.Left, uv.Bottom);
            vertex.ColorTint = color.GetColor();
        }

        {
            VertexText& vertex = m_VertexBufferMappingText.PushBack<VertexText>();
            vertex.Position = epiVec3f(pen.x + w, pen.y, z);
            vertex.UV = epiVec2f(uv.Right, uv.Bottom);
            vertex.ColorTint = color.GetColor();
        }

        {
            VertexText& vertex = m_VertexBufferMappingText.PushBack<VertexText>();
            vertex.Position = epiVec3f(pen.x + w, pen.y + h, z);
            vertex.UV = epiVec2f(uv.Right, uv.Top);
            vertex.ColorTint = color.GetColor();
        }

        {
            VertexText& vertex = m_VertexBufferMappingText.PushBack<VertexText>();
            vertex.Position = epiVec3f(pen.x + w, pen.y + h, z);
            vertex.UV = epiVec2f(uv.Right, uv.Top);
            vertex.ColorTint = color.GetColor();
        }

        {
            VertexText& vertex = m_VertexBufferMappingText.PushBack<VertexText>();
            vertex.Position = epiVec3f(pen.x, pen.y + h, z);
            vertex.UV = epiVec2f(uv.Left, uv.Top);
            vertex.ColorTint = color.GetColor();
        }

        {
            VertexText& vertex = m_VertexBufferMappingText.PushBack<VertexText>();
            vertex.Position = epiVec3f(pen.x, pen.y, z);
            vertex.UV = epiVec2f(uv.Left, uv.Bottom);
            vertex.ColorTint = color.GetColor();
        }

        pos.x += advanceX;
#endif
    }
}

void gfxDrawerText::SceneBegin()
{
    //m_VertexBufferMappingText.Map(gfxVertexBufferMapAccess::Write);
}

void gfxDrawerText::SceneEnd(const gfxCamera& camera)
{
    //const epiSize_t textVerticesCount = m_VertexBufferMappingText.UnMap() / sizeof(VertexText);

    {
        // TODO: restore
        // gfxBindableScoped scope(m_ShaderProgramText, m_VertexArrayText, m_TextAtlas);

        // m_ShaderProgramText.Texture("u_texture", 0);

        // m_ShaderProgramText.Uniform("u_shift", 0.0f);
        // m_ShaderProgramText.Uniform("u_gamma", 1.43f);

        // const epiSize_t atlasW = m_TextAtlas.GetTexture().GetWidth();
        // const epiSize_t atlasH = m_TextAtlas.GetTexture().GetHeight();
        // const epiVec2f pixelSize(1.0f / atlasW, 1.0f / atlasH);
        // m_ShaderProgramText.Uniform("u_pixel_size", pixelSize);

        // const epiMat4x4f& VP = camera.GetProjectionMatrix() * camera.GetViewMatrix();
        // m_ShaderProgramText.Uniform("u_view_projection", VP);

        // TODO: restore
        // glDrawArrays(GL_TRIANGLES, 0, textVerticesCount);
    }
}

EPI_NAMESPACE_END()
