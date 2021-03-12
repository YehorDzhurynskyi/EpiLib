#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

#include "EpiGraphicsDriverVK/gfxQueueFamilyImplVK.h"

struct VkPhysicalDevice_T;

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxSurfaceImplVK;
class gfxPhysicalDeviceImplVK : public gfxPhysicalDeviceImpl
{
public:
    void Init(VkPhysicalDevice_T* device);

    epiString GetName() const override;
    gfxPhysicalDeviceType GetType() const override;

    std::unique_ptr<gfxDeviceImpl> CreateDevice(gfxQueueDescriptorList& queueDescriptorList,
                                                gfxPhysicalDeviceExtension extensionMask) const override;

    epiBool IsExtensionsSupported(gfxPhysicalDeviceExtension mask) const override;
    epiBool IsFeatureSupported(gfxPhysicalDeviceFeature feature) const override;
    epiBool IsQueueTypeSupported(gfxQueueType mask) const override;

    const epiArray<gfxQueueFamilyImplVK>& GetQueueFamilies() const;

    VkPhysicalDevice_T* GetVkPhysicalDevice() const;

protected:
    VkPhysicalDevice_T* m_VkDevice{nullptr};
    epiArray<gfxQueueFamilyImplVK> m_QueueFamilies;
};

} // namespace internalgfx

EPI_NAMESPACE_END()
