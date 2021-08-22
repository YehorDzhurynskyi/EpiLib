#pragma once

#include "EpiGraphics/gfxPhysicalDevice.h"
#include "EpiGraphics/gfxInstance.h"

#include "EpiGraphicsImpl/gfxDeviceImpl.h"

EPI_NAMESPACE_BEGIN()

class gfxPhysicalDevice::Impl : public std::enable_shared_from_this<gfxPhysicalDevice::Impl>
{
public:
    static std::shared_ptr<gfxPhysicalDevice::Impl> ExtractImpl(const gfxPhysicalDevice& device) { return device.m_Impl; }

public:
    explicit Impl(const gfxInstance& instance);
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    virtual std::shared_ptr<gfxDevice::Impl> CreateDevice(const gfxDeviceCreateInfo & info) = 0;

    virtual epiFloat GetMaxSamplerAnisotropy() const = 0;
    virtual epiString GetName() const = 0;
    virtual gfxPhysicalDeviceType GetType() const = 0;

    virtual gfxFormatProperties FormatPropertiesFor(gfxFormat format) const = 0;

    virtual epiBool IsExtensionSupported(gfxPhysicalDeviceExtension extension) const = 0;
    virtual epiBool IsFeatureSupported(gfxPhysicalDeviceFeature feature) const = 0;
    virtual epiBool IsQueueTypeSupported(gfxQueueType mask) const = 0;

    const gfxInstance& GetInstance() const;
    const epiArray<std::shared_ptr<gfxQueueFamilyDescriptor::Impl>>& GetQueueFamilyDescriptors() const;

protected:
    gfxInstance m_Instance;
    epiArray<std::shared_ptr<gfxQueueFamilyDescriptor::Impl>> m_QueueFamilyDescriptors;
};

EPI_NAMESPACE_END()
