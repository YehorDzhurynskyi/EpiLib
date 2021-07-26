#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

struct VkImageView_T;
struct VkDevice_T;

EPI_NAMESPACE_BEGIN()

class gfxTextureViewImplVK : public gfxTextureView::Impl
{
public:
    explicit gfxTextureViewImplVK(VkDevice_T* device);
    gfxTextureViewImplVK(const gfxTextureViewImplVK& rhs) = delete;
    gfxTextureViewImplVK& operator=(const gfxTextureViewImplVK& rhs) = delete;
    gfxTextureViewImplVK(gfxTextureViewImplVK&& rhs) = default;
    gfxTextureViewImplVK& operator=(gfxTextureViewImplVK&& rhs) = default;
    ~gfxTextureViewImplVK() override;

    epiBool Init(const gfxTextureViewCreateInfo& info);

    VkImageView_T* GetVkImageView() const;

protected:
    VkDevice_T* m_VkDevice{nullptr};
    VkImageView_T* m_VkImageView{nullptr};
};

EPI_NAMESPACE_END()
