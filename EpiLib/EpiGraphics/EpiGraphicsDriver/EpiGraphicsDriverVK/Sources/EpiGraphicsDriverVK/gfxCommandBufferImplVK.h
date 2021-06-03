#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

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

    epiBool RecordBegin(gfxCommandBufferUsage usage) override;
    epiBool RecordEnd() override;

    void RenderPassBegin(const gfxRenderPassBeginInfo& info, const gfxRenderPassImpl& renderPassImpl, const gfxFrameBufferImpl& frameBufferImpl) override;
    void RenderPassEnd() override;

    void PipelineBind(const gfxPipelineGraphicsImpl& pipeline) override;

    void VertexBuffersBind(const epiPtrArray<const gfxBufferImpl>& buffers, const epiArray<epiU32>& offsets = {}) override;
    void IndexBufferBind(const gfxBufferImpl& bufferImpl, gfxIndexBufferType type, epiU32 offset = 0) override;
    void DescriptorSetsBind(gfxPipelineBindPoint bindPoint,
                            const gfxPipelineLayout& pipelineLayout,
                            const epiArray<gfxDescriptorSet>& sets,
                            const epiArray<epiU32>& offsets,
                            epiU32 firstSet) override;

    void Draw(epiU32 vertexCount, epiU32 instanceCount, epiU32 firstVertex, epiU32 firstInstance) override;
    void DrawIndexed(epiU32 indexCount, epiU32 instanceCount, epiU32 firstIndex, epiU32 vertexOffset, epiU32 firstInstance) override;
    void Copy(const gfxBufferImpl& src, const gfxBufferImpl& dst, const epiArray<gfxCommandBufferRecordCopyRegion>& copyRegions) override;

    VkCommandBuffer_T* GetVkCommandBuffer() const;

protected:
    VkCommandBuffer_T* m_VkCommandBuffer{nullptr};
    epiBool m_IsPrimary{false};
};

} // namespace internalgfx

EPI_NAMESPACE_END()
