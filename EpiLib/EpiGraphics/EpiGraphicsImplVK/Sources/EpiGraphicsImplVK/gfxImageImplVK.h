#pragma once

#include "EpiGraphicsImpl/gfxImageImpl.h"

struct VkImage_T;
struct VkImageView_T;
struct VkDevice_T;

EPI_NAMESPACE_BEGIN()

class gfxImageImplVK : public gfxImage::Impl
{
public:
    explicit gfxImageImplVK(VkImage_T* image);
    gfxImageImplVK(const gfxImageImplVK& rhs) = delete;
    gfxImageImplVK& operator=(const gfxImageImplVK& rhs) = delete;
    gfxImageImplVK(gfxImageImplVK&& rhs) = default;
    gfxImageImplVK& operator=(gfxImageImplVK&& rhs) = default;
    ~gfxImageImplVK() override = default;

    VkImage_T* GetVkImage() const;

protected:
    VkImage_T* m_VkImage{nullptr};
};

class gfxImageImplVKOwner : public gfxImageImplVK
{
public:
    explicit gfxImageImplVKOwner(VkDevice_T* device);
    gfxImageImplVKOwner(const gfxImageImplVKOwner& rhs) = delete;
    gfxImageImplVKOwner& operator=(const gfxImageImplVKOwner& rhs) = delete;
    gfxImageImplVKOwner(gfxImageImplVKOwner&& rhs) = default;
    gfxImageImplVKOwner& operator=(gfxImageImplVKOwner&& rhs) = default;
    ~gfxImageImplVKOwner() override;

    epiBool Init(const gfxImageCreateInfo& info);

protected:
    VkDevice_T* m_VkDevice{nullptr};
};

EPI_NAMESPACE_END()
