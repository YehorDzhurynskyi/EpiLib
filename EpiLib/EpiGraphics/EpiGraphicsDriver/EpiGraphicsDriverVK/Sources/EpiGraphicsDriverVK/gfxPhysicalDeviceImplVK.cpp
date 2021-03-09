#include "EpiGraphicsDriverVK/gfxPhysicalDeviceImplVK.h"

#include "EpiGraphicsDriverVK/gfxSurfaceImplVK.h"
#include "EpiGraphicsDriverVK/gfxQueueFamilyImplVK.h"
#include "EpiGraphicsDriverVK/gfxDeviceImplVK.h"

#include <vulkan/vulkan.hpp>

namespace
{

EPI_NAMESPACE_USING()

gfxPhysicalDeviceExtension SupportedPhysicalDeviceExtensionMask(VkPhysicalDevice device)
{
    epiU32 supportedExtensionsCount = 0;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &supportedExtensionsCount, nullptr);

    std::vector<VkExtensionProperties> supportedExtensions(supportedExtensionsCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &supportedExtensionsCount, supportedExtensions.data());

    epiU64 mask = 0;
    for (const auto& extension : supportedExtensions)
    {
        if (strcmp(extension.extensionName, VK_KHR_SWAPCHAIN_EXTENSION_NAME) == 0)
        {
            mask |= gfxDriverExtension_Surface;
        }
        else
        {
            epiLogWarn("Unrecognized Vulkan instance extension=`{}`!", extension.extensionName);
        }
    }

    return static_cast<gfxPhysicalDeviceExtension>(mask);
}

}

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

void gfxPhysicalDeviceImplVK::Init(VkPhysicalDevice device)
{
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(m_VkDevice, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(m_VkDevice, &queueFamilyCount, queueFamilies.data());

    epiU32 queueFamilyIndex = 0;
    for (const auto& queueFamily : queueFamilies)
    {
        const gfxQueueType supportedQueueTypes = epiMask(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT ? gfxQueueType_Graphics : gfxQueueType{0},
                                                         queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT ? gfxQueueType_Compute : gfxQueueType{0},
                                                         queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT ? gfxQueueType_Transfer : gfxQueueType{0},
                                                         queueFamily.queueFlags & VK_QUEUE_SPARSE_BINDING_BIT ? gfxQueueType_SparseBinding : gfxQueueType{0},
                                                         queueFamily.queueFlags & VK_QUEUE_PROTECTED_BIT ? gfxQueueType_Protected : gfxQueueType{0});
        m_QueueFamilies.push_back(gfxQueueFamilyImplVK(queueFamilyIndex, queueFamily.queueCount, supportedQueueTypes));

        ++queueFamilyIndex;
    }
}

epiString gfxPhysicalDeviceImplVK::GetName() const
{
    VkPhysicalDeviceProperties properties;
    vkGetPhysicalDeviceProperties(m_VkDevice, &properties);

    return properties.deviceName;
}

gfxPhysicalDeviceType gfxPhysicalDeviceImplVK::GetType() const
{
    VkPhysicalDeviceProperties properties;
    vkGetPhysicalDeviceProperties(m_VkDevice, &properties);

    switch (properties.deviceType)
    {
    case VK_PHYSICAL_DEVICE_TYPE_OTHER: return gfxPhysicalDeviceType::Other;
    case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: return gfxPhysicalDeviceType::IntegratedGPU;
    case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU: return gfxPhysicalDeviceType::DiscreteGPU;
    case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU: return gfxPhysicalDeviceType::VirtualGPU;
    case VK_PHYSICAL_DEVICE_TYPE_CPU: return gfxPhysicalDeviceType::CPU;
    default: epiAssert(!"Unhandled case!");
    }

    return gfxPhysicalDeviceType::None;
}

std::unique_ptr<gfxDeviceImpl> gfxPhysicalDeviceImplVK::CreateDevice(gfxQueueDescriptorList& queueDescriptorList,
                                                                     gfxPhysicalDeviceExtension extensionMask) const
{
    std::unique_ptr<gfxDeviceImplVK> device = std::make_unique<gfxDeviceImplVK>();
    if (!device->Init(*this, queueDescriptorList, extensionMask))
    {
        return nullptr;
    }

    return device;
}

epiBool gfxPhysicalDeviceImplVK::IsPresentSupported(const gfxSurfaceImpl& surface) const
{
    return std::any_of(m_QueueFamilies.begin(), m_QueueFamilies.end(), [this, &surface](const gfxQueueFamilyImpl& queueFamily) {
        return IsPresentSupported(surface, queueFamily);
    });
}

epiBool gfxPhysicalDeviceImplVK::IsPresentSupported(const gfxSurfaceImpl& surface, const gfxQueueFamilyImpl& queueFamily) const
{
    const gfxSurfaceImplVK& surfaceVk = static_cast<const gfxSurfaceImplVK&>(surface);
    const gfxQueueFamilyImplVK& queueFamilyVk = static_cast<const gfxQueueFamilyImplVK&>(queueFamily);

    VkBool32 presentSupported = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(m_VkDevice, queueFamilyVk.GetIndex(), surfaceVk.GetVkSurface(), &presentSupported);

    return presentSupported;
}

epiBool gfxPhysicalDeviceImplVK::IsExtensionsSupported(gfxPhysicalDeviceExtension mask) const
{
    return (SupportedPhysicalDeviceExtensionMask(m_VkDevice) & mask) == mask;
}

epiBool gfxPhysicalDeviceImplVK::IsFeatureSupported(gfxPhysicalDeviceFeature feature) const
{
    VkPhysicalDeviceFeatures features;
    vkGetPhysicalDeviceFeatures(m_VkDevice, &features);

    switch (feature)
    {
    case gfxPhysicalDeviceFeature::GeometryShader: return features.geometryShader;
    case gfxPhysicalDeviceFeature::TessellationShader: return features.tessellationShader;
    case gfxPhysicalDeviceFeature::ShaderFloat64: return features.shaderFloat64;
    case gfxPhysicalDeviceFeature::ShaderInt64: return features.shaderInt64;
    case gfxPhysicalDeviceFeature::ShaderInt16: return features.shaderInt16;
    default: epiAssert(!"Unhandled case");
    }

    return false;
}

epiBool gfxPhysicalDeviceImplVK::IsQueueTypeSupported(gfxQueueType mask) const
{
    return std::any_of(m_QueueFamilies.begin(), m_QueueFamilies.end(), [mask](const gfxQueueFamilyImplVK& family)
    {
        return family.IsQueueTypeSupported(mask);
    });
}

VkPhysicalDevice gfxPhysicalDeviceImplVK::GetVkPhysicalDevice() const
{
    return m_VkDevice;
}

const epiArray<gfxQueueFamilyImplVK>& gfxPhysicalDeviceImplVK::GetQueueFamilies() const
{
    return m_QueueFamilies;
}

} // namespace internalgfx

EPI_NAMESPACE_END()
