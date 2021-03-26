EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxCommandPool.h"
#include "EpiGraphicsDriverCommon/gfxCommandPool.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"
#include "EpiGraphicsDriverCommon/gfxFrameBuffer.h"
#include "EpiGraphicsDriverCommon/gfxRenderPass.h"

EPI_NAMESPACE_BEGIN()

gfxCommandBuffer::gfxCommandBuffer(internalgfx::gfxCommandBufferImpl* impl)
    : m_Impl{impl}
{
}

epiBool gfxCommandBuffer::GetIsPrimary_Callback() const
{
    return m_Impl->GetIsPrimary();
}

epiBool gfxCommandBuffer::RenderPassBegin(const gfxRenderPassBeginInfo & info)
{
    if (info.GetFrameBuffer() == nullptr)
    {
        epiLogError("Failed to begin RenderPass on CommandBuffer! FrameBuffer is not provided!");
        return false;
    }

    if (info.GetRenderPass() == nullptr)
    {
        epiLogError("Failed to begin RenderPass on CommandBuffer! RenderPass is not provided!");
        return false;
    }

    const internalgfx::gfxFrameBufferImpl* frameBufferImpl = info.GetFrameBuffer()->m_Impl;
    if (frameBufferImpl == nullptr)
    {
        epiLogError("Failed to begin RenderPass on CommandBuffer! FrameBuffer has no implementation!");
        return false;
    }

    const internalgfx::gfxRenderPassImpl* renderPassImpl = info.GetRenderPass()->m_Impl;
    if (renderPassImpl == nullptr)
    {
        epiLogError("Failed to begin RenderPass on CommandBuffer! RenderPass has no implementation!");
        return false;
    }

    return m_Impl->RenderPassBegin(info, *renderPassImpl, *frameBufferImpl);
}

epiBool gfxCommandBuffer::RenderPassEnd()
{
    return m_Impl->RenderPassEnd();
}

gfxCommandPool::gfxCommandPool(internalgfx::gfxCommandPoolImpl* impl)
    : m_Impl{impl}
{
}

gfxCommandPool::gfxCommandPool(gfxCommandPool&& rhs)
{
    m_Impl = rhs.m_Impl;

    rhs.m_Impl = nullptr;
}

gfxCommandPool& gfxCommandPool::operator=(gfxCommandPool&& rhs)
{
    m_Impl = rhs.m_Impl;

    rhs.m_Impl = nullptr;

    return *this;
}

gfxCommandPool::~gfxCommandPool()
{
    delete m_Impl;
}

std::optional<gfxCommandBuffer> gfxCommandPool::BufferAtPrimary(epiU32 index)
{
    std::optional<gfxCommandBuffer> commandBuffer;

    if (internalgfx::gfxCommandBufferImpl* commandBufferImpl = m_Impl->BufferAtPrimary(index))
    {
        commandBuffer = gfxCommandBuffer(commandBufferImpl);
    }

    return commandBuffer;
}

std::optional<gfxCommandBuffer> gfxCommandPool::BufferAtSecondary(epiU32 index)
{
    std::optional<gfxCommandBuffer> commandBuffer;

    if (internalgfx::gfxCommandBufferImpl* commandBufferImpl = m_Impl->BufferAtSecondary(index))
    {
        commandBuffer = gfxCommandBuffer(commandBufferImpl);
    }

    return commandBuffer;
}

EPI_NAMESPACE_END()
