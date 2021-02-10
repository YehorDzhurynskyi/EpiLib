#include "EpiGraphicsDriverVK/gfxPhysicalDeviceImplVK.h"

#include "EpiGraphicsDriverVK/gfxSurfaceImplVK.h"
#include "EpiGraphicsDriverVK/gfxQueueFamilyImplVK.h"
#include "EpiGraphicsDriverVK/gfxDeviceImplVK.h"

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

gfxPhysicalDeviceImplVK::gfxPhysicalDeviceImplVK(VkPhysicalDevice device, const gfxSurfaceImplVK& surface)
    : m_VkDevice{device}
{
    VkPhysicalDeviceProperties properties;
    vkGetPhysicalDeviceProperties(m_VkDevice, &properties);

    m_Name = properties.deviceName;

    switch (properties.deviceType)
    {
    case VK_PHYSICAL_DEVICE_TYPE_OTHER: m_Type = gfxPhysicalDeviceType::Other; break;
    case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: m_Type = gfxPhysicalDeviceType::IntegratedGPU; break;
    case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU: m_Type = gfxPhysicalDeviceType::DiscreteGPU; break;
    case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU: m_Type = gfxPhysicalDeviceType::VirtualGPU; break;
    case VK_PHYSICAL_DEVICE_TYPE_CPU: m_Type = gfxPhysicalDeviceType::CPU; break;
    default: epiAssert(!"Unhandled case!");
    }

    VkPhysicalDeviceFeatures features;
    vkGetPhysicalDeviceFeatures(m_VkDevice, &features);

    epiFor(epiArrLen(m_Features))
    {
        const gfxPhysicalDeviceFeature feature = static_cast<gfxPhysicalDeviceFeature>(index);
        switch (feature)
        {
        case gfxPhysicalDeviceFeature::GeometryShader: m_Features[index] = features.geometryShader; break;
        case gfxPhysicalDeviceFeature::TessellationShader: m_Features[index] = features.tessellationShader; break;
        case gfxPhysicalDeviceFeature::ShaderFloat64: m_Features[index] = features.shaderFloat64; break;
        case gfxPhysicalDeviceFeature::ShaderInt64: m_Features[index] = features.shaderInt64; break;
        case gfxPhysicalDeviceFeature::ShaderInt16: m_Features[index] = features.shaderInt16; break;
        default: epiAssert(!"Unhandled case");
        }
    }

    m_ExtensionMaskSupported = SupportedPhysicalDeviceExtensionMask(m_VkDevice);

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(m_VkDevice, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(m_VkDevice, &queueFamilyCount, queueFamilies.data());

    epiU32 queueFamilyIndex = 0;
    for (const auto& queueFamily : queueFamilies)
    {
        epiU32 mask = 0;
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            mask |= gfxQueueType_Graphics;
        }

        if (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT)
        {
            mask |= gfxQueueType_Compute;
        }

        if (queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT)
        {
            mask |= gfxQueueType_Transfer;
        }

        if (queueFamily.queueFlags & VK_QUEUE_SPARSE_BINDING_BIT)
        {
            mask |= gfxQueueType_SparseBinding;
        }

        if (queueFamily.queueFlags & VK_QUEUE_PROTECTED_BIT)
        {
            mask |= gfxQueueType_Protected;
        }

        const gfxQueueType supportedQueueTypes = static_cast<gfxQueueType>(mask);

        VkBool32 presentSupported = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(m_VkDevice, queueFamilyIndex, surface.GetVkSurface(), &presentSupported);

        m_QueueFamilies.push_back(new gfxQueueFamilyImplVK(queueFamilyIndex, queueFamily.queueCount, supportedQueueTypes, presentSupported));

        ++queueFamilyIndex;
    }
}

epiString gfxPhysicalDeviceImplVK::GetName() const
{
    return m_Name;
}

gfxPhysicalDeviceType gfxPhysicalDeviceImplVK::GetType() const
{
    return m_Type;
}

gfxDeviceImpl* gfxPhysicalDeviceImplVK::CreateDevice(gfxQueueType queueTypeMask, gfxPhysicalDeviceExtension extensionMask, epiBool presentSupportRequired) const
{
    const epiBool isSuitable = IsQueueTypeSupported(queueTypeMask) &&
                               IsExtensionsSupported(extensionMask) &&
                               (!presentSupportRequired || IsPresentSupported());

    if (!isSuitable)
    {
        return nullptr;
    }

    return new gfxDeviceImplVK(*this, queueTypeMask, extensionMask, presentSupportRequired);
}

epiBool gfxPhysicalDeviceImplVK::IsExtensionsSupported(gfxPhysicalDeviceExtension mask) const
{
    return (m_ExtensionMaskSupported & mask) == mask;
}

epiBool gfxPhysicalDeviceImplVK::IsFeatureSupported(gfxPhysicalDeviceFeature feature) const
{
    const epiS32 at = static_cast<epiS32>(feature);
    epiAssert(at >= 0 && at < epiArrLen(m_Features));

    return m_Features[at];
}

epiBool gfxPhysicalDeviceImplVK::IsQueueTypeSupported(gfxQueueType mask) const
{
    return std::any_of(m_QueueFamilies.begin(), m_QueueFamilies.end(), [mask](const gfxQueueFamilyImpl* family)
    {
        return family->IsQueueTypeSupported(mask);
    });
}

epiBool gfxPhysicalDeviceImplVK::IsPresentSupported() const
{
    return std::any_of(m_QueueFamilies.begin(), m_QueueFamilies.end(), [](const gfxQueueFamilyImpl* family)
    {
        return family->IsPresentSupported();
    });
}

const epiPtrArray<gfxQueueFamilyImpl>& gfxPhysicalDeviceImplVK::GetQueueFamilies() const
{
    return m_QueueFamilies;
}

VkPhysicalDevice gfxPhysicalDeviceImplVK::GetVkPhysicalDevice() const
{
    return m_VkDevice;
}

} // namespace internalgfx

EPI_NAMESPACE_END()
