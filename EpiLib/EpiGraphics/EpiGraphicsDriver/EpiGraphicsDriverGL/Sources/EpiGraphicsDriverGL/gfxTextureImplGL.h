#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxTextureImplGL : public gfxTextureImpl
{
public:
    gfxTextureImplGL() = default;
    gfxTextureImplGL(const gfxTextureImplGL& rhs) = delete;
    gfxTextureImplGL& operator=(const gfxTextureImplGL& rhs) = delete;
    gfxTextureImplGL(gfxTextureImplGL&& rhs);
    gfxTextureImplGL& operator=(gfxTextureImplGL&& rhs);
    ~gfxTextureImplGL() override = default;

    void Create2D(const epiByte* initData,
                  epiU32 width,
                  epiU32 height,
                  gfxTextureFormat format,
                  gfxTexturePixelType pixelType) override;
    void Destroy() override;

    epiU32 GetWidth() const override;
    epiU32 GetHeight() const override;
    epiBool GetIsCreated() const override;
    epiU32 GetID() const override;
    gfxTextureType GetType() const override;

    void Bind() override;
    void UnBind() override;

protected:
    epiU32 m_ID{0};
    epiU32 m_Width{0};
    epiU32 m_Height{0};
    gfxTextureType m_Type{gfxTextureType::None};
};

} // namespace internalgfx

EPI_NAMESPACE_END()
