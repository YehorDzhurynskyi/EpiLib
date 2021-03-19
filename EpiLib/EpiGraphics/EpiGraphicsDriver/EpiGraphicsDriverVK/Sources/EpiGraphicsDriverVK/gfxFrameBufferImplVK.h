#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

struct VkDevice_T;
struct VkFramebuffer_T;

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxFrameBufferImplVK : public gfxFrameBufferImpl
{
public:
    explicit gfxFrameBufferImplVK(VkDevice_T* device);
    gfxFrameBufferImplVK(const gfxFrameBufferImplVK& rhs) = delete;
    gfxFrameBufferImplVK& operator=(const gfxFrameBufferImplVK& rhs) = delete;
    gfxFrameBufferImplVK(gfxFrameBufferImplVK&& rhs) = default;
    gfxFrameBufferImplVK& operator=(gfxFrameBufferImplVK&& rhs) = default;
    ~gfxFrameBufferImplVK() override;

    epiBool Init(const gfxFrameBufferCreateInfo& info, const gfxRenderPassImpl* renderPassImpl);

protected:
    VkDevice_T* m_VkDevice{nullptr};
    VkFramebuffer_T* m_VkFrameBuffer{nullptr};
};

} // namespace internalgfx

EPI_NAMESPACE_END()
