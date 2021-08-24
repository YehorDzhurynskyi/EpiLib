#pragma once

#include "EpiGraphicsImpl/gfxImageImpl.h"

struct VkImage_T;
struct VkImageView_T;
struct VkDevice_T;

EPI_NAMESPACE_BEGIN()

class gfxImageImplVK : public gfxImage::Impl
{
public:
    explicit gfxImageImplVK(const gfxDevice& device);
    gfxImageImplVK(const gfxImageImplVK& rhs) = delete;
    gfxImageImplVK& operator=(const gfxImageImplVK& rhs) = delete;
    gfxImageImplVK(gfxImageImplVK&& rhs) = default;
    gfxImageImplVK& operator=(gfxImageImplVK&& rhs) = default;
    ~gfxImageImplVK() override;

    epiBool Init(const gfxImageCreateInfo& info);
    epiBool Init(VkImage_T* image);

    VkImage_T* GetVkImage() const;

protected:
    VkImage_T* m_VkImage{nullptr};
};

class gfxImageImplVKSwapChain : public gfxImage::Impl
{
public:
    gfxImageImplVKSwapChain(const gfxDevice& device, VkImage_T* image);

    VkImage_T* GetVkImage() const;

protected:
    VkImage_T* m_VkImage{nullptr};
};

EPI_NAMESPACE_END()
