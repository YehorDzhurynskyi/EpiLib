EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxCommandPool.h"
#include "EpiGraphicsDriverCommon/gfxCommandPool.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxCommandBuffer::gfxCommandBuffer(internalgfx::gfxCommandBufferImpl* impl)
    : m_Impl{impl}
{
}

gfxCommandBuffer::gfxCommandBuffer(gfxCommandBuffer&& rhs)
{
    m_Impl = rhs.m_Impl;

    rhs.m_Impl = nullptr;
}

gfxCommandBuffer& gfxCommandBuffer::operator=(gfxCommandBuffer&& rhs)
{
    m_Impl = rhs.m_Impl;

    rhs.m_Impl = nullptr;

    return *this;
}

gfxCommandBuffer::~gfxCommandBuffer()
{
    delete m_Impl;
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

EPI_NAMESPACE_END()
