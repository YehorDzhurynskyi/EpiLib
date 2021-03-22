EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxFrameBuffer.h"
#include "EpiGraphicsDriverCommon/gfxFrameBuffer.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

void gfxFrameBufferCreateInfo::AddAttachment(gfxFramebufferAttachmentImageInfo&& info)
{
    m_AttachmentImageInfos.push_back(std::move(info));
}

gfxFrameBuffer::gfxFrameBuffer(internalgfx::gfxFrameBufferImpl* impl)
    : m_Impl{impl}
{
}

gfxFrameBuffer::gfxFrameBuffer(gfxFrameBuffer&& rhs)
{
    m_Impl = rhs.m_Impl;

    rhs.m_Impl = nullptr;
}

gfxFrameBuffer& gfxFrameBuffer::operator=(gfxFrameBuffer&& rhs)
{
    m_Impl = rhs.m_Impl;

    rhs.m_Impl = nullptr;

    return *this;
}

gfxFrameBuffer::~gfxFrameBuffer()
{
    delete m_Impl;
}

EPI_NAMESPACE_END()
