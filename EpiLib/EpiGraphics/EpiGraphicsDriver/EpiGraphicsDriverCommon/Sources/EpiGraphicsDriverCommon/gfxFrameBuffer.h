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

class gfxFrameBufferCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxFrameBufferCreateInfo)

EPI_GENHIDDEN_gfxFrameBufferCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0x1ff94eb8};

    enum gfxFrameBufferCreateInfo_PIDs
    {
        PID_Size = 0x57f28b54,
        PID_RenderPass = 0x662aa9d7,
        PID_COUNT = 2
    };

protected:
    void SetRenderPass_Callback(gfxRenderPass&& value);

protected:
    epiSize2u m_Size{};
    gfxRenderPass m_RenderPass{};

EPI_GENREGION_END(gfxFrameBufferCreateInfo)
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
    gfxFrameBuffer() = default;
    explicit gfxFrameBuffer(internalgfx::gfxFrameBufferImpl* impl);
    gfxFrameBuffer(const gfxFrameBuffer& rhs) = delete;
    gfxFrameBuffer& operator=(const gfxFrameBuffer& rhs) = delete;
    gfxFrameBuffer(gfxFrameBuffer&& rhs);
    gfxFrameBuffer& operator=(gfxFrameBuffer&& rhs);
    ~gfxFrameBuffer();

protected:
    internalgfx::gfxFrameBufferImpl* m_Impl{nullptr};
};

EPI_NAMESPACE_END()
