#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

struct VkDevice_T;
struct VkCommandPool_T;
struct VkCommandBuffer_T;

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxCommandBufferImplVK : public gfxCommandBufferImpl
{
public:
    gfxCommandBufferImplVK(VkCommandBuffer_T* commandBuffer, epiBool isPrimary);
    gfxCommandBufferImplVK(const gfxCommandBufferImplVK& rhs) = delete;
    gfxCommandBufferImplVK& operator=(const gfxCommandBufferImplVK& rhs) = delete;
    gfxCommandBufferImplVK(gfxCommandBufferImplVK&& rhs) = default;
    gfxCommandBufferImplVK& operator=(gfxCommandBufferImplVK&& rhs) = default;
    ~gfxCommandBufferImplVK() override = default;

    epiBool RenderPassBegin(const gfxRenderPassBeginInfo& info, const gfxRenderPassImpl& renderPassImpl, const gfxFrameBufferImpl& frameBufferImpl) const override;
    epiBool RenderPassEnd() const override;

    VkCommandBuffer_T* GetVkCommandBuffer() const;

protected:
    VkCommandBuffer_T* m_VkCommandBuffer{nullptr};
    epiBool m_IsPrimary{false};
};

class gfxCommandPoolImplVK : public gfxCommandPoolImpl
{
public:
    explicit gfxCommandPoolImplVK(VkDevice_T* device);
    gfxCommandPoolImplVK(const gfxCommandPoolImplVK& rhs) = delete;
    gfxCommandPoolImplVK& operator=(const gfxCommandPoolImplVK& rhs) = delete;
    gfxCommandPoolImplVK(gfxCommandPoolImplVK&& rhs) = default;
    gfxCommandPoolImplVK& operator=(gfxCommandPoolImplVK&& rhs) = default;
    ~gfxCommandPoolImplVK() override;

    epiBool Init(const gfxCommandPoolCreateInfo& info, const gfxQueueFamilyImpl* queueFamilyImpl);

protected:
    VkDevice_T* m_VkDevice{nullptr};
    VkCommandPool_T* m_VkCommandPool{nullptr};
    std::vector<std::unique_ptr<gfxCommandBufferImplVK>> m_PrimaryCommandBuffers;
    std::vector<std::unique_ptr<gfxCommandBufferImplVK>> m_SecondaryCommandBuffers;
};

} // namespace internalgfx

EPI_NAMESPACE_END()
