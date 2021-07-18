#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

#include "EpiGraphicsDriverVK/gfxQueueFamilyImplVK.h"

struct VkPhysicalDevice_T;

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxPhysicalDeviceImplVK : public gfxPhysicalDeviceImpl
{
public:
    void Init(VkPhysicalDevice_T* device);

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

} // namespace internalgfx

EPI_NAMESPACE_END()
