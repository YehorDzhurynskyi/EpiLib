EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxFrameBuffer.h"
#include "EpiGraphicsDriverCommon/gfxFrameBuffer.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

void gfxFrameBufferCreateInfo::AddAttachment(gfxFramebufferAttachmentImageInfo&& info)
{
    m_AttachmentImageInfos.push_back(std::move(info));
}

gfxFrameBuffer::gfxFrameBuffer(const std::shared_ptr<internalgfx::gfxFrameBufferImpl>& impl)
    : m_Impl{impl}
{
}

EPI_NAMESPACE_END()
