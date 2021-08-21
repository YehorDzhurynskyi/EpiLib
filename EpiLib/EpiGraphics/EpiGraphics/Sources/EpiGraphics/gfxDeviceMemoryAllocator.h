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
        PID_COUNT = 1
    };

protected:
    gfxDeviceMemoryAllocatorCreateMask m_CreateMask{};

EPI_GENREGION_END(gfxDeviceMemoryAllocatorCreateInfo)
};

class gfxDeviceMemoryAllocator : public Object
{
EPI_GENREGION_BEGIN(gfxDeviceMemoryAllocator)

EPI_GENHIDDEN_gfxDeviceMemoryAllocator()

public:
    constexpr static epiMetaTypeID TypeID{0xa17feb69};

    enum gfxDeviceMemoryAllocator_PIDs
    {
        PID_COUNT = 0
    };

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
