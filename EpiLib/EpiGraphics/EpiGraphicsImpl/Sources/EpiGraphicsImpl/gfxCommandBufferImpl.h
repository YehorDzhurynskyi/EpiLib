#pragma once

#include "EpiGraphics/gfxCommandBuffer.h"

EPI_NAMESPACE_BEGIN()

class gfxCommandBuffer::Impl
{
public:
    static std::shared_ptr<gfxCommandBuffer::Impl> ExtractImpl(const gfxCommandBuffer& commandBuffer) { return commandBuffer.m_Impl; }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    virtual epiBool GetIsPrimary() const = 0;

    virtual epiBool RecordBegin(gfxCommandBufferUsage usage) = 0;
    virtual epiBool RecordEnd() = 0;

    virtual void RenderPassBegin(const gfxRenderPassBeginInfo& info) = 0;
    virtual void RenderPassEnd() = 0;

    virtual void PipelineBind(const gfxPipelineGraphics& pipeline) = 0;
    virtual void PipelineBarrier(const gfxCommandBufferRecordPipelineBarier& pipelineBarrier) = 0;

    virtual void VertexBuffersBind(const epiArray<gfxBuffer>& buffers, const epiArray<epiU32>& offsets = {}) = 0;
    virtual void IndexBufferBind(const gfxBuffer& buffer, gfxIndexBufferType type, epiU32 offset = 0) = 0;
    virtual void DescriptorSetsBind(gfxPipelineBindPoint bindPoint,
                                    const gfxPipelineLayout& pipelineLayout,
                                    const epiArray<gfxDescriptorSet>& sets,
                                    const epiArray<epiU32>& offsets,
                                    epiU32 firstSet) = 0;

    virtual void Draw(epiU32 vertexCount, epiU32 instanceCount, epiU32 firstVertex, epiU32 firstInstance) = 0;
    virtual void DrawIndexed(epiU32 indexCount, epiU32 instanceCount, epiU32 firstIndex, epiU32 vertexOffset, epiU32 firstInstance) = 0;
    virtual void Copy(const gfxBuffer& src, const gfxBuffer& dst, const epiArray<gfxCommandBufferRecordCopyRegion>& copyRegions) = 0;
    virtual void Copy(const gfxBuffer& src, const gfxImage& dst, gfxImageLayout dstLayout, const epiArray<gfxCommandBufferRecordCopyBufferToImage>& copyRegions) = 0;
};

EPI_NAMESPACE_END()
