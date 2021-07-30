#pragma once

#include "EpiGraphics/gfxDriverInternal.h"

struct VkImageView_T;
struct VkDevice_T;

EPI_NAMESPACE_BEGIN()

class gfxImageViewImplVK : public gfxImageView::Impl
{
public:
    explicit gfxImageViewImplVK(VkDevice_T* device);
    gfxImageViewImplVK(const gfxImageViewImplVK& rhs) = delete;
    gfxImageViewImplVK& operator=(const gfxImageViewImplVK& rhs) = delete;
    gfxImageViewImplVK(gfxImageViewImplVK&& rhs) = default;
    gfxImageViewImplVK& operator=(gfxImageViewImplVK&& rhs) = default;
    ~gfxImageViewImplVK() override;

    epiBool Init(const gfxImageViewCreateInfo& info);

    VkImageView_T* GetVkImageView() const;

protected:
    VkDevice_T* m_VkDevice{nullptr};
    VkImageView_T* m_VkImageView{nullptr};
};

EPI_NAMESPACE_END()
