#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxDeviceMemory.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphics/gfxEnum.h"
#include "EpiGraphics/gfxBuffer.h"
#include "EpiGraphics/gfxImage.h"

EPI_NAMESPACE_BEGIN()

class gfxMemoryBarrier : public Object
{
EPI_GENREGION_BEGIN(gfxMemoryBarrier)

EPI_GENHIDDEN_gfxMemoryBarrier()

public:
    constexpr static epiMetaTypeID TypeID{0xbed81168};

    enum gfxMemoryBarrier_PIDs
    {
        PID_SrcAccessMask = 0xe4d2b1e8,
        PID_DstAccessMask = 0x31ce8c4d,
        PID_COUNT = 2
    };

protected:
    gfxAccess m_SrcAccessMask{};
    gfxAccess m_DstAccessMask{};

EPI_GENREGION_END(gfxMemoryBarrier)
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

class gfxImageMemoryBarrier : public Object
{
EPI_GENREGION_BEGIN(gfxImageMemoryBarrier)

EPI_GENHIDDEN_gfxImageMemoryBarrier()

public:
    constexpr static epiMetaTypeID TypeID{0xdb16c216};

    enum gfxImageMemoryBarrier_PIDs
    {
        PID_Image = 0x4fc2b5b,
        PID_SrcAccessMask = 0xe4d2b1e8,
        PID_DstAccessMask = 0x31ce8c4d,
        PID_OldLayout = 0x93cbca0d,
        PID_NewLayout = 0xcdc94336,
        PID_SrcQueueFamilyIndex = 0x292c7bd,
        PID_DstQueueFamilyIndex = 0x837f242b,
        PID_IsSrcQueueFamilyIndexIgnored = 0xe8ba2402,
        PID_IsDstQueueFamilyIndexIgnored = 0x71d3dc18,
        PID_SubresourceRange = 0x5a75fb0e,
        PID_COUNT = 10
    };

protected:
    gfxImage m_Image{};
    gfxAccess m_SrcAccessMask{};
    gfxAccess m_DstAccessMask{};
    gfxImageLayout m_OldLayout{};
    gfxImageLayout m_NewLayout{};
    epiU32 m_SrcQueueFamilyIndex{0};
    epiU32 m_DstQueueFamilyIndex{0};
    epiBool m_IsSrcQueueFamilyIndexIgnored{false};
    epiBool m_IsDstQueueFamilyIndexIgnored{false};
    gfxImageSubresourceRange m_SubresourceRange{};

EPI_GENREGION_END(gfxImageMemoryBarrier)
};

class gfxCommandBufferRecordPipelineBarier : public Object
{
EPI_GENREGION_BEGIN(gfxCommandBufferRecordPipelineBarier)

EPI_GENHIDDEN_gfxCommandBufferRecordPipelineBarier()

public:
    constexpr static epiMetaTypeID TypeID{0x28dc5fc7};

    enum gfxCommandBufferRecordPipelineBarier_PIDs
    {
        PID_SrcStageMask = 0x5890cb97,
        PID_DstStageMask = 0x24ec8ab5,
        PID_DependencyFlags = 0x68167a5,
        PID_MemoryBarriers = 0xb0ffaf07,
        PID_BufferMemoryBarriers = 0x7471824,
        PID_ImageMemoryBarriers = 0x7d257b36,
        PID_COUNT = 6
    };

protected:
    gfxPipelineStage m_SrcStageMask{};
    gfxPipelineStage m_DstStageMask{};
    gfxDependency m_DependencyFlags{};
    epiArray<gfxMemoryBarrier> m_MemoryBarriers{};
    epiArray<gfxBufferMemoryBarrier> m_BufferMemoryBarriers{};
    epiArray<gfxImageMemoryBarrier> m_ImageMemoryBarriers{};

EPI_GENREGION_END(gfxCommandBufferRecordPipelineBarier)
};

class gfxBindBufferMemoryInfo : public Object
{
EPI_GENREGION_BEGIN(gfxBindBufferMemoryInfo)

EPI_GENHIDDEN_gfxBindBufferMemoryInfo()

public:
    constexpr static epiMetaTypeID TypeID{0x691f6202};

    enum gfxBindBufferMemoryInfo_PIDs
    {
        PID_Buffer = 0x36f6f5c4,
        PID_Offset = 0x5ea6cfe6,
        PID_COUNT = 2
    };

protected:
    gfxBuffer m_Buffer{};
    epiSize_t m_Offset{0};

EPI_GENREGION_END(gfxBindBufferMemoryInfo)

public:
    static gfxBindBufferMemoryInfo FromBuffer(const gfxBuffer& buffer, epiSize_t offset = 0);
};

class gfxBindImageMemoryInfo : public Object
{
EPI_GENREGION_BEGIN(gfxBindImageMemoryInfo)

EPI_GENHIDDEN_gfxBindImageMemoryInfo()

public:
    constexpr static epiMetaTypeID TypeID{0x2b1c0be7};

    enum gfxBindImageMemoryInfo_PIDs
    {
        PID_Image = 0x4fc2b5b,
        PID_Offset = 0x5ea6cfe6,
        PID_COUNT = 2
    };

protected:
    gfxImage m_Image{};
    epiSize_t m_Offset{0};

EPI_GENREGION_END(gfxBindImageMemoryInfo)

public:
    static gfxBindImageMemoryInfo FromImage(const gfxImage& image, epiSize_t offset = 0);
};

class gfxDeviceMemoryCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxDeviceMemoryCreateInfo)

EPI_GENHIDDEN_gfxDeviceMemoryCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0xd2391506};

    enum gfxDeviceMemoryCreateInfo_PIDs
    {
        PID_Size = 0x57f28b54,
        PID_PropertyMask = 0x483bfadf,
        PID_COUNT = 2
    };

protected:
    epiSize_t m_Size{0};
    gfxDeviceMemoryPropertyMask m_PropertyMask{};

EPI_GENREGION_END(gfxDeviceMemoryCreateInfo)
};

class gfxDeviceMemory : public Object
{
EPI_GENREGION_BEGIN(gfxDeviceMemory)

EPI_GENHIDDEN_gfxDeviceMemory()

public:
    constexpr static epiMetaTypeID TypeID{0x589c0207};

    enum gfxDeviceMemory_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxDeviceMemory)

public:
    class Impl;

public:
    class Mapping final
    {
    public:
        Mapping() = default;
        ~Mapping();

        epiBool Init(const std::shared_ptr<Impl>& deviceMemory, epiSize_t size, epiSize_t offset);

        epiBool IsMapped() const;
        operator epiBool() const;

        epiByte* Data();

        template<typename T>
        epiSize_t PushBack(const T& value, epiSize_t cursor, epiSize_t stride = sizeof(T));

    protected:
        std::shared_ptr<Impl> m_DeviceMemoryImpl; // TODO: weak_ptr ?
        epiByte* m_Data{nullptr};
    };

public:
    gfxDeviceMemory() = default;
    explicit gfxDeviceMemory(const std::shared_ptr<Impl>& impl);

    epiBool HasImpl() const;

    epiBool IsPropertyEnabled(gfxDeviceMemoryPropertyMask mask) const;

    epiBool BindBuffer(const gfxBindBufferMemoryInfo& info);
    epiBool BindImage(const gfxBindImageMemoryInfo& info);

    Mapping Map(epiSize_t size, epiSize_t offset = 0);

protected:
    std::shared_ptr<Impl> m_Impl;
};

template<typename T>
epiSize_t gfxDeviceMemory::Mapping::PushBack(const T& value, epiSize_t cursor, epiSize_t stride)
{
    static_assert(std::is_trivially_copyable_v<T>);
    epiAssert(stride >= sizeof(T));

    memcpy(m_Data + cursor, &value, stride);

    return cursor + stride;
}

EPI_NAMESPACE_END()
