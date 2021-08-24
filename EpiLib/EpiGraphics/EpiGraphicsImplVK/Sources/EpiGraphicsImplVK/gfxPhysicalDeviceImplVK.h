#pragma once

#include "EpiGraphicsImpl/gfxPhysicalDeviceImpl.h"

struct VkPhysicalDevice_T;

EPI_NAMESPACE_BEGIN()

class gfxPhysicalDeviceImplVK : public gfxPhysicalDevice::Impl
{
public:
    explicit gfxPhysicalDeviceImplVK(const gfxInstance& instance);

    epiBool Init(VkPhysicalDevice_T* device);

    std::shared_ptr<gfxDevice::Impl> CreateDevice(const gfxDeviceCreateInfo& info) override;

    epiFloat GetMaxSamplerAnisotropy() const override;
    epiString GetName() const override;
    gfxPhysicalDeviceType GetType() const override;

    gfxFormatProperties FormatPropertiesFor(gfxFormat format) const override;

    epiBool IsExtensionSupported(gfxPhysicalDeviceExtension extension) const override;
    epiBool IsFeatureSupported(gfxPhysicalDeviceFeature feature) const override;
    epiBool IsQueueTypeSupported(gfxQueueType mask) const override;

    VkPhysicalDevice_T* GetVkPhysicalDevice() const;

protected:
    void FillExtensionsSupported();
    void FillFeaturesSupported();

protected:
    VkPhysicalDevice_T* m_VkDevice{nullptr};
    epiBool m_ExtensionSupported[static_cast<epiU32>(gfxPhysicalDeviceExtension::COUNT)]{};
    epiBool m_FeatureSupported[static_cast<epiU32>(gfxPhysicalDeviceFeature::COUNT)]{};
};

EPI_NAMESPACE_END()