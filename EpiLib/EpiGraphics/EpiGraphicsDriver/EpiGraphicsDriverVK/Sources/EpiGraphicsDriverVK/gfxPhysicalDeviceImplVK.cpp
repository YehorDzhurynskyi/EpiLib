#include "EpiGraphicsDriverVK/gfxPhysicalDeviceImplVK.h"

#include "EpiGraphicsDriverVK/gfxSurfaceImplVK.h"

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

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(m_VkDevice, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(m_VkDevice, &queueFamilyCount, queueFamilies.data());

    epiU32 queueFamilyIndex = 0;
    for (const auto& queueFamily : queueFamilies)
    {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            m_QueueFamilyIndices.FamilyGraphics = queueFamilyIndex;
        }

        if (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT)
        {
            m_QueueFamilyIndices.FamilyCompute = queueFamilyIndex;
        }

        if (queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT)
        {
            m_QueueFamilyIndices.FamilyTransfer = queueFamilyIndex;
        }

        if (queueFamily.queueFlags & VK_QUEUE_SPARSE_BINDING_BIT)
        {
            m_QueueFamilyIndices.FamilySparseBinding = queueFamilyIndex;
        }

        if (queueFamily.queueFlags & VK_QUEUE_PROTECTED_BIT)
        {
            m_QueueFamilyIndices.FamilyProtected = queueFamilyIndex;
        }

        VkBool32 presentSupported = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(m_VkDevice, queueFamilyIndex, surface.GetVkSurface(), &presentSupported);
        if (presentSupported)
        {
            m_QueueFamilyIndices.FamilyPresentation = queueFamilyIndex;
        }

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

epiBool gfxPhysicalDeviceImplVK::IsFeatureSupported(gfxPhysicalDeviceFeature feature) const
{
    const epiS32 at = static_cast<epiS32>(feature);
    epiAssert(at >= 0 && at < epiArrLen(m_Features));

    return m_Features[at];
}

epiBool gfxPhysicalDeviceImplVK::IsQueueFamilySupported(gfxQueueFamily mask) const
{
    epiBool supported = true;

    if (mask & gfxQueueFamily_Graphics)
    {
        supported = supported && m_QueueFamilyIndices.FamilyGraphics.has_value();
    }

    if (mask & gfxQueueFamily_Compute)
    {
        supported = supported && m_QueueFamilyIndices.FamilyCompute.has_value();
    }

    if (mask & gfxQueueFamily_Transfer)
    {
        supported = supported && m_QueueFamilyIndices.FamilyTransfer.has_value();
    }

    if (mask & gfxQueueFamily_SparseBinding)
    {
        supported = supported && m_QueueFamilyIndices.FamilySparseBinding.has_value();
    }

    if (mask & gfxQueueFamily_Protected)
    {
        supported = supported && m_QueueFamilyIndices.FamilyProtected.has_value();
    }

    if (mask & gfxQueueFamily_Presentation)
    {
        supported = supported && m_QueueFamilyIndices.FamilyPresentation.has_value();
    }

    return supported;
}

gfxPhysicalDeviceImpl::QueueFamilyIndices gfxPhysicalDeviceImplVK::GetQueueFamilyIndices() const
{
    return m_QueueFamilyIndices;
}

VkPhysicalDevice gfxPhysicalDeviceImplVK::GetVkPhysicalDevice() const
{
    return m_VkDevice;
}

} // namespace internalgfx

EPI_NAMESPACE_END()
