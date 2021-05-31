#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxFrameBuffer.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxRenderPass.h"
#include "EpiGraphicsDriverCommon/gfxTextureView.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxFrameBufferImpl;

} // internalgfx

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
        PID_Attachments = 0xc1587501,
        PID_COUNT = 3
    };

protected:
    gfxRenderPass m_RenderPass{};
    epiSize2u m_Size{};
    epiArray<gfxTextureView> m_Attachments{};

EPI_GENREGION_END(gfxFrameBufferCreateInfo)

public:
    void AddAttachment(const gfxTextureView& attachment);
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
    friend class gfxCommandBufferRecord;

public:
    gfxFrameBuffer() = default;
    explicit gfxFrameBuffer(const std::shared_ptr<internalgfx::gfxFrameBufferImpl>& impl);

protected:
    epiPimpl<internalgfx::gfxFrameBufferImpl> m_Impl;
};

EPI_NAMESPACE_END()
