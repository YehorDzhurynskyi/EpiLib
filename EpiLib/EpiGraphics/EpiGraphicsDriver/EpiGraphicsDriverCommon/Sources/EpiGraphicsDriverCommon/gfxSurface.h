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
        PID_COUNT = 6
    };

protected:
    epiU32 m_MinImageCount{0};
    epiU32 m_MaxImageCount{0};
    epiU32 m_MaxImageArrayLayers{0};
    epiSize2u m_CurrentExtent{};
    epiSize2u m_MinImageExtent{};
    epiSize2u m_MaxImageExtent{};

EPI_GENREGION_END(gfxSurfaceCapabilities)
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
    gfxSurface() = default;
    gfxSurface(internalgfx::gfxSurfaceImpl* impl);
    gfxSurface(const gfxSurface& rhs) = delete;
    gfxSurface& operator=(const gfxSurface& rhs) = delete;
    gfxSurface(gfxSurface&& rhs);
    gfxSurface& operator=(gfxSurface&& rhs);
    ~gfxSurface();

public:
    gfxQueueDescriptor CreateQueueDescriptor(const epiArray<epiFloat>& priorities, gfxQueueType type = gfxQueueType{0}) const;

    epiBool IsPresentSupportedFor(const gfxPhysicalDevice& device) const;
    gfxSurfaceCapabilities GetCapabilitiesFor(const gfxPhysicalDevice& device) const;
    epiArray<gfxSurfaceFormat> GetSupportedFormatsFor(const gfxPhysicalDevice& device) const;
    epiArray<gfxSurfacePresentMode> GetSupportedPresentModesFor(const gfxPhysicalDevice& device) const;

protected:
    internalgfx::gfxSurfaceImpl* m_Impl{nullptr};
};

EPI_NAMESPACE_END()
