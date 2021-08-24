#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxBuffer.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphics/gfxEnum.h"
#include "EpiGraphics/gfxQueueFamily.h"

EPI_NAMESPACE_BEGIN()

class gfxBufferCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxBufferCreateInfo)

EPI_GENHIDDEN_gfxBufferCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0x5596e349};

    enum gfxBufferCreateInfo_PIDs
    {
        PID_CreateMask = 0xc2e0d2f0,
        PID_UsageMask = 0x6be8b578,
        PID_Size = 0x57f28b54,
        PID_SharingMode = 0xfcf8b68f,
        PID_QueueFamilies = 0x459d6c2c,
        PID_COUNT = 5
    };

protected:
    gfxBufferCreateMask m_CreateMask{};
    gfxBufferUsageMask m_UsageMask{};
    epiSize_t m_Size{0};
    gfxSharingMode m_SharingMode{};
    epiArray<gfxQueueFamily> m_QueueFamilies{};

EPI_GENREGION_END(gfxBufferCreateInfo)
};

class gfxDevice;
class gfxBuffer : public Object
{
EPI_GENREGION_BEGIN(gfxBuffer)

EPI_GENHIDDEN_gfxBuffer()

public:
    constexpr static epiMetaTypeID TypeID{0x903c9bd4};

    enum gfxBuffer_PIDs
    {
        PID_Device = 0xe83b3b8,
        PID_COUNT = 1
    };

protected:
    const gfxDevice& GetDevice_Callback() const;

EPI_GENREGION_END(gfxBuffer)

public:
    class Impl;

public:
    gfxBuffer() = default;
    explicit gfxBuffer(const std::shared_ptr<Impl>& impl);

    epiBool HasImpl() const;

protected:
    std::shared_ptr<Impl> m_Impl;
};

EPI_NAMESPACE_END()
