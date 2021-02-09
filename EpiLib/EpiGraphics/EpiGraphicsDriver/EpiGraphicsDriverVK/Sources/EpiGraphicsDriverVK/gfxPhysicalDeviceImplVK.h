#pragma once

#include "EpiGraphicsDriverImpl/EpiGraphicsDriverImpl.h"

#include <vulkan/vulkan.hpp>

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxSurfaceImplVK;
class gfxPhysicalDeviceImplVK : public gfxPhysicalDeviceImpl
{
public:
    gfxPhysicalDeviceImplVK(VkPhysicalDevice device, const gfxSurfaceImplVK& surface);
    gfxPhysicalDeviceImplVK(const gfxPhysicalDeviceImplVK& rhs) = default;
    gfxPhysicalDeviceImplVK& operator=(const gfxPhysicalDeviceImplVK& rhs) = default;
    gfxPhysicalDeviceImplVK(gfxPhysicalDeviceImplVK&& rhs) = default;
    gfxPhysicalDeviceImplVK& operator=(gfxPhysicalDeviceImplVK&& rhs) = default;
    ~gfxPhysicalDeviceImplVK() override = default;

    epiString GetName() const override;
    gfxPhysicalDeviceType GetType() const override;

    gfxDeviceImpl* CreateDevice(gfxQueueType queueTypeMask, gfxPhysicalDeviceExtension extensionMask, epiBool presentSupportRequired) const override;

    epiBool IsFeatureSupported(gfxPhysicalDeviceFeature feature) const override;
    epiBool IsQueueTypeSupported(gfxQueueType mask) const override;
    epiBool IsPresentSupported() const override;

    const epiPtrArray<gfxQueueFamilyImpl>& GetQueueFamilies() const override;

    VkPhysicalDevice GetVkPhysicalDevice() const;

protected:
    VkPhysicalDevice m_VkDevice{VK_NULL_HANDLE};
    epiString m_Name{};
    gfxPhysicalDeviceType m_Type{gfxPhysicalDeviceType::None};
    epiBool m_Features[static_cast<epiSize_t>(gfxPhysicalDeviceFeature::COUNT)];
    epiPtrArray<gfxQueueFamilyImpl> m_QueueFamilies;
};

} // namespace internalgfx

EPI_NAMESPACE_END()
