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

epiBool gfxCommandBuffer::RenderPassBegin(const gfxRenderPassBeginInfo & info)
{
    const auto frameBufferImpl = info.GetFrameBuffer().m_Impl;
    if (!frameBufferImpl)
    {
        epiLogError("Failed to begin RenderPass on CommandBuffer! FrameBuffer has no implementation!");
        return false;
    }

    const auto renderPassImpl = info.GetRenderPass().m_Impl;
    if (!renderPassImpl)
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

gfxCommandPool::gfxCommandPool(const std::shared_ptr<internalgfx::gfxCommandPoolImpl>& impl)
    : m_Impl{impl}
{
}

EPI_NAMESPACE_END()
