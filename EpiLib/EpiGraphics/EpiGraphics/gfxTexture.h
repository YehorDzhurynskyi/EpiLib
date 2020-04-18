#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxTexture.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxBindable.h"

EPI_NAMESPACE_BEGIN()

// TODO: move to epi
enum class gfxTextureType
{
    Texture1D,
    Texture2D,
    Texture3D,
    Texture1DArray,
    Texture2DArray,
    Texture3DArray,
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
    void Create(epiSize_t capacity, gfxTextureType type);
    void Destroy();

    void Bind() override;
    void UnBind() override;
};

EPI_NAMESPACE_END()
