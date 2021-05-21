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
    gfxDeviceMemory() = default;
    explicit gfxDeviceMemory(const std::shared_ptr<internalgfx::gfxDeviceMemoryImpl>& impl);

    epiByte* Map(epiSize_t size, epiSize_t offset);
    void Unmap();

protected:
    epiPimpl<internalgfx::gfxDeviceMemoryImpl> m_Impl;
};

EPI_NAMESPACE_END()
