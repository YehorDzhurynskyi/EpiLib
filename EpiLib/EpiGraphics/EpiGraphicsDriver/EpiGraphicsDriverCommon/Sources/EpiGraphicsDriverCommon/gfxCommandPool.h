#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxCommandPool.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxRenderPass.h"
#include "EpiGraphicsDriverCommon/gfxQueueFamily.h"
#include "EpiGraphicsDriverCommon/gfxFrameBuffer.h"
#include "EpiGraphicsDriverCommon/gfxBuffer.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxCommandPoolImpl;
class gfxCommandBufferImpl;

} // internalgfx

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

class gfxFrameBuffer;
class gfxRenderPass;
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

class gfxCommandBufferRecord : public Object
{
EPI_GENREGION_BEGIN(gfxCommandBufferRecord)

EPI_GENHIDDEN_gfxCommandBufferRecord()

public:
    constexpr static epiMetaTypeID TypeID{0xfa5418ce};

    enum gfxCommandBufferRecord_PIDs
    {
        PID_IsInitialized = 0x101015d0,
        PID_COUNT = 1
    };

protected:
    epiBool m_IsInitialized{false};

EPI_GENREGION_END(gfxCommandBufferRecord)

public:
    explicit gfxCommandBufferRecord(internalgfx::gfxCommandBufferImpl* impl);
    ~gfxCommandBufferRecord();

    operator epiBool() const;

    gfxCommandBufferRecord& RenderPassBegin(const gfxRenderPassBeginInfo& info);
    gfxCommandBufferRecord& RenderPassEnd();

    gfxCommandBufferRecord& PipelineBind(const gfxPipelineGraphics& pipeline);

    gfxCommandBufferRecord& VertexBuffersBind(const epiArray<gfxBuffer>& buffers, const epiArray<epiU32>& offsets = {});

    gfxCommandBufferRecord& Draw(epiU32 vertexCount, epiU32 instanceCount, epiU32 firstVertex, epiU32 firstInstance);

protected:
    internalgfx::gfxCommandBufferImpl* m_Impl{nullptr};
};

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
    gfxCommandBuffer() = default;
    explicit gfxCommandBuffer(const std::shared_ptr<internalgfx::gfxCommandBufferImpl>& impl);

    gfxCommandBufferRecord RecordCommands();

protected:
    epiPimpl<internalgfx::gfxCommandBufferImpl> m_Impl;
};

class gfxQueueFamily;
class gfxCommandPoolCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxCommandPoolCreateInfo)

EPI_GENHIDDEN_gfxCommandPoolCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0xd83ebde9};

    enum gfxCommandPoolCreateInfo_PIDs
    {
        PID_QueueFamily = 0xfa954047,
        PID_PrimaryCommandBufferCount = 0x180011ae,
        PID_SecondaryCommandBufferCount = 0x62333abe,
        PID_COUNT = 3
    };

protected:
    gfxQueueFamily m_QueueFamily{};
    epiU32 m_PrimaryCommandBufferCount{0};
    epiU32 m_SecondaryCommandBufferCount{0};

EPI_GENREGION_END(gfxCommandPoolCreateInfo)
};

class gfxCommandPool : public Object
{
EPI_GENREGION_BEGIN(gfxCommandPool)

EPI_GENHIDDEN_gfxCommandPool()

public:
    constexpr static epiMetaTypeID TypeID{0x60157c7f};

    enum gfxCommandPool_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxCommandPool)

public:
    gfxCommandPool() = default;
    explicit gfxCommandPool(const std::shared_ptr<internalgfx::gfxCommandPoolImpl>& impl);

protected:
    epiPimpl<internalgfx::gfxCommandPoolImpl> m_Impl;
};

EPI_NAMESPACE_END()
