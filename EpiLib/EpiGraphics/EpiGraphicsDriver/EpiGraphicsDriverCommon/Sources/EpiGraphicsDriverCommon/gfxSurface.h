#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxSurface.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxEnum.h"
#include "EpiGraphicsDriverCommon/gfxQueueDescriptor.h"

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxSurfaceImpl;
class gfxPhysicalDeviceImpl;

} // internalgfx

class gfxSurfaceCapabilities : public Object
{
EPI_GENREGION_BEGIN(gfxSurfaceCapabilities)

EPI_GENHIDDEN_gfxSurfaceCapabilities()

public:
    constexpr static epiMetaTypeID TypeID{0x2480adec};

    enum gfxSurfaceCapabilities_PIDs
    {
        PID_MinImageCount = 0x55cc6b5,
        PID_MaxImageCount = 0x4513bec3,
        PID_MaxImageArrayLayers = 0xbbf8286f,
        PID_CurrentExtent = 0xbcfa8c13,
        PID_MinImageExtent = 0x3e399bbd,
        PID_MaxImageExtent = 0x871f00cc,
        PID_SupportedSurfaceTransformMask = 0x9da9b0e4,
        PID_SupportedCompositeAlphaMask = 0x5b3422cc,
        PID_SupportedUsage = 0xbc2208b2,
        PID_CurrentSurfaceTransformMask = 0x797fb8fb,
        PID_COUNT = 10
    };

protected:
    epiU32 m_MinImageCount{0};
    epiU32 m_MaxImageCount{0};
    epiU32 m_MaxImageArrayLayers{0};
    epiSize2u m_CurrentExtent{};
    epiSize2u m_MinImageExtent{};
    epiSize2u m_MaxImageExtent{};
    gfxSurfaceTransformMask m_SupportedSurfaceTransformMask{};
    gfxCompositeAlphaMask m_SupportedCompositeAlphaMask{};
    gfxImageUsage m_SupportedUsage{};
    gfxSurfaceTransformMask m_CurrentSurfaceTransformMask{};

EPI_GENREGION_END(gfxSurfaceCapabilities)

public:
    epiSize2u ClampExtent(const epiSize2u& extent) const;
    epiU32 RecommendedImageMinCount() const;
};

class gfxSurfaceFormat : public Object
{
EPI_GENREGION_BEGIN(gfxSurfaceFormat)

EPI_GENHIDDEN_gfxSurfaceFormat()

public:
    constexpr static epiMetaTypeID TypeID{0x47c9b72c};

    enum gfxSurfaceFormat_PIDs
    {
        PID_Format = 0xd91677e9,
        PID_ColorSpace = 0x871ca6b1,
        PID_COUNT = 2
    };

protected:
    gfxFormat m_Format{};
    gfxSurfaceColorSpace m_ColorSpace{};

EPI_GENREGION_END(gfxSurfaceFormat)

public:
    friend epiBool operator==(const gfxSurfaceFormat& lhs, const gfxSurfaceFormat& rhs);
    friend epiBool operator!=(const gfxSurfaceFormat& lhs, const gfxSurfaceFormat& rhs);
};

class gfxPhysicalDevice;
class gfxSurface : public Object
{
EPI_GENREGION_BEGIN(gfxSurface)

EPI_GENHIDDEN_gfxSurface()

public:
    constexpr static epiMetaTypeID TypeID{0x6eed7df8};

    enum gfxSurface_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxSurface)

public:
    friend class gfxDevice;
    friend class gfxQueueDescriptor;
    friend class gfxSwapChain;
    friend class internalgfx::gfxSurfaceImpl;

public:
    gfxSurface() = default;
    explicit gfxSurface(const std::shared_ptr<internalgfx::gfxSurfaceImpl>& impl);

public:
    epiBool HasImpl() const;

    epiBool IsCompatibleWith(const gfxPhysicalDevice& device,
                             const gfxSurfaceFormat& format,
                             gfxSurfacePresentMode presentMode) const;

    epiBool IsPresentSupportedFor(const gfxPhysicalDevice& device) const;
    epiBool IsPresentSupportedFor(const gfxPhysicalDevice& device, const gfxQueueFamily& queueFamily) const;
    epiBool IsPresentSupportedFor(const gfxPhysicalDevice& device, const gfxQueueFamilyDescriptor& queueFamilyDesc) const;
    gfxSurfaceCapabilities GetCapabilitiesFor(const gfxPhysicalDevice& device) const;
    epiArray<gfxSurfaceFormat> GetSupportedFormatsFor(const gfxPhysicalDevice& device) const;
    epiArray<gfxSurfacePresentMode> GetSupportedPresentModesFor(const gfxPhysicalDevice& device) const;

protected:
    epiPimpl<internalgfx::gfxSurfaceImpl> m_Impl;
};

EPI_NAMESPACE_END()
