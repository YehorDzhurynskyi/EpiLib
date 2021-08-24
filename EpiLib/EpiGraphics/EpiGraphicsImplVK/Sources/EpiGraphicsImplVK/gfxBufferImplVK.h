#pragma once

#include "EpiGraphicsImpl/gfxBufferImpl.h"

struct VkDevice_T;
struct VkBuffer_T;

EPI_NAMESPACE_BEGIN()

class gfxBufferImplVK : public gfxBuffer::Impl
{
public:
    explicit gfxBufferImplVK(const gfxDevice& device);
    gfxBufferImplVK(const gfxBufferImplVK& rhs) = delete;
    gfxBufferImplVK& operator=(const gfxBufferImplVK& rhs) = delete;
    gfxBufferImplVK(gfxBufferImplVK&& rhs) = default;
    gfxBufferImplVK& operator=(gfxBufferImplVK&& rhs) = default;
    ~gfxBufferImplVK() override;

    epiBool Init(const gfxBufferCreateInfo& info);
    epiBool Init(VkBuffer_T* buffer);

    VkBuffer_T* GetVkBuffer() const;

protected:
    VkBuffer_T* m_VkBuffer{nullptr};
};

EPI_NAMESPACE_END()
