#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxImage.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxEnum.h"

EPI_NAMESPACE_BEGIN()

class gfxImageCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxImageCreateInfo)

EPI_GENHIDDEN_gfxImageCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0x724865ad};

    enum gfxImageCreateInfo_PIDs
    {
        PID_Type = 0x2cecf817,
        PID_Format = 0xd91677e9,
        PID_Extent = 0x21a25c7e,
        PID_MipLevels = 0xc35c5bc9,
        PID_ArrayLayers = 0x65ffb52d,
        PID_SampleCount = 0x2397b6e7,
        PID_Usage = 0x112a7174,
        PID_InitialLayout = 0xcf791b4,
        PID_Tiling = 0xaca1f4b8,
        PID_COUNT = 9
    };

protected:
    gfxImageType m_Type{};
    gfxFormat m_Format{gfxFormat::UNDEFINED};
    epiVec3u m_Extent{};
    epiU32 m_MipLevels{0};
    epiU32 m_ArrayLayers{0};
    gfxSampleCount m_SampleCount{gfxSampleCount::Sample1};
    gfxImageUsage m_Usage{};
    gfxImageLayout m_InitialLayout{gfxImageLayout::Undefined};
    gfxImageTiling m_Tiling{};

EPI_GENREGION_END(gfxImageCreateInfo)
};

class gfxImage : public Object
{
EPI_GENREGION_BEGIN(gfxImage)

EPI_GENHIDDEN_gfxImage()

public:
    constexpr static epiMetaTypeID TypeID{0x50caeee4};

    enum gfxImage_PIDs
    {
        PID_COUNT = 0
    };

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

EPI_NAMESPACE_END()
