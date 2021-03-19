#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

struct VkImage_T;
struct VkImageView_T;
struct VkDevice_T;

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxTextureImplVK : public gfxTextureImpl
{
public:
    gfxTextureImplVK(VkDevice_T* device, VkImage_T* image);
    gfxTextureImplVK(const gfxTextureImplVK& rhs) = delete;
    gfxTextureImplVK& operator=(const gfxTextureImplVK& rhs) = delete;
    gfxTextureImplVK(gfxTextureImplVK&& rhs);
    gfxTextureImplVK& operator=(gfxTextureImplVK&& rhs);
    ~gfxTextureImplVK() override = default;

    epiBool Create2D(const epiByte* initData,
                     epiU32 width,
                     epiU32 height,
                     gfxFormat format,
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
    VkImage_T* m_VkImage{nullptr};
    VkImageView_T* m_VkImageView{nullptr};
    VkDevice_T* m_VkDevice{nullptr};
    epiU32 m_Width{0};
    epiU32 m_Height{0};
    gfxTextureType m_Type{gfxTextureType::None};
};

} // namespace internalgfx

EPI_NAMESPACE_END()
