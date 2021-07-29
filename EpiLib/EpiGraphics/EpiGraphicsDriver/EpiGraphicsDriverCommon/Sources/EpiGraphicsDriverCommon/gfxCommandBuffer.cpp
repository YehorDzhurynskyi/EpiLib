EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxCommandBuffer.h"
#include "EpiGraphicsDriverCommon/gfxCommandBuffer.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxCommandBuffer::Record::Record(Record&& rhs)
{
    if (&rhs != this)
    {
        m_IsInitialized = rhs.m_IsInitialized;
        m_Impl = rhs.m_Impl;

        rhs.m_IsInitialized = false;
        rhs.m_Impl = nullptr;
    }
}

gfxCommandBuffer::Record& gfxCommandBuffer::Record::operator=(Record&& rhs)
{
    if (&rhs != this)
    {
        m_IsInitialized = rhs.m_IsInitialized;
        m_Impl = rhs.m_Impl;

        rhs.m_IsInitialized = false;
        rhs.m_Impl = nullptr;
    }

    return *this;
}

gfxCommandBuffer::Record::~Record()
{
    if (m_IsInitialized)
    {
        m_Impl->RecordEnd();
    }
}

void gfxCommandBuffer::Record::RecordBegin(gfxCommandBuffer::Impl* impl, gfxCommandBufferUsage usage)
{
    m_Impl = impl;
    m_IsInitialized = false;

    if (m_Impl != nullptr)
    {
        m_IsInitialized = m_Impl->RecordBegin(usage);
    }
}

gfxCommandBuffer::Record::operator epiBool() const
{
    return m_IsInitialized;
}

gfxCommandBuffer::Record& gfxCommandBuffer::Record::RenderPassBegin(const gfxRenderPassBeginInfo& info)
{
    if (!info.GetRenderPass().HasImpl())
    {
        epiLogError("Failed to begin RenderPass! Provided RenderPass has no implementation!");
        return *this;
    }

    if (!info.GetFrameBuffer().HasImpl())
    {
        epiLogError("Failed to begin RenderPass! Provided FrameBuffer has no implementation!");
        return *this;
    }

    m_Impl->RenderPassBegin(info);

    return *this;
}

gfxCommandBuffer::Record& gfxCommandBuffer::Record::RenderPassEnd()
{
    m_Impl->RenderPassEnd();

    return *this;
}

gfxCommandBuffer::Record& gfxCommandBuffer::Record::PipelineBind(const gfxPipelineGraphics& pipeline)
{
    if (!pipeline.HasImpl())
    {
        epiLogError("Failed to bind Pipeline! The provided Pipeline has no implementation!");
        return *this;
    }

    const epiBool allViewportsAreValid = std::all_of(pipeline.GetViewports().begin(),
                                                     pipeline.GetViewports().end(),
                                                     [](const gfxPipelineViewport& v)
    {
        return v.IsValid();
    });

    if (!allViewportsAreValid)
    {
        epiLogError("Failed to bind Pipeline! The provided Pipeline has invalid viewport!");
        return *this;
    }

    m_Impl->PipelineBind(pipeline);

    return *this;
}

gfxCommandBuffer::Record& gfxCommandBuffer::Record::PipelineBarrier(const gfxCommandBufferRecordPipelineBarier& pipelineBarrier)
{
    const epiBool bufferMemoryBarriersValid = std::all_of(pipelineBarrier.GetBufferMemoryBarriers().begin(),
                                                          pipelineBarrier.GetBufferMemoryBarriers().end(),
                                                          [](const gfxBufferMemoryBarrier& barrier)
    {
        return barrier.GetBuffer().HasImpl();
    });

    if (!bufferMemoryBarriersValid)
    {
        epiLogError("Failed to barrier Pipeline! Some of the provided BufferMemoryBarrier has no Buffer implementation!");
        return *this;
    }

    const epiBool imageMemoryBarriersValid = std::all_of(pipelineBarrier.GetImageMemoryBarriers().begin(),
                                                         pipelineBarrier.GetImageMemoryBarriers().end(),
                                                         [](const gfxImageMemoryBarrier& barrier)
    {
        return barrier.GetImage().HasImpl();
    });

    if (!imageMemoryBarriersValid)
    {
        epiLogError("Failed to barrier Pipeline! Some of the provided ImageMemoryBarrier has no Image implementation!");
        return *this;
    }

    m_Impl->PipelineBarrier(pipelineBarrier);

    return *this;
}

gfxCommandBuffer::Record& gfxCommandBuffer::Record::VertexBuffersBind(const epiArray<gfxBuffer>& buffers, const epiArray<epiU32>& offsets)
{
    const epiBool allBuffersAreValid = std::all_of(buffers.begin(), buffers.end(), [](const gfxBuffer& buffer)
    {
        return buffer.HasImpl();
    });

    if (!allBuffersAreValid)
    {
        epiLogError("Failed to bind vertex Buffers! Some of the provided Buffers have no implementation!");
        return *this;
    }

    m_Impl->VertexBuffersBind(buffers, offsets);

    return *this;
}

gfxCommandBuffer::Record& gfxCommandBuffer::Record::IndexBufferBind(const gfxBuffer& buffer, gfxIndexBufferType type, epiU32 offset)
{
    if (!buffer.HasImpl())
    {
        epiLogError("Failed to bind Index Buffer! The provided Buffer has no implementation!");
        return *this;
    }

    m_Impl->IndexBufferBind(buffer, type, offset);

    return *this;
}

gfxCommandBuffer::Record& gfxCommandBuffer::Record::DescriptorSetsBind(gfxPipelineBindPoint bindPoint,
                                                                                                       const gfxPipelineLayout& pipelineLayout,
                                                                                                       const epiArray<gfxDescriptorSet>& sets,
                                                                                                       const epiArray<epiU32>& offsets,
                                                                                                       epiU32 firstSet)
{
    m_Impl->DescriptorSetsBind(bindPoint, pipelineLayout, sets, offsets, firstSet);

    return *this;
}

gfxCommandBuffer::Record& gfxCommandBuffer::Record::Draw(epiU32 vertexCount, epiU32 instanceCount, epiU32 firstVertex, epiU32 firstInstance)
{
    m_Impl->Draw(vertexCount, instanceCount, firstVertex, firstInstance);

    return *this;
}

gfxCommandBuffer::Record& gfxCommandBuffer::Record::DrawIndexed(epiU32 indexCount, epiU32 instanceCount, epiU32 firstIndex, epiU32 vertexOffset, epiU32 firstInstance)
{
    m_Impl->DrawIndexed(indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);

    return *this;
}

gfxCommandBuffer::Record& gfxCommandBuffer::Record::Copy(const gfxBuffer& src, const gfxBuffer& dst, const epiArray<gfxCommandBufferRecordCopyRegion>& copyRegions)
{
    if (!src.HasImpl())
    {
        epiLogError("Failed to Copy! The provided source Buffer has no implementation!");
        return *this;
    }

    if (!dst.HasImpl())
    {
        epiLogError("Failed to Copy! The provided destination Buffer has no implementation!");
        return *this;
    }

    m_Impl->Copy(src, dst, copyRegions);

    return *this;
}

gfxCommandBuffer::Record& gfxCommandBuffer::Record::Copy(const gfxBuffer& src, const gfxImage& dst, gfxImageLayout dstLayout, const epiArray<gfxCommandBufferRecordCopyBufferToImage>& copyRegions)
{
    if (!src.HasImpl())
    {
        epiLogError("Failed to Copy! Source Buffer has no implementation!");
        return *this;
    }

    if (!dst.HasImpl())
    {
        epiLogError("Failed to Copy! Destination Image has no implementation!");
        return *this;
    }

    m_Impl->Copy(src, dst, dstLayout, copyRegions);

    return *this;
}

gfxCommandBuffer::gfxCommandBuffer(const std::shared_ptr<Impl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxCommandBuffer::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

gfxCommandBuffer::Record gfxCommandBuffer::RecordCommands(gfxCommandBufferUsage usage)
{
    Record record;
    record.RecordBegin(m_Impl.get(), usage);

    return record;
}

epiBool gfxCommandBuffer::GetIsPrimary_Callback() const
{
    return m_Impl->GetIsPrimary();
}

EPI_NAMESPACE_END()
