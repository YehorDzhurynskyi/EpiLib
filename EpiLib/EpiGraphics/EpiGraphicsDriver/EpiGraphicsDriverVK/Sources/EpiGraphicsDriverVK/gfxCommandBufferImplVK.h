#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

struct VkCommandBuffer_T;

EPI_NAMESPACE_BEGIN()

class gfxCommandBufferImplVK : public gfxCommandBuffer::Impl
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

    void RenderPassBegin(const gfxRenderPassBeginInfo& info) override;
    void RenderPassEnd() override;

    void PipelineBind(const gfxPipelineGraphics& pipeline) override;
    void PipelineBarrier(const gfxCommandBufferRecordPipelineBarier& pipelineBarrier) override;

    void VertexBuffersBind(const epiArray<gfxBuffer>& buffers, const epiArray<epiU32>& offsets = {}) override;
    void IndexBufferBind(const gfxBuffer& buffer, gfxIndexBufferType type, epiU32 offset = 0) override;
    void DescriptorSetsBind(gfxPipelineBindPoint bindPoint,
                            const gfxPipelineLayout& pipelineLayout,
                            const epiArray<gfxDescriptorSet>& sets,
                            const epiArray<epiU32>& offsets,
                            epiU32 firstSet) override;

    void Draw(epiU32 vertexCount, epiU32 instanceCount, epiU32 firstVertex, epiU32 firstInstance) override;
    void DrawIndexed(epiU32 indexCount, epiU32 instanceCount, epiU32 firstIndex, epiU32 vertexOffset, epiU32 firstInstance) override;
    void Copy(const gfxBuffer& src, const gfxBuffer& dst, const epiArray<gfxCommandBufferRecordCopyRegion>& copyRegions) override;
    void Copy(const gfxBuffer& src, const gfxImage& dst, gfxImageLayout dstLayout, const epiArray<gfxCommandBufferRecordCopyBufferToImage>& copyRegions) override;

    VkCommandBuffer_T* GetVkCommandBuffer() const;

protected:
    VkCommandBuffer_T* m_VkCommandBuffer{nullptr};
    epiBool m_IsPrimary{false};
};

EPI_NAMESPACE_END()
