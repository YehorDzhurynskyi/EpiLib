#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxBuffer.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxEnum.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxBufferImpl;

} // namespace internalgfx

class gfxBufferCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxBufferCreateInfo)

EPI_GENHIDDEN_gfxBufferCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0x5596e349};

    enum gfxBufferCreateInfo_PIDs
    {
        PID_Capacity = 0x4c9ed322,
        PID_Usage = 0x112a7174,
        PID_COUNT = 2
    };

protected:
    epiSize_t m_Capacity{0};
    gfxBufferUsage m_Usage{};

EPI_GENREGION_END(gfxBufferCreateInfo)
};

class gfxBuffer : public Object
{
EPI_GENREGION_BEGIN(gfxBuffer)

EPI_GENHIDDEN_gfxBuffer()

public:
    constexpr static epiMetaTypeID TypeID{0x903c9bd4};

    enum gfxBuffer_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxBuffer)

public:
    friend class gfxDevice;
    friend class gfxCommandBufferRecord;

public:
    gfxBuffer() = default;
    explicit gfxBuffer(const std::shared_ptr<internalgfx::gfxBufferImpl> &impl);

protected:
    epiPimpl<internalgfx::gfxBufferImpl> m_Impl;
};

EPI_NAMESPACE_END()
