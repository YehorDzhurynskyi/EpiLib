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

    epiBool GetIsPrimary() const override;

    epiBool RecordBegin() override;
    epiBool RecordEnd() override;

    void RenderPassBegin(const gfxRenderPassBeginInfo& info, const gfxRenderPassImpl& renderPassImpl, const gfxFrameBufferImpl& frameBufferImpl) override;
    void RenderPassEnd() override;

    void PipelineBind(const gfxPipelineGraphicsImpl& pipeline) override;

    void VertexBuffersBind(const epiPtrArray<const gfxBufferImpl>& buffers, const epiArray<epiU32>& offsets = {}) override;

    void Draw(epiU32 vertexCount, epiU32 instanceCount, epiU32 firstVertex, epiU32 firstInstance) override;

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

    epiBool Init(const gfxCommandPoolCreateInfo& info, const gfxQueueFamilyImpl& queueFamilyImpl);

protected:
    VkDevice_T* m_VkDevice{nullptr};
    VkCommandPool_T* m_VkCommandPool{nullptr};
};

} // namespace internalgfx

EPI_NAMESPACE_END()
