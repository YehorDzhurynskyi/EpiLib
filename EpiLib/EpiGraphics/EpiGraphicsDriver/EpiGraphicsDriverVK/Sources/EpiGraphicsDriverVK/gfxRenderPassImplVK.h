#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

struct VkRenderPass_T;
struct VkDevice_T;

EPI_NAMESPACE_BEGIN()

class gfxRenderPassImplVK : public gfxRenderPass::Impl
{
public:
    gfxRenderPassImplVK(VkDevice_T* device);
    gfxRenderPassImplVK(const gfxRenderPassImplVK& rhs) = delete;
    gfxRenderPassImplVK& operator=(const gfxRenderPassImplVK& rhs) = delete;
    gfxRenderPassImplVK(gfxRenderPassImplVK&& rhs) = default;
    gfxRenderPassImplVK& operator=(gfxRenderPassImplVK&& rhs) = default;
    ~gfxRenderPassImplVK() override;

    epiBool Init(const gfxRenderPassCreateInfo& info);

    VkRenderPass_T* GetVkRenderPass() const;

protected:
    VkRenderPass_T* m_VkRenderPass{nullptr};
    VkDevice_T* m_VkDevice{nullptr};
};

EPI_NAMESPACE_END()
