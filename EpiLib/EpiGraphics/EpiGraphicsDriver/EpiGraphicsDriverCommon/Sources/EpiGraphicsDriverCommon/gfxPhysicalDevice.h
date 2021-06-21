#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxPhysicalDevice.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxDevice.h"

#include "EpiGraphicsDriverCommon/gfxEnum.h"
#include "EpiGraphicsDriverCommon/gfxQueueDescriptor.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxPhysicalDeviceImpl;

} // namespace internalgfx

class gfxFormatProperties : public Object
{
EPI_GENREGION_BEGIN(gfxFormatProperties)

EPI_GENHIDDEN_gfxFormatProperties()

public:
    constexpr static epiMetaTypeID TypeID{0x6f36a2ff};

    enum gfxFormatProperties_PIDs
    {
        PID_LinearTilingFeatureMask = 0x32751455,
        PID_OptimalTilingFeatureMask = 0xbd20e6d6,
        PID_BufferFeatureMask = 0x179c4755,
        PID_COUNT = 3
    };

protected:
    gfxFormatFeatureMask m_LinearTilingFeatureMask{};
    gfxFormatFeatureMask m_OptimalTilingFeatureMask{};
    gfxFormatFeatureMask m_BufferFeatureMask{};

EPI_GENREGION_END(gfxFormatProperties)
};

class gfxPhysicalDevice : public Object
{
EPI_GENREGION_BEGIN(gfxPhysicalDevice)

EPI_GENHIDDEN_gfxPhysicalDevice()

public:
    constexpr static epiMetaTypeID TypeID{0x334f63fd};

    enum gfxPhysicalDevice_PIDs
    {
        PID_Name = 0xfe11d138,
        PID_Type = 0x2cecf817,
        PID_COUNT = 2
    };

protected:
    epiString GetName_Callback() const;
    gfxPhysicalDeviceType GetType_Callback() const;

EPI_GENREGION_END(gfxPhysicalDevice)

public:
    friend class gfxSurface;

public:
    gfxPhysicalDevice() = default;
    explicit gfxPhysicalDevice(const std::shared_ptr<internalgfx::gfxPhysicalDeviceImpl>& impl);

public:
    std::optional<gfxDevice> CreateDevice(gfxQueueDescriptorList& queueDescriptorList,
                                          const epiArray<gfxPhysicalDeviceExtension>& extensionsRequired,
                                          const epiArray<gfxPhysicalDeviceFeature>& featuresRequired) const;

    // TODO: Introduce PhysicalDeviceLimits struct and move it there
    epiFloat GetMaxSamplerAnisotropy() const;

    gfxFormatProperties FormatPropertiesFor(gfxFormat format) const;

    epiBool IsExtensionSupported(gfxPhysicalDeviceExtension extension) const;
    epiBool IsFeatureSupported(gfxPhysicalDeviceFeature feature) const;
    epiBool IsQueueTypeSupported(gfxQueueType mask) const;

protected:
    epiPimpl<internalgfx::gfxPhysicalDeviceImpl> m_Impl;
};

EPI_NAMESPACE_END()
