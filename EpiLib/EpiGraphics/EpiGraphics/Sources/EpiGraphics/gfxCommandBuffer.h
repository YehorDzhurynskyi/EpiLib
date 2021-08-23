#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxCommandBuffer.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphics/gfxEnum.h"
#include "EpiGraphics/gfxRenderPass.h"
#include "EpiGraphics/gfxFrameBuffer.h"
#include "EpiGraphics/gfxDescriptorSet.h"
#include "EpiGraphics/Synchronization/gfxSemaphore.h"

EPI_NAMESPACE_BEGIN()

class gfxRenderPassClearValue : public Object
{
EPI_GENREGION_BEGIN(gfxRenderPassClearValue)

EPI_GENHIDDEN_gfxRenderPassClearValue()

public:
    constexpr static epiMetaTypeID TypeID{0x81026e32};

    enum gfxRenderPassClearValue_PIDs
    {
        PID_Color = 0xa79767ed,
        PID_Depth = 0x3b62336d,
        PID_Stencil = 0x2f63936a,
        PID_COUNT = 3
    };

protected:
    epiVec4f m_Color{};
    epiFloat m_Depth{0.0f};
    epiU32 m_Stencil{0};

EPI_GENREGION_END(gfxRenderPassClearValue)
};

class gfxRenderPassBeginInfo : public Object
{
EPI_GENREGION_BEGIN(gfxRenderPassBeginInfo)

EPI_GENHIDDEN_gfxRenderPassBeginInfo()

public:
    constexpr static epiMetaTypeID TypeID{0x6151783c};

    enum gfxRenderPassBeginInfo_PIDs
    {
        PID_FrameBuffer = 0xf98a204d,
        PID_RenderPass = 0x662aa9d7,
        PID_RenderArea = 0x7fce409b,
        PID_ClearValues = 0x127d6743,
        PID_COUNT = 4
    };

protected:
    gfxFrameBuffer m_FrameBuffer{};
    gfxRenderPass m_RenderPass{};
    epiRect2s m_RenderArea{};
    epiArray<gfxRenderPassClearValue> m_ClearValues{};

EPI_GENREGION_END(gfxRenderPassBeginInfo)
};

class gfxCommandBufferRecordCopyRegion : public Object
{
EPI_GENREGION_BEGIN(gfxCommandBufferRecordCopyRegion)

EPI_GENHIDDEN_gfxCommandBufferRecordCopyRegion()

public:
    constexpr static epiMetaTypeID TypeID{0x197d8dfb};

    enum gfxCommandBufferRecordCopyRegion_PIDs
    {
        PID_Size = 0x57f28b54,
        PID_SrcOffset = 0x1699c7cd,
        PID_DstOffset = 0xb0eb4aab,
        PID_COUNT = 3
    };

protected:
    epiSize_t m_Size{0};
    epiSize_t m_SrcOffset{0};
    epiSize_t m_DstOffset{0};

EPI_GENREGION_END(gfxCommandBufferRecordCopyRegion)
};

class gfxCommandBufferRecordCopyBufferToImage : public Object
{
EPI_GENREGION_BEGIN(gfxCommandBufferRecordCopyBufferToImage)

EPI_GENHIDDEN_gfxCommandBufferRecordCopyBufferToImage()

public:
    constexpr static epiMetaTypeID TypeID{0xaf2e47cc};

    enum gfxCommandBufferRecordCopyBufferToImage_PIDs
    {
        PID_BufferOffset = 0xd7e09c30,
        PID_BufferRowLength = 0xaa97b8f2,
        PID_BufferImageHeight = 0xa85bff1e,
        PID_ImageSubresource = 0x29375a7b,
        PID_ImageOffset = 0x45472804,
        PID_ImageExtent = 0x3a43bb9c,
        PID_COUNT = 6
    };

protected:
    epiSize_t m_BufferOffset{0};
    epiU32 m_BufferRowLength{0};
    epiU32 m_BufferImageHeight{0};
    gfxImageSubresourceLayers m_ImageSubresource{};
    epiVec3s m_ImageOffset{};
    epiVec3u m_ImageExtent{};

EPI_GENREGION_END(gfxCommandBufferRecordCopyBufferToImage)
};

class gfxPipelineLayout;
class gfxPipelineGraphics;
class gfxCommandBufferRecordPipelineBarier;
class gfxCommandBuffer : public Object
{
EPI_GENREGION_BEGIN(gfxCommandBuffer)

EPI_GENHIDDEN_gfxCommandBuffer()

public:
    constexpr static epiMetaTypeID TypeID{0x29d43d9};

    enum gfxCommandBuffer_PIDs
    {
        PID_IsPrimary = 0xf3733be5,
        PID_COUNT = 1
    };

protected:
    epiBool GetIsPrimary_Callback() const;

EPI_GENREGION_END(gfxCommandBuffer)

public:
    class Impl;

    class Record
    {
    public:
        Record() = default;
        Record(const Record& rhs) = delete;
        Record& operator=(const Record& rhs) = delete;
        Record(Record&& rhs);
        Record& operator=(Record&& rhs);
        ~Record();

        void RecordBegin(gfxCommandBuffer::Impl* impl, gfxCommandBufferUsage usage);

        operator epiBool() const;

        Record& RenderPassBegin(const gfxRenderPassBeginInfo& info);
        Record& RenderPassEnd();

        Record& PipelineBind(const gfxPipelineGraphics& pipeline);
        Record& PipelineBarrier(const gfxCommandBufferRecordPipelineBarier& pipelineBarrier);

        Record& VertexBuffersBind(const epiArray<gfxBuffer>& buffers, const epiArray<epiU32>& offsets = {});
        Record& IndexBufferBind(const gfxBuffer& buffer, gfxIndexBufferType type, epiU32 offset = 0);
        Record& DescriptorSetsBind(gfxPipelineBindPoint bindPoint,
                                   const gfxPipelineLayout& pipelineLayout,
                                   const epiArray<gfxDescriptorSet>& sets,
                                   const epiArray<epiU32>& offsets = {},
                                   epiU32 firstSet = 0);

        Record& Draw(epiU32 vertexCount, epiU32 instanceCount, epiU32 firstVertex, epiU32 firstInstance);
        Record& DrawIndexed(epiU32 indexCount, epiU32 instanceCount, epiU32 firstIndex, epiU32 vertexOffset, epiU32 firstInstance);
        Record& Copy(const gfxBuffer& src, const gfxBuffer& dst, const epiArray<gfxCommandBufferRecordCopyRegion>& copyRegions);
        Record& Copy(const gfxBuffer& src, const gfxImage& dst, gfxImageLayout dstLayout, const epiArray<gfxCommandBufferRecordCopyBufferToImage>& copyRegions);

    protected:
        gfxCommandBuffer::Impl* m_Impl{nullptr};
        epiBool m_IsInitialized{false};
    };

public:
    gfxCommandBuffer() = default;
    explicit gfxCommandBuffer(const std::shared_ptr<Impl>& impl);

    epiBool HasImpl() const;

    Record RecordCommands(gfxCommandBufferUsage usage = gfxCommandBufferUsage{0});

protected:
    std::shared_ptr<Impl> m_Impl;
};

class gfxQueueSubmitInfo : public Object
{
EPI_GENREGION_BEGIN(gfxQueueSubmitInfo)

EPI_GENHIDDEN_gfxQueueSubmitInfo()

public:
    constexpr static epiMetaTypeID TypeID{0x37aceed2};

    enum gfxQueueSubmitInfo_PIDs
    {
        PID_WaitSemaphores = 0xde36b270,
        PID_WaitDstStageMasks = 0x5c9921bb,
        PID_SignalSemaphores = 0xa8746c09,
        PID_CommandBuffers = 0xc25694f,
        PID_COUNT = 4
    };

protected:
    epiArray<gfxSemaphore> m_WaitSemaphores{};
    epiArray<gfxPipelineStage> m_WaitDstStageMasks{};
    epiArray<gfxSemaphore> m_SignalSemaphores{};
    epiArray<gfxCommandBuffer> m_CommandBuffers{};

EPI_GENREGION_END(gfxQueueSubmitInfo)
};

EPI_NAMESPACE_END()
