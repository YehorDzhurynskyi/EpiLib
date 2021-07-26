#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

struct VkImage_T;
struct VkImageView_T;
struct VkDevice_T;

EPI_NAMESPACE_BEGIN()

class gfxTextureImplVK : public gfxTexture::Impl
{
public:
    explicit gfxTextureImplVK(VkImage_T* image);
    gfxTextureImplVK(const gfxTextureImplVK& rhs) = delete;
    gfxTextureImplVK& operator=(const gfxTextureImplVK& rhs) = delete;
    gfxTextureImplVK(gfxTextureImplVK&& rhs) = default;
    gfxTextureImplVK& operator=(gfxTextureImplVK&& rhs) = default;
    ~gfxTextureImplVK() override = default;

    VkImage_T* GetVkImage() const;

protected:
    VkImage_T* m_VkImage{nullptr};
};

class gfxTextureImplVKOwner : public gfxTextureImplVK
{
public:
    explicit gfxTextureImplVKOwner(VkDevice_T* device);
    gfxTextureImplVKOwner(const gfxTextureImplVKOwner& rhs) = delete;
    gfxTextureImplVKOwner& operator=(const gfxTextureImplVKOwner& rhs) = delete;
    gfxTextureImplVKOwner(gfxTextureImplVKOwner&& rhs) = default;
    gfxTextureImplVKOwner& operator=(gfxTextureImplVKOwner&& rhs) = default;
    ~gfxTextureImplVKOwner() override;

    epiBool Init(const gfxTextureCreateInfo& info);

protected:
    VkDevice_T* m_VkDevice{nullptr};
};

EPI_NAMESPACE_END()
