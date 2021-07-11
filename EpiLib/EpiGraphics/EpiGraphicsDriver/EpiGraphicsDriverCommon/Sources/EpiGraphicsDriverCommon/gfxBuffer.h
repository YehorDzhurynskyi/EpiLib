#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxBuffer.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxEnum.h"

EPI_NAMESPACE_BEGIN()

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
    class Impl;

public:
    gfxBuffer() = default;
    explicit gfxBuffer(const std::shared_ptr<gfxBuffer::Impl>& impl);

    epiBool HasImpl() const;

protected:
    std::shared_ptr<gfxBuffer::Impl> m_Impl;
};

class gfxBufferMemoryBarrier : public Object
{
EPI_GENREGION_BEGIN(gfxBufferMemoryBarrier)

EPI_GENHIDDEN_gfxBufferMemoryBarrier()

public:
    constexpr static epiMetaTypeID TypeID{0xb7925aff};

    enum gfxBufferMemoryBarrier_PIDs
    {
        PID_Buffer = 0x36f6f5c4,
        PID_SrcAccessMask = 0xe4d2b1e8,
        PID_DstAccessMask = 0x31ce8c4d,
        PID_SrcQueueFamilyIndex = 0x292c7bd,
        PID_DstQueueFamilyIndex = 0x837f242b,
        PID_IsSrcQueueFamilyIndexIgnored = 0xe8ba2402,
        PID_IsDstQueueFamilyIndexIgnored = 0x71d3dc18,
        PID_Offset = 0x5ea6cfe6,
        PID_Size = 0x57f28b54,
        PID_COUNT = 9
    };

protected:
    gfxBuffer m_Buffer{};
    gfxAccess m_SrcAccessMask{};
    gfxAccess m_DstAccessMask{};
    epiU32 m_SrcQueueFamilyIndex{0};
    epiU32 m_DstQueueFamilyIndex{0};
    epiBool m_IsSrcQueueFamilyIndexIgnored{false};
    epiBool m_IsDstQueueFamilyIndexIgnored{false};
    epiSize_t m_Offset{0};
    epiSize_t m_Size{0};

EPI_GENREGION_END(gfxBufferMemoryBarrier)
};

EPI_NAMESPACE_END()
