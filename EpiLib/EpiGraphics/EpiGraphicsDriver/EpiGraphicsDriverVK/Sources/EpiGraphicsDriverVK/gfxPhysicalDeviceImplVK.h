#include "EpiGraphicsDriverAPI/EpiGraphicsDriverAPI.h"

#include <vulkan/vulkan.hpp>

EPI_NAMESPACE_BEGIN()

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

    epiBool IsFeatureSupported(gfxPhysicalDeviceFeature feature) const override;
    epiBool IsQueueFamilySupported(gfxQueueFamily mask) const override;

    QueueFamilyIndices GetQueueFamilyIndices() const override;

    VkPhysicalDevice GetVkPhysicalDevice() const;

protected:
    VkPhysicalDevice m_VkDevice{VK_NULL_HANDLE};
    epiString m_Name{};
    gfxPhysicalDeviceType m_Type{gfxPhysicalDeviceType::None};
    epiBool m_Features[static_cast<epiSize_t>(gfxPhysicalDeviceFeature::COUNT)];
    QueueFamilyIndices m_QueueFamilyIndices;
};

EPI_NAMESPACE_END()
