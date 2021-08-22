#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxDeviceMemoryAllocator.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphics/gfxEnum.h"

EPI_NAMESPACE_BEGIN()

class gfxDeviceMemoryAllocatorCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxDeviceMemoryAllocatorCreateInfo)

EPI_GENHIDDEN_gfxDeviceMemoryAllocatorCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0x773b4bfd};

    enum gfxDeviceMemoryAllocatorCreateInfo_PIDs
    {
        PID_CreateMask = 0xc2e0d2f0,
        PID_PreferredLargeHeapBlockSize = 0xcb9b9cb0,
        PID_FrameInUseCount = 0x9c83cc1d,
        PID_COUNT = 3
    };

protected:
    gfxDeviceMemoryAllocatorCreateMask m_CreateMask{};
    epiSize_t m_PreferredLargeHeapBlockSize{0};
    epiU32 m_FrameInUseCount{0};

EPI_GENREGION_END(gfxDeviceMemoryAllocatorCreateInfo)
};

class gfxDevice;
class gfxDeviceMemoryAllocator : public Object
{
EPI_GENREGION_BEGIN(gfxDeviceMemoryAllocator)

EPI_GENHIDDEN_gfxDeviceMemoryAllocator()

public:
    constexpr static epiMetaTypeID TypeID{0xa17feb69};

    enum gfxDeviceMemoryAllocator_PIDs
    {
        PID_Device = 0xe83b3b8,
        PID_COUNT = 1
    };

protected:
    const gfxDevice& GetDevice_Callback() const;

EPI_GENREGION_END(gfxDeviceMemoryAllocator)

public:
    class Impl;

public:
    gfxDeviceMemoryAllocator() = default;
    explicit gfxDeviceMemoryAllocator(const std::shared_ptr<Impl>& impl);

    epiBool HasImpl() const;

protected:
    std::shared_ptr<Impl> m_Impl;
};

EPI_NAMESPACE_END()
