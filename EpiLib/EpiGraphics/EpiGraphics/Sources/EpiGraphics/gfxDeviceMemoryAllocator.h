#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxDeviceMemoryAllocator.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphics/gfxEnum.h"
#include "EpiGraphics/gfxBuffer.h"
#include "EpiGraphics/gfxImage.h"

EPI_NAMESPACE_BEGIN()

class gfxDeviceMemoryPoolCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxDeviceMemoryPoolCreateInfo)

EPI_GENHIDDEN_gfxDeviceMemoryPoolCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0xe48eee21};

    enum gfxDeviceMemoryPoolCreateInfo_PIDs
    {
        PID_CreateMask = 0xc2e0d2f0,
        PID_BlockSize = 0xfae3d937,
        PID_MinBlockCount = 0x31087e50,
        PID_MaxBlockCount = 0x71470626,
        PID_FrameInUseCount = 0x9c83cc1d,
        PID_Priority = 0x9bd0be71,
        PID_MinAllocationAlignment = 0x86cdcdb6,
        PID_COUNT = 7
    };

protected:
    gfxDeviceMemoryPoolCreateMask m_CreateMask{};
    epiSize_t m_BlockSize{0};
    epiSize_t m_MinBlockCount{0};
    epiSize_t m_MaxBlockCount{0};
    epiU32 m_FrameInUseCount{0};
    epiFloat m_Priority{0.0f};
    epiSize_t m_MinAllocationAlignment{0};

EPI_GENREGION_END(gfxDeviceMemoryPoolCreateInfo)
};

class gfxDeviceMemoryPool : public Object
{
EPI_GENREGION_BEGIN(gfxDeviceMemoryPool)

EPI_GENHIDDEN_gfxDeviceMemoryPool()

public:
    constexpr static epiMetaTypeID TypeID{0x29b4f6bf};

    enum gfxDeviceMemoryPool_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxDeviceMemoryPool)
};

class gfxDeviceMemoryAllocationCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxDeviceMemoryAllocationCreateInfo)

EPI_GENHIDDEN_gfxDeviceMemoryAllocationCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0x639dc2d1};

    enum gfxDeviceMemoryAllocationCreateInfo_PIDs
    {
        PID_CreateMask = 0xc2e0d2f0,
        PID_Usage = 0x112a7174,
        PID_RequiredPropertiesMask = 0x5d8bea07,
        PID_PreferredPropertiesMask = 0xca916bd6,
        PID_Pool = 0xfa306b8,
        PID_Priority = 0x9bd0be71,
        PID_COUNT = 6
    };

protected:
    gfxDeviceMemoryAllocationCreateMask m_CreateMask{};
    gfxDeviceMemoryAllocationUsage m_Usage{};
    gfxDeviceMemoryPropertyMask m_RequiredPropertiesMask{};
    gfxDeviceMemoryPropertyMask m_PreferredPropertiesMask{};
    gfxDeviceMemoryPool m_Pool{};
    epiFloat m_Priority{0.0f};

EPI_GENREGION_END(gfxDeviceMemoryAllocationCreateInfo)

public:
    static gfxDeviceMemoryAllocationCreateInfo FromUsage(gfxDeviceMemoryAllocationCreateMask createMask,
                                                         gfxDeviceMemoryAllocationUsage usage);

    static gfxDeviceMemoryAllocationCreateInfo FromPropertiesFlags(gfxDeviceMemoryAllocationCreateMask createMask,
                                                                   gfxDeviceMemoryPropertyMask requiredPropertiesMask,
                                                                   gfxDeviceMemoryPropertyMask preferredPropertiesMask);
};

class gfxDeviceMemoryAllocator;
class gfxDeviceMemoryAllocation : public Object
{
EPI_GENREGION_BEGIN(gfxDeviceMemoryAllocation)

EPI_GENHIDDEN_gfxDeviceMemoryAllocation()

public:
    constexpr static epiMetaTypeID TypeID{0xb726156b};

    enum gfxDeviceMemoryAllocation_PIDs
    {
        PID_Allocator = 0x4f8e170f,
        PID_IsMapped = 0xf47f7939,
        PID_IsMappable = 0x19fbf83b,
        PID_COUNT = 3
    };

protected:
    const gfxDeviceMemoryAllocator& GetAllocator_Callback() const;
    epiBool GetIsMapped_Callback() const;
    epiBool GetIsMappable_Callback() const;

EPI_GENREGION_END(gfxDeviceMemoryAllocation)

public:
    class Impl;

public:
    class Mapping final
    {
    public:
        Mapping() = default;
        Mapping(const Mapping& rhs) = delete;
        Mapping& operator=(const Mapping& rhs) = delete;
        Mapping(Mapping&& rhs);
        Mapping& operator=(Mapping&& rhs);
        ~Mapping();

        epiBool Init(const std::shared_ptr<Impl>& deviceMemoryAllocationImpl);

        epiBool IsMapped() const;
        operator epiBool() const;

        epiByte* Mapped();

        template<typename T>
        epiSize_t PushBack(const T& value, epiSize_t cursor, epiSize_t stride = sizeof(T));

    protected:
        std::shared_ptr<Impl> m_DeviceMemoryAllocationImpl; // TODO: weak_ptr ?
    };

public:
    gfxDeviceMemoryAllocation() = default;
    explicit gfxDeviceMemoryAllocation(const std::shared_ptr<Impl>& impl);

    epiBool HasImpl() const;

    epiBool IsPropertyEnabled(gfxDeviceMemoryPropertyMask mask) const;

    epiBool BindBuffer(const gfxBuffer& buffer);
    epiBool BindImage(const gfxImage& image);

    Mapping Map();

    epiBool Invalidate(epiSize_t offset, epiSize_t size = 0);
    epiBool Flush(epiSize_t offset, epiSize_t size = 0);

protected:
    std::shared_ptr<Impl> m_Impl;
};

template<typename T>
epiSize_t gfxDeviceMemoryAllocation::Mapping::PushBack(const T& value, epiSize_t cursor, epiSize_t stride)
{
    static_assert(std::is_trivially_copyable_v<T>);
    epiAssert(IsMapped());
    epiAssert(stride >= sizeof(T));

    memcpy(Mapped() + cursor, &value, stride);

    return cursor + stride;
}

class gfxDeviceMemoryAllocationBuffer : public gfxDeviceMemoryAllocation
{
EPI_GENREGION_BEGIN(gfxDeviceMemoryAllocationBuffer)

EPI_GENHIDDEN_gfxDeviceMemoryAllocationBuffer()

public:
    constexpr static epiMetaTypeID TypeID{0xb98d0ad8};

    enum gfxDeviceMemoryAllocationBuffer_PIDs
    {
        PID_Buffer = 0x36f6f5c4,
        PID_COUNT = 1
    };

protected:
    gfxBuffer m_Buffer{};

EPI_GENREGION_END(gfxDeviceMemoryAllocationBuffer)

public:
    gfxDeviceMemoryAllocationBuffer() = default;
    gfxDeviceMemoryAllocationBuffer(const std::shared_ptr<Impl>& impl, gfxBuffer&& buffer);
};

class gfxDeviceMemoryAllocationImage : public gfxDeviceMemoryAllocation
{
EPI_GENREGION_BEGIN(gfxDeviceMemoryAllocationImage)

EPI_GENHIDDEN_gfxDeviceMemoryAllocationImage()

public:
    constexpr static epiMetaTypeID TypeID{0x1a9dc887};

    enum gfxDeviceMemoryAllocationImage_PIDs
    {
        PID_Image = 0x4fc2b5b,
        PID_COUNT = 1
    };

protected:
    gfxImage m_Image{};

EPI_GENREGION_END(gfxDeviceMemoryAllocationImage)

public:
    gfxDeviceMemoryAllocationImage() = default;
    gfxDeviceMemoryAllocationImage(const std::shared_ptr<Impl>& impl, gfxImage&& image);
};

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

    std::optional<gfxDeviceMemoryAllocationBuffer> CreateBuffer(const gfxDeviceMemoryAllocationCreateInfo& allocationInfo,
                                                                const gfxBufferCreateInfo& bufferInfo);

    std::optional<gfxDeviceMemoryAllocationImage> CreateImage(const gfxDeviceMemoryAllocationCreateInfo& allocationInfo,
                                                              const gfxImageCreateInfo& imageInfo);

    std::optional<gfxDeviceMemoryAllocation> AllocateBuffer(const gfxDeviceMemoryAllocationCreateInfo& info,
                                                            const gfxBuffer& buffer);

    std::optional<gfxDeviceMemoryAllocation> AllocateImage(const gfxDeviceMemoryAllocationCreateInfo& info,
                                                           const gfxImage& image);

protected:
    std::shared_ptr<Impl> m_Impl;
};

EPI_NAMESPACE_END()
