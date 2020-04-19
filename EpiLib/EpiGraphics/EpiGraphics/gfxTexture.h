#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxTexture.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxBindable.h"

EPI_NAMESPACE_BEGIN()

// TODO: move to epi
enum class gfxTextureType
{
    None,
    Texture2D,
    COUNT
};

// TODO: move to epi
enum class gfxTextureFormat
{
    R,
    G,
    B,
    A,
    RG,
    RGB,
    BGR,
    RGBA,
    BGRA,
    COUNT
};

// TODO: move to epi
enum class gfxTexturePixelType
{
    BYTE,
    UBYTE,
    SHORT,
    USHORT,
    INT,
    UINT,
    COUNT
};

class gfxTexture : public gfxBindable
{
EPI_GENREGION_BEGIN(gfxTexture)
public:
    EPI_GENHIDDEN_gfxTexture()

    constexpr static MetaTypeID TypeID{0x50caeee4};

    enum gfxTexture_PIDs
    {
        PID_IsCreated = 0x560b66db,
        PID_ID = 0x11d3633a,
        PID_COUNT = 2
    };

protected:
    epiBool GetIsCreated_Callback() const;

protected:
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
