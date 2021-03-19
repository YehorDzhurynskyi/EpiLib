#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxTexture.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxBindable.h"

#include "EpiGraphicsDriverCommon/gfxEnum.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxTextureImpl;

} // namespace internalgfx

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
        PID_Type = 0x2cecf817,
        PID_COUNT = 5
    };

protected:
    epiU32 GetWidth_Callback() const;
    epiU32 GetHeight_Callback() const;
    epiBool GetIsCreated_Callback() const;
    epiU32 GetID_Callback() const;
    gfxTextureType GetType_Callback() const;

EPI_GENREGION_END(gfxTexture)

public:
    gfxTexture() = default;
    gfxTexture(const gfxTexture& rhs) = delete;
    gfxTexture& operator=(const gfxTexture& rhs) = delete;
    gfxTexture(gfxTexture&& rhs);
    gfxTexture& operator=(gfxTexture&& rhs);
    ~gfxTexture();

public:
    void Create2D(const epiByte* initData,
                  epiU32 width,
                  epiU32 height,
                  gfxTextureFormat format,
                  gfxTexturePixelType pixelType);
    void Destroy();

    void Bind() override;
    void UnBind() override;

protected:
    internalgfx::gfxTextureImpl* m_Impl{nullptr};
};

EPI_NAMESPACE_END()
