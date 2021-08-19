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
    gfxDeviceMemoryProperty m_PropertyMask{};

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
        Mapping(const std::shared_ptr<Impl>& impl, epiSize_t size, epiSize_t offset);
        ~Mapping();

        epiBool IsMapped() const;
        operator epiBool() const;

        epiByte* Data();

        template<typename T>
        void PushBack(const T& value, epiSize_t stride = sizeof(T));

    protected:
        std::shared_ptr<Impl> m_Impl{nullptr}; // TODO: weak_ptr ?
        epiByte* m_Data{nullptr};
        epiSize_t m_Cursor{0};
    };

public:
    gfxDeviceMemory() = default;
    explicit gfxDeviceMemory(const std::shared_ptr<Impl>& impl);

    epiBool HasImpl() const;

    epiBool BindBuffer(const gfxBindBufferMemoryInfo& info);
    epiBool BindImage(const gfxBindImageMemoryInfo& info);

    Mapping Map(epiSize_t size, epiSize_t offset = 0);

protected:
    std::shared_ptr<Impl> m_Impl;
};

template<typename T>
void gfxDeviceMemory::Mapping::PushBack(const T& value, epiSize_t stride)
{
    static_assert(std::is_trivially_copyable_v<T>);
    epiAssert(stride >= sizeof(T));

    memcpy(m_Data + m_Cursor, &value, stride);

    m_Cursor += stride;
}

EPI_NAMESPACE_END()
