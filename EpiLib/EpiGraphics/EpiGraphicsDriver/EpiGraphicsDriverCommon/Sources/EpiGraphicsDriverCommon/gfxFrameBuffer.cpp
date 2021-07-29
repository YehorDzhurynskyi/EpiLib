EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxFrameBuffer.h"
#include "EpiGraphicsDriverCommon/gfxFrameBuffer.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

void gfxFrameBufferCreateInfo::AddAttachment(const gfxImageView& attachment)
{
    m_Attachments.push_back(attachment);
}

gfxFrameBuffer::gfxFrameBuffer(const std::shared_ptr<Impl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxFrameBuffer::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

EPI_NAMESPACE_END()
