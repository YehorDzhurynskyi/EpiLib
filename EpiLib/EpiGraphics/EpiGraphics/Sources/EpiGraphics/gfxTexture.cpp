EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxTexture.h"
#include "EpiGraphics/gfxTexture.cxx"
EPI_GENREGION_END(include)

#include <glad/glad.h>

EPI_NAMESPACE_BEGIN()

gfxTexture::~gfxTexture()
{
    if (GetIsCreated())
    {
        Destroy();
    }
}

gfxTexture::gfxTexture(gfxTexture&& rhs)
{
    m_ID = rhs.m_ID;
    m_Type = rhs.m_Type;
    rhs.m_ID = 0;
    rhs.m_Type = gfxTextureType::None;
}

gfxTexture& gfxTexture::operator=(gfxTexture&& rhs)
{
    m_ID = rhs.m_ID;
    m_Type = rhs.m_Type;
    rhs.m_ID = 0;
    rhs.m_Type = gfxTextureType::None;

    return *this;
}

void gfxTexture::Create2D(void* initData,
                          epiSize_t width,
                          epiSize_t height,
                          gfxTextureFormat format,
                          gfxTexturePixelType pixelType)
{
    epiExpect(!GetIsCreated(), "Create method should be called on destroyed texture");
    epiExpect(width > 0, "width of the texture should be greater than 0");
    epiExpect(height > 0, "width of the texture should be greater than 0");

    GLenum glFormat;
    switch (format)
    {
    case gfxTextureFormat::R: glFormat = GL_RED; break;
    case gfxTextureFormat::RG: glFormat = GL_RG; break;
    case gfxTextureFormat::RGB:  glFormat = GL_RGB; break;
    case gfxTextureFormat::BGR:  glFormat = GL_BGR; break;
    case gfxTextureFormat::RGBA: glFormat = GL_RGBA; break;
    case gfxTextureFormat::BGRA: glFormat = GL_BGRA; break;
    default: epiAssert(false, "Unhandled case"); return;
    }

    GLenum glPixelType;
    switch (pixelType)
    {
    case gfxTexturePixelType::BYTE: glPixelType = GL_BYTE; break;
    case gfxTexturePixelType::UBYTE: glPixelType = GL_UNSIGNED_BYTE; break;
    case gfxTexturePixelType::SHORT:  glPixelType = GL_SHORT; break;
    case gfxTexturePixelType::USHORT:  glPixelType = GL_UNSIGNED_SHORT; break;
    case gfxTexturePixelType::INT: glPixelType = GL_INT; break;
    case gfxTexturePixelType::UINT: glPixelType = GL_UNSIGNED_INT; break;
    default: epiAssert(false, "Unhandled case"); return;
    }

    glGenTextures(1, &m_ID);
    if (m_ID == 0)
    {
        return;
    }
    m_Type = gfxTextureType::Texture2D;

    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, glFormat, width, height, 0, glFormat, glPixelType, initData);

    m_Width = width;
    m_Height = height;
}

void gfxTexture::Destroy()
{
    epiExpect(GetIsCreated(), "Destroy method should be called on already created vertex buffer");

    glDeleteTextures(1, &m_ID);
    m_ID = 0;
}

epiBool gfxTexture::GetIsCreated_Callback() const
{
    return m_ID != 0 && m_Type != gfxTextureType::None;
}

void gfxTexture::Bind()
{
    epiExpect(GetIsCreated(), "A texture expected to be created");

    super::Bind();
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

void gfxTexture::UnBind()
{
    epiExpect(GetIsCreated(), "A texture expected to be created");

    super::UnBind();
    glBindTexture(GL_TEXTURE_2D, 0);
}


EPI_NAMESPACE_END()
