#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

struct VkDevice_T;
struct VkFramebuffer_T;

EPI_NAMESPACE_BEGIN()

class gfxFrameBufferImplVK : public gfxFrameBuffer::Impl
{
public:
    explicit gfxFrameBufferImplVK(VkDevice_T* device);
    gfxFrameBufferImplVK(const gfxFrameBufferImplVK& rhs) = delete;
    gfxFrameBufferImplVK& operator=(const gfxFrameBufferImplVK& rhs) = delete;
    gfxFrameBufferImplVK(gfxFrameBufferImplVK&& rhs) = default;
    gfxFrameBufferImplVK& operator=(gfxFrameBufferImplVK&& rhs) = default;
    ~gfxFrameBufferImplVK() override;

    epiBool Init(const gfxFrameBufferCreateInfo& info, const internalgfx::gfxRenderPassImpl& renderPassImpl, const epiPtrArray<const internalgfx::gfxTextureViewImpl>& textureViewImpls);

    VkFramebuffer_T* GetVkFrameBuffer() const;

protected:
    VkDevice_T* m_VkDevice{nullptr};
    VkFramebuffer_T* m_VkFrameBuffer{nullptr};
};

EPI_NAMESPACE_END()
