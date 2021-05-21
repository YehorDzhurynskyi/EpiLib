#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

struct VkImageView_T;
struct VkDevice_T;

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxTextureViewImplVK : public gfxTextureViewImpl
{
public:
    explicit gfxTextureViewImplVK(VkDevice_T* device);
    gfxTextureViewImplVK(const gfxTextureViewImplVK& rhs) = delete;
    gfxTextureViewImplVK& operator=(const gfxTextureViewImplVK& rhs) = delete;
    gfxTextureViewImplVK(gfxTextureViewImplVK&& rhs) = default;
    gfxTextureViewImplVK& operator=(gfxTextureViewImplVK&& rhs) = default;
    ~gfxTextureViewImplVK() override;

    epiBool Init(const gfxTextureViewCreateInfo& info, const gfxTextureImpl& textureImpl);

    VkImageView_T* GetVkImageView() const;

protected:
    VkDevice_T* m_VkDevice{nullptr};
    VkImageView_T* m_VkImageView{nullptr};
};

} // namespace internalgfx

EPI_NAMESPACE_END()
