#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

struct VkRenderPass_T;
struct VkDevice_T;

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxRenderPassImplVK : public gfxRenderPassImpl
{
public:
    gfxRenderPassImplVK(VkDevice_T* device);
    gfxRenderPassImplVK(const gfxRenderPassImplVK& rhs) = delete;
    gfxRenderPassImplVK& operator=(const gfxRenderPassImplVK& rhs) = delete;
    gfxRenderPassImplVK(gfxRenderPassImplVK&& rhs) = default;
    gfxRenderPassImplVK& operator=(gfxRenderPassImplVK&& rhs) = default;
    ~gfxRenderPassImplVK() override;

    epiBool Init(const gfxRenderPassCreateInfo& info);
    epiBool Init(const gfxRenderPassSchema& schema);

    VkRenderPass_T* GetVkRenderPass() const;

protected:
    VkRenderPass_T* m_VkRenderPass{nullptr};
    VkDevice_T* m_VkDevice{nullptr};
};

} // namespace internalgfx

EPI_NAMESPACE_END()
