#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxImage.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphics/gfxEnum.h"
#include "EpiGraphics/gfxQueueFamily.h"

EPI_NAMESPACE_BEGIN()

class gfxImageCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxImageCreateInfo)

EPI_GENHIDDEN_gfxImageCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0xa554a68e};

    enum gfxImageCreateInfo_PIDs
    {
        PID_CreateMask = 0xc2e0d2f0,
        PID_UsageMask = 0x6be8b578,
        PID_Type = 0x2cecf817,
        PID_Format = 0xd91677e9,
        PID_Extent = 0x21a25c7e,
        PID_MipLevels = 0xc35c5bc9,
        PID_ArrayLayers = 0x65ffb52d,
        PID_SampleCount = 0x2397b6e7,
        PID_InitialLayout = 0xcf791b4,
        PID_Tiling = 0xaca1f4b8,
        PID_SharingMode = 0xfcf8b68f,
        PID_QueueFamilies = 0x459d6c2c,
        PID_COUNT = 12
    };

protected:
    gfxImageCreateMask m_CreateMask{};
    gfxImageUsageMask m_UsageMask{};
    gfxImageType m_Type{};
    gfxFormat m_Format{};
    epiVec3u m_Extent{};
    epiU32 m_MipLevels{0};
    epiU32 m_ArrayLayers{0};
    gfxSampleCountMask m_SampleCount{};
    gfxImageLayout m_InitialLayout{};
    gfxImageTiling m_Tiling{};
    gfxSharingMode m_SharingMode{};
    epiArray<gfxQueueFamily> m_QueueFamilies{};

EPI_GENREGION_END(gfxImageCreateInfo)
};

class gfxDevice;
class gfxImage : public Object
{
EPI_GENREGION_BEGIN(gfxImage)

EPI_GENHIDDEN_gfxImage()

public:
    constexpr static epiMetaTypeID TypeID{0x72c55cfe};

    enum gfxImage_PIDs
    {
        PID_Device = 0xe83b3b8,
        PID_COUNT = 1
    };

protected:
    const gfxDevice& GetDevice_Callback() const;

EPI_GENREGION_END(gfxImage)

public:
    class Impl;

public:
    gfxImage() = default;
    explicit gfxImage(const std::shared_ptr<Impl>& impl);

    epiBool HasImpl() const;

protected:
    std::shared_ptr<Impl> m_Impl;
};

class gfxImageSubresourceLayers : public Object
{
EPI_GENREGION_BEGIN(gfxImageSubresourceLayers)

EPI_GENHIDDEN_gfxImageSubresourceLayers()

public:
    constexpr static epiMetaTypeID TypeID{0x42646fc6};

    enum gfxImageSubresourceLayers_PIDs
    {
        PID_AspectMask = 0x522981c3,
        PID_MipLevel = 0x5fbf18a8,
        PID_BaseArrayLayer = 0x73d2d345,
        PID_LayerCount = 0x8255c3f7,
        PID_COUNT = 4
    };

protected:
    gfxImageAspect m_AspectMask{};
    epiU32 m_MipLevel{0};
    epiU32 m_BaseArrayLayer{0};
    epiU32 m_LayerCount{0};

EPI_GENREGION_END(gfxImageSubresourceLayers)
};

class gfxImageSubresourceRange : public Object
{
EPI_GENREGION_BEGIN(gfxImageSubresourceRange)

EPI_GENHIDDEN_gfxImageSubresourceRange()

public:
    constexpr static epiMetaTypeID TypeID{0xaec1a12f};

    enum gfxImageSubresourceRange_PIDs
    {
        PID_AspectMask = 0x522981c3,
        PID_BaseMipLevel = 0x7c09b49,
        PID_LevelCount = 0x3f45e3bc,
        PID_BaseArrayLayer = 0x73d2d345,
        PID_LayerCount = 0x8255c3f7,
        PID_COUNT = 5
    };

protected:
    gfxImageAspect m_AspectMask{};
    epiU32 m_BaseMipLevel{0};
    epiU32 m_LevelCount{0};
    epiU32 m_BaseArrayLayer{0};
    epiU32 m_LayerCount{0};

EPI_GENREGION_END(gfxImageSubresourceRange)
};

EPI_NAMESPACE_END()
