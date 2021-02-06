EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxTexture.h"
#include "EpiGraphics/gfxTexture.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

gfxTexture::~gfxTexture()
{
    if (GetIsCreated())
    {
        Destroy();
    }
}

void gfxTexture::Create2D(const epiByte* initData,
                          epiU32 width,
                          epiU32 height,
                          gfxTextureFormat format,
                          gfxTexturePixelType pixelType)
{
    epiExpect(!GetIsCreated(), "Create method should be called on destroyed texture");
    epiExpect(width > 0, "width of the texture should be greater than 0");
    epiExpect(height > 0, "width of the texture should be greater than 0");

    m_Impl->Create2D(initData, width, height, format, pixelType);
}

void gfxTexture::Destroy()
{
    epiExpect(GetIsCreated(), "Destroy method should be called on already created vertex buffer");

    m_Impl->Destroy();
}

epiU32 gfxTexture::GetWidth_Callback() const
{
    return m_Impl->GetWidth();
}

epiU32 gfxTexture::GetHeight_Callback() const
{
    return m_Impl->GetHeight();
}

epiBool gfxTexture::GetIsCreated_Callback() const
{
    return m_Impl->GetIsCreated();
}

epiU32 gfxTexture::GetID_Callback() const
{
    return m_Impl->GetID();
}

gfxTextureType gfxTexture::GetType_Callback() const
{
    return m_Impl->GetType();
}

void gfxTexture::Bind()
{
    epiExpect(GetIsCreated(), "A texture expected to be created");

    super::Bind();

    m_Impl->Bind();
}

void gfxTexture::UnBind()
{
    epiExpect(GetIsCreated(), "A texture expected to be created");

    super::UnBind();

    m_Impl->UnBind();
}


EPI_NAMESPACE_END()
