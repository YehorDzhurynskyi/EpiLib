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
    explicit gfxTextureImplVK(VkDevice_T* device);
    gfxTextureImplVK(const gfxTextureImplVK& rhs) = delete;
    gfxTextureImplVK& operator=(const gfxTextureImplVK& rhs) = delete;
    gfxTextureImplVK(gfxTextureImplVK&& rhs) = default;
    gfxTextureImplVK& operator=(gfxTextureImplVK&& rhs) = default;
    ~gfxTextureImplVK() override;

    epiBool Init(const gfxTextureCreateInfo& info);

    VkImage_T* GetVkImage() const;

protected:
    VkDevice_T* m_VkDevice{nullptr};
    VkImage_T* m_VkImage{nullptr};
};

} // namespace internalgfx

EPI_NAMESPACE_END()
