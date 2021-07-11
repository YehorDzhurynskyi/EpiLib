#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"
#include "EpiGraphicsDriverCommon/gfxBuffer.h"

struct VkDevice_T;
struct VkBuffer_T;

EPI_NAMESPACE_BEGIN()

class gfxBufferImplVK : public gfxBuffer::Impl
{
public:
    explicit gfxBufferImplVK(VkDevice_T* device);
    gfxBufferImplVK(const gfxBufferImplVK& rhs) = delete;
    gfxBufferImplVK& operator=(const gfxBufferImplVK& rhs) = delete;
    gfxBufferImplVK(gfxBufferImplVK&& rhs) = default;
    gfxBufferImplVK& operator=(gfxBufferImplVK&& rhs) = default;
    ~gfxBufferImplVK() override;

    epiBool Init(const gfxBufferCreateInfo& info);

    VkBuffer_T* GetVkBuffer() const;

protected:
    VkDevice_T* m_VkDevice{nullptr};
    VkBuffer_T* m_VkBuffer{nullptr};
};

EPI_NAMESPACE_END()
