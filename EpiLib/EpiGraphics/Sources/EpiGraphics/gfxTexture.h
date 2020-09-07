#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxTexture.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxBindable.h"

EPI_NAMESPACE_BEGIN()

enum class gfxTextureType
{
EPI_GENREGION_BEGIN(gfxTextureType)
    None = 0,
    Texture2D = 1
EPI_GENREGION_END(gfxTextureType)
};

enum class gfxTextureFormat
{
EPI_GENREGION_BEGIN(gfxTextureFormat)
    R = 0,
    RG = 1,
    RGB = 2,
    BGR = 3,
    RGBA = 4,
    BGRA = 5
EPI_GENREGION_END(gfxTextureFormat)
};

enum class gfxTexturePixelType
{
EPI_GENREGION_BEGIN(gfxTexturePixelType)
    BYTE = 0,
    UBYTE = 1,
    SHORT = 2,
    USHORT = 3,
    INT = 4,
    UINT = 5
EPI_GENREGION_END(gfxTexturePixelType)
};

class gfxTexture : public gfxBindable
{
EPI_GENREGION_BEGIN(gfxTexture)

EPI_GENHIDDEN_gfxTexture()

public:
    constexpr static epiMetaTypeID TypeID{0x50caeee4};

    enum gfxTexture_PIDs
    {
        PID_Width = 0x4ddb6a2b,
        PID_Height = 0xf2e1e039,
        PID_IsCreated = 0x560b66db,
        PID_ID = 0x11d3633a,
        PID_COUNT = 4
    };

protected:
    epiBool GetIsCreated_Callback() const;

protected:
    epiSize_t m_Width{0};
    epiSize_t m_Height{0};
    epiU32 m_ID{0};

EPI_GENREGION_END(gfxTexture)

public:
    gfxTexture() = default;
    gfxTexture(const gfxTexture& rhs) = delete;
    gfxTexture& operator=(const gfxTexture& rhs) = delete;
    gfxTexture(gfxTexture&& rhs);
    gfxTexture& operator=(gfxTexture&& rhs);
    ~gfxTexture();

public:
    void Create2D(void* initData,
                  epiSize_t width,
                  epiSize_t height,
                  gfxTextureFormat format,
                  gfxTexturePixelType pixelType);

    void Destroy();

    void Bind() override;
    void UnBind() override;

protected:
    gfxTextureType m_Type{gfxTextureType::None};
};

EPI_NAMESPACE_END()
