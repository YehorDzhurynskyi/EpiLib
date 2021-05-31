#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxDeviceMemory.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxEnum.h"
#include "EpiGraphicsDriverCommon/gfxBuffer.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxDeviceMemoryImpl;

} // namespace internalgfx

class gfxDeviceMemoryCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxDeviceMemoryCreateInfo)

EPI_GENHIDDEN_gfxDeviceMemoryCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0xd2391506};

    enum gfxDeviceMemoryCreateInfo_PIDs
    {
        PID_Buffer = 0x36f6f5c4,
        PID_PropertyMask = 0x483bfadf,
        PID_COUNT = 2
    };

protected:
    gfxBuffer m_Buffer{};
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
    class Mapping final
    {
    public:
        Mapping(internalgfx::gfxDeviceMemoryImpl* impl, epiSize_t size, epiSize_t offset);
        ~Mapping();

        epiBool IsMapped() const;
        operator epiBool() const;

        epiByte* Data();

        template<typename T>
        void PushBack(const T& value, epiSize_t stride = sizeof(T));

    protected:
        internalgfx::gfxDeviceMemoryImpl* m_Impl{nullptr};
        epiByte* m_Data{nullptr};
        epiSize_t m_Cursor{0};
    };

public:
    gfxDeviceMemory() = default;
    explicit gfxDeviceMemory(const std::shared_ptr<internalgfx::gfxDeviceMemoryImpl>& impl);

    Mapping Map(epiSize_t size, epiSize_t offset = 0);

protected:
    epiPimpl<internalgfx::gfxDeviceMemoryImpl> m_Impl;
};

template<typename T>
void gfxDeviceMemory::Mapping::PushBack(const T& value, epiSize_t stride)
{
    static_assert(std::is_trivially_copyable_v<T>);

    memcpy(m_Data + m_Cursor, &value, stride);

    m_Cursor += stride;
}


EPI_NAMESPACE_END()
