#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxFrameBuffer.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxRenderPass.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxFrameBufferImpl;

} // internalgfx

class gfxFramebufferAttachmentImageInfo : public Object
{
EPI_GENREGION_BEGIN(gfxFramebufferAttachmentImageInfo)

EPI_GENHIDDEN_gfxFramebufferAttachmentImageInfo()

public:
    constexpr static epiMetaTypeID TypeID{0x6556f0d2};

    enum gfxFramebufferAttachmentImageInfo_PIDs
    {
        PID_Usage = 0x112a7174,
        PID_Size = 0x57f28b54,
        PID_LayerCount = 0x8255c3f7,
        PID_Formats = 0xc20183a0,
        PID_COUNT = 4
    };

protected:
    gfxImageUsage m_Usage{};
    epiSize2u m_Size{};
    epiU32 m_LayerCount{1};
    epiArray<gfxFormat> m_Formats{};

EPI_GENREGION_END(gfxFramebufferAttachmentImageInfo)
};

class gfxFrameBufferCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxFrameBufferCreateInfo)

EPI_GENHIDDEN_gfxFrameBufferCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0x1ff94eb8};

    enum gfxFrameBufferCreateInfo_PIDs
    {
        PID_RenderPass = 0x662aa9d7,
        PID_Size = 0x57f28b54,
        PID_AttachmentImageInfos = 0xeef19709,
        PID_COUNT = 3
    };

protected:
    gfxRenderPass m_RenderPass{};
    epiSize2u m_Size{};
    epiArray<gfxFramebufferAttachmentImageInfo> m_AttachmentImageInfos{};

EPI_GENREGION_END(gfxFrameBufferCreateInfo)

public:
    void AddAttachment(gfxFramebufferAttachmentImageInfo&& info);
};

class gfxFrameBuffer : public Object
{
EPI_GENREGION_BEGIN(gfxFrameBuffer)

EPI_GENHIDDEN_gfxFrameBuffer()

public:
    constexpr static epiMetaTypeID TypeID{0x26f63f06};

    enum gfxFrameBuffer_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxFrameBuffer)

public:
    friend class gfxCommandBuffer;

public:
    gfxFrameBuffer() = default;
    explicit gfxFrameBuffer(const std::shared_ptr<internalgfx::gfxFrameBufferImpl>& impl);

protected:
    epiPimpl<internalgfx::gfxFrameBufferImpl> m_Impl;
};

EPI_NAMESPACE_END()
