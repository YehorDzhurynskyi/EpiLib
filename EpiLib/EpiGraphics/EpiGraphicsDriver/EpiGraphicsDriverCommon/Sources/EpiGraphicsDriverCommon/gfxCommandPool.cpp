EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxCommandPool.h"
#include "EpiGraphicsDriverCommon/gfxCommandPool.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"
#include "EpiGraphicsDriverCommon/gfxFrameBuffer.h"
#include "EpiGraphicsDriverCommon/gfxRenderPass.h"

EPI_NAMESPACE_BEGIN()

gfxCommandBuffer::gfxCommandBuffer(const std::shared_ptr<internalgfx::gfxCommandBufferImpl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxCommandBuffer::GetIsPrimary_Callback() const
{
    return m_Impl->GetIsPrimary();
}

gfxCommandBufferRecord gfxCommandBuffer::RecordCommands()
{
    return gfxCommandBufferRecord(m_Impl.Ptr());
}

gfxCommandBufferRecord::gfxCommandBufferRecord(internalgfx::gfxCommandBufferImpl* impl)
    : m_Impl{impl}
{
    if (m_Impl)
    {
        m_IsInitialized = m_Impl->RecordBegin();
    }
}

gfxCommandBufferRecord::~gfxCommandBufferRecord()
{
    if (GetIsInitialized())
    {
        m_Impl->RecordEnd();
    }
}

gfxCommandBufferRecord::operator epiBool() const
{
    return GetIsInitialized();
}

gfxCommandBufferRecord& gfxCommandBufferRecord::RenderPassBegin(const gfxRenderPassBeginInfo& info)
{
    const auto renderPassImpl = info.GetRenderPass().m_Impl;
    if (!renderPassImpl)
    {
        epiLogError("Failed to begin RenderPass! Provided RenderPass has no implementation!");
        return *this;
    }

    const auto frameBufferImpl = info.GetFrameBuffer().m_Impl;
    if (!frameBufferImpl)
    {
        epiLogError("Failed to begin RenderPass! Provided FrameBuffer has no implementation!");
        return *this;
    }

    m_Impl->RenderPassBegin(info, *renderPassImpl, *frameBufferImpl);

    return *this;
}

gfxCommandBufferRecord& gfxCommandBufferRecord::RenderPassEnd()
{
    m_Impl->RenderPassEnd();

    return *this;
}

gfxCommandBufferRecord& gfxCommandBufferRecord::PipelineBind(const gfxPipelineGraphics& pipeline)
{
    const auto pipelineImpl = pipeline.m_Impl;
    if (!pipelineImpl)
    {
        epiLogError("Failed to bind Pipeline! Provided Pipeline has no implementation!");
        return *this;
    }

    const epiBool hasInvalidViewport = std::any_of(pipeline.GetViewports().begin(),
                                                   pipeline.GetViewports().end(),
                                                   [](const gfxPipelineViewport& v)
    {
        return !v.IsValid();
    });

    if (hasInvalidViewport)
    {
        epiLogError("Failed to bind Pipeline! Provided Pipeline has invalid viewports!");
        return *this;
    }

    m_Impl->PipelineBind(*pipelineImpl);

    return *this;
}

gfxCommandBufferRecord& gfxCommandBufferRecord::VertexBuffersBind(const epiArray<gfxBuffer>& buffers, const epiArray<epiU32>& offsets)
{
    epiPtrArray<const internalgfx::gfxBufferImpl> buffersImpl;
    buffersImpl.Reserve(buffers.Size());

    std::transform(buffers.begin(), buffers.end(), std::back_inserter(buffersImpl), [](const gfxBuffer& buffer)
    {
        return buffer.m_Impl.Ptr();
    });

    if (buffersImpl.Size() != buffers.Size())
    {
        epiLogError("Failed to bind Vertex Buffers! Some of the provided Buffers has no implementation!");
        return *this;
    }

    m_Impl->VertexBuffersBind(buffersImpl, offsets);

    return *this;
}

gfxCommandBufferRecord& gfxCommandBufferRecord::Draw(epiU32 vertexCount, epiU32 instanceCount, epiU32 firstVertex, epiU32 firstInstance)
{
    m_Impl->Draw(vertexCount, instanceCount, firstVertex, firstInstance);

    return *this;
}

gfxCommandPool::gfxCommandPool(const std::shared_ptr<internalgfx::gfxCommandPoolImpl>& impl)
    : m_Impl{impl}
{
}

EPI_NAMESPACE_END()
