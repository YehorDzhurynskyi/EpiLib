#include "EpiGraphicsDriverVK/gfxPhysicalDeviceImplVK.h"

#include "EpiGraphicsDriverVK/gfxEnumVK.h"
#include "EpiGraphicsDriverVK/gfxSurfaceImplVK.h"
#include "EpiGraphicsDriverVK/gfxQueueFamilyImplVK.h"
#include "EpiGraphicsDriverVK/gfxDeviceImplVK.h"

#include <vulkan/vulkan.h>

namespace
{

EPI_NAMESPACE_USING()

static constexpr const epiChar* kDeviceExtensionNames[]
{
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
    VK_KHR_IMAGELESS_FRAMEBUFFER_EXTENSION_NAME,
    VK_KHR_IMAGE_FORMAT_LIST_EXTENSION_NAME
};
static_assert(epiArrLen(kDeviceExtensionNames) == static_cast<epiU32>(gfxPhysicalDeviceExtension::COUNT));

}

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

void gfxPhysicalDeviceImplVK::Init(VkPhysicalDevice device)
{
    m_VkDevice = device;
    FillExtensionsSupported();
    FillFeaturesSupported();

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
        m_QueueFamilyDescriptors.push_back(gfxQueueFamilyDescriptorImplVK(queueFamilyIndex, queueFamily.queueCount, supportedQueueTypes));

        ++queueFamilyIndex;
    }
}

epiFloat gfxPhysicalDeviceImplVK::GetMaxSamplerAnisotropy() const
{
    VkPhysicalDeviceProperties properties;
    vkGetPhysicalDeviceProperties(m_VkDevice, &properties);

    return properties.limits.maxSamplerAnisotropy;
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
                                                                     const epiArray<gfxPhysicalDeviceExtension>& extensionsRequired,
                                                                     const epiArray<gfxPhysicalDeviceFeature>& featuresRequired) const
{
    std::unique_ptr<gfxDeviceImplVK> device = std::make_unique<gfxDeviceImplVK>(*this);
    if (!device->Init(queueDescriptorList, extensionsRequired, featuresRequired))
    {
        return nullptr;
    }

    return device;
}

gfxFormatProperties gfxPhysicalDeviceImplVK::FormatPropertiesFor(gfxFormat format) const
{
    VkFormatProperties propertiesVk;
    vkGetPhysicalDeviceFormatProperties(m_VkDevice, gfxFormatTo(format), &propertiesVk);

    gfxFormatProperties properties;
    properties.SetLinearTilingFeatureMask(gfxFormatFeatureMaskFrom(propertiesVk.linearTilingFeatures));
    properties.SetOptimalTilingFeatureMask(gfxFormatFeatureMaskFrom(propertiesVk.optimalTilingFeatures));
    properties.SetBufferFeatureMask(gfxFormatFeatureMaskFrom(propertiesVk.bufferFeatures));

    return properties;
}

epiBool gfxPhysicalDeviceImplVK::IsExtensionSupported(gfxPhysicalDeviceExtension extension) const
{
    return m_ExtensionSupported[static_cast<epiU32>(extension)];
}

epiBool gfxPhysicalDeviceImplVK::IsFeatureSupported(gfxPhysicalDeviceFeature feature) const
{
    return m_FeatureSupported[static_cast<epiU32>(feature)];
}

epiBool gfxPhysicalDeviceImplVK::IsQueueTypeSupported(gfxQueueType mask) const
{
    return std::any_of(m_QueueFamilyDescriptors.begin(), m_QueueFamilyDescriptors.end(), [mask](const gfxQueueFamilyDescriptorImplVK& family)
    {
        return family.IsQueueTypeSupported(mask);
    });
}

VkPhysicalDevice gfxPhysicalDeviceImplVK::GetVkPhysicalDevice() const
{
    return m_VkDevice;
}

const epiArray<gfxQueueFamilyDescriptorImplVK>& gfxPhysicalDeviceImplVK::GetQueueFamilyDescriptors() const
{
    return m_QueueFamilyDescriptors;
}

void gfxPhysicalDeviceImplVK::FillExtensionsSupported()
{
    epiU32 supportedExtensionsCount = 0;
    vkEnumerateDeviceExtensionProperties(m_VkDevice, nullptr, &supportedExtensionsCount, nullptr);

    std::vector<VkExtensionProperties> supportedExtensions(supportedExtensionsCount);
    vkEnumerateDeviceExtensionProperties(m_VkDevice, nullptr, &supportedExtensionsCount, supportedExtensions.data());

    for (const auto& extension : supportedExtensions)
    {
        const auto it = std::find_if(kDeviceExtensionNames,
                                     kDeviceExtensionNames + epiArrLen(kDeviceExtensionNames),
                                     [needle = extension.extensionName](const epiChar* name) {
            return strncmp(needle, name, strlen(name)) == 0;
        });

        if (it != kDeviceExtensionNames + epiArrLen(kDeviceExtensionNames))
        {
            m_ExtensionSupported[std::distance(kDeviceExtensionNames, it)] = true;
        }
        else
        {
            epiLogWarn("Unrecognized Vulkan physical device extension=`{}`!", extension.extensionName);
        }
    }
}

void gfxPhysicalDeviceImplVK::FillFeaturesSupported()
{
#if 0
    VkPhysicalDeviceVulkan12Features features12{};
    features12.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;

    VkPhysicalDeviceVulkan11Features features11{};
    features11.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES;
    features11.pNext = &features12;

    VkPhysicalDeviceFeatures2 features{};
    features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
    features.pNext = &features11;
    vkGetPhysicalDeviceFeatures2(m_VkDevice, &features);

    const VkBool32 kFeatures[]
    {
        features.features.robustBufferAccess,
        features.features.fullDrawIndexUint32,
        features.features.imageCubeArray,
        features.features.independentBlend,
        features.features.geometryShader,
        features.features.tessellationShader,
        features.features.sampleRateShading,
        features.features.dualSrcBlend,
        features.features.logicOp,
        features.features.multiDrawIndirect,
        features.features.drawIndirectFirstInstance,
        features.features.depthClamp,
        features.features.depthBiasClamp,
        features.features.fillModeNonSolid,
        features.features.depthBounds,
        features.features.wideLines,
        features.features.largePoints,
        features.features.alphaToOne,
        features.features.multiViewport,
        features.features.samplerAnisotropy,
        features.features.textureCompressionETC2,
        features.features.textureCompressionASTC_LDR,
        features.features.textureCompressionBC,
        features.features.occlusionQueryPrecise,
        features.features.pipelineStatisticsQuery,
        features.features.vertexPipelineStoresAndAtomics,
        features.features.fragmentStoresAndAtomics,
        features.features.shaderTessellationAndGeometryPointSize,
        features.features.shaderImageGatherExtended,
        features.features.shaderStorageImageExtendedFormats,
        features.features.shaderStorageImageMultisample,
        features.features.shaderStorageImageReadWithoutFormat,
        features.features.shaderStorageImageWriteWithoutFormat,
        features.features.shaderUniformBufferArrayDynamicIndexing,
        features.features.shaderSampledImageArrayDynamicIndexing,
        features.features.shaderStorageBufferArrayDynamicIndexing,
        features.features.shaderStorageImageArrayDynamicIndexing,
        features.features.shaderClipDistance,
        features.features.shaderCullDistance,
        features.features.shaderFloat64,
        features.features.shaderInt64,
        features.features.shaderInt16,
        features.features.shaderResourceResidency,
        features.features.shaderResourceMinLod,
        features.features.sparseBinding,
        features.features.sparseResidencyBuffer,
        features.features.sparseResidencyImage2D,
        features.features.sparseResidencyImage3D,
        features.features.sparseResidency2Samples,
        features.features.sparseResidency4Samples,
        features.features.sparseResidency8Samples,
        features.features.sparseResidency16Samples,
        features.features.sparseResidencyAliased,
        features.features.variableMultisampleRate,
        features.features.inheritedQueries,

        features11.storageBuffer16BitAccess,
        features11.uniformAndStorageBuffer16BitAccess,
        features11.storagePushConstant16,
        features11.storageInputOutput16,
        features11.multiview,
        features11.multiviewGeometryShader,
        features11.multiviewTessellationShader,
        features11.variablePointersStorageBuffer,
        features11.variablePointers,
        features11.protectedMemory,
        features11.samplerYcbcrConversion,
        features11.shaderDrawParameters,

        features12.samplerMirrorClampToEdge,
        features12.drawIndirectCount,
        features12.storageBuffer8BitAccess,
        features12.uniformAndStorageBuffer8BitAccess,
        features12.storagePushConstant8,
        features12.shaderBufferInt64Atomics,
        features12.shaderSharedInt64Atomics,
        features12.shaderFloat16,
        features12.shaderInt8,
        features12.descriptorIndexing,
        features12.shaderInputAttachmentArrayDynamicIndexing,
        features12.shaderUniformTexelBufferArrayDynamicIndexing,
        features12.shaderStorageTexelBufferArrayDynamicIndexing,
        features12.shaderUniformBufferArrayNonUniformIndexing,
        features12.shaderSampledImageArrayNonUniformIndexing,
        features12.shaderStorageBufferArrayNonUniformIndexing,
        features12.shaderStorageImageArrayNonUniformIndexing,
        features12.shaderInputAttachmentArrayNonUniformIndexing,
        features12.shaderUniformTexelBufferArrayNonUniformIndexing,
        features12.shaderStorageTexelBufferArrayNonUniformIndexing,
        features12.descriptorBindingUniformBufferUpdateAfterBind,
        features12.descriptorBindingSampledImageUpdateAfterBind,
        features12.descriptorBindingStorageImageUpdateAfterBind,
        features12.descriptorBindingStorageBufferUpdateAfterBind,
        features12.descriptorBindingUniformTexelBufferUpdateAfterBind,
        features12.descriptorBindingStorageTexelBufferUpdateAfterBind,
        features12.descriptorBindingUpdateUnusedWhilePending,
        features12.descriptorBindingPartiallyBound,
        features12.descriptorBindingVariableDescriptorCount,
        features12.runtimeDescriptorArray,
        features12.samplerFilterMinmax,
        features12.scalarBlockLayout,
        features12.imagelessFramebuffer,
        features12.uniformBufferStandardLayout,
        features12.shaderSubgroupExtendedTypes,
        features12.separateDepthStencilLayouts,
        features12.hostQueryReset,
        features12.timelineSemaphore,
        features12.bufferDeviceAddress,
        features12.bufferDeviceAddressCaptureReplay,
        features12.bufferDeviceAddressMultiDevice,
        features12.vulkanMemoryModel,
        features12.vulkanMemoryModelDeviceScope,
        features12.vulkanMemoryModelAvailabilityVisibilityChains,
        features12.shaderOutputViewportIndex,
        features12.shaderOutputLayer,
        features12.subgroupBroadcastDynamicId
    };
    static_assert(epiArrLen(kFeatures) == static_cast<epiU32>(gfxPhysicalDeviceFeature::COUNT));
#else
    VkPhysicalDeviceFeatures features{};
    vkGetPhysicalDeviceFeatures(m_VkDevice, &features);

    const VkBool32 kFeatures[]
    {
        features.robustBufferAccess,
        features.fullDrawIndexUint32,
        features.imageCubeArray,
        features.independentBlend,
        features.geometryShader,
        features.tessellationShader,
        features.sampleRateShading,
        features.dualSrcBlend,
        features.logicOp,
        features.multiDrawIndirect,
        features.drawIndirectFirstInstance,
        features.depthClamp,
        features.depthBiasClamp,
        features.fillModeNonSolid,
        features.depthBounds,
        features.wideLines,
        features.largePoints,
        features.alphaToOne,
        features.multiViewport,
        features.samplerAnisotropy,
        features.textureCompressionETC2,
        features.textureCompressionASTC_LDR,
        features.textureCompressionBC,
        features.occlusionQueryPrecise,
        features.pipelineStatisticsQuery,
        features.vertexPipelineStoresAndAtomics,
        features.fragmentStoresAndAtomics,
        features.shaderTessellationAndGeometryPointSize,
        features.shaderImageGatherExtended,
        features.shaderStorageImageExtendedFormats,
        features.shaderStorageImageMultisample,
        features.shaderStorageImageReadWithoutFormat,
        features.shaderStorageImageWriteWithoutFormat,
        features.shaderUniformBufferArrayDynamicIndexing,
        features.shaderSampledImageArrayDynamicIndexing,
        features.shaderStorageBufferArrayDynamicIndexing,
        features.shaderStorageImageArrayDynamicIndexing,
        features.shaderClipDistance,
        features.shaderCullDistance,
        features.shaderFloat64,
        features.shaderInt64,
        features.shaderInt16,
        features.shaderResourceResidency,
        features.shaderResourceMinLod,
        features.sparseBinding,
        features.sparseResidencyBuffer,
        features.sparseResidencyImage2D,
        features.sparseResidencyImage3D,
        features.sparseResidency2Samples,
        features.sparseResidency4Samples,
        features.sparseResidency8Samples,
        features.sparseResidency16Samples,
        features.sparseResidencyAliased,
        features.variableMultisampleRate,
        features.inheritedQueries,

        false, // features11.storageBuffer16BitAccess
        false, // features11.uniformAndStorageBuffer16BitAccess
        false, // features11.storagePushConstant16
        false, // features11.storageInputOutput16
        false, // features11.multiview
        false, // features11.multiviewGeometryShader
        false, // features11.multiviewTessellationShader
        false, // features11.variablePointersStorageBuffer
        false, // features11.variablePointers
        false, // features11.protectedMemory
        false, // features11.samplerYcbcrConversion
        false, // features11.shaderDrawParameters

        false, // features12.samplerMirrorClampToEdge
        false, // features12.drawIndirectCount
        false, // features12.storageBuffer8BitAccess
        false, // features12.uniformAndStorageBuffer8BitAccess
        false, // features12.storagePushConstant8
        false, // features12.shaderBufferInt64Atomics
        false, // features12.shaderSharedInt64Atomics
        false, // features12.shaderFloat16
        false, // features12.shaderInt8
        false, // features12.descriptorIndexing
        false, // features12.shaderInputAttachmentArrayDynamicIndexing
        false, // features12.shaderUniformTexelBufferArrayDynamicIndexing
        false, // features12.shaderStorageTexelBufferArrayDynamicIndexing
        false, // features12.shaderUniformBufferArrayNonUniformIndexing
        false, // features12.shaderSampledImageArrayNonUniformIndexing
        false, // features12.shaderStorageBufferArrayNonUniformIndexing
        false, // features12.shaderStorageImageArrayNonUniformIndexing
        false, // features12.shaderInputAttachmentArrayNonUniformIndexing
        false, // features12.shaderUniformTexelBufferArrayNonUniformIndexing
        false, // features12.shaderStorageTexelBufferArrayNonUniformIndexing
        false, // features12.descriptorBindingUniformBufferUpdateAfterBind
        false, // features12.descriptorBindingSampledImageUpdateAfterBind
        false, // features12.descriptorBindingStorageImageUpdateAfterBind
        false, // features12.descriptorBindingStorageBufferUpdateAfterBind
        false, // features12.descriptorBindingUniformTexelBufferUpdateAfterBind
        false, // features12.descriptorBindingStorageTexelBufferUpdateAfterBind
        false, // features12.descriptorBindingUpdateUnusedWhilePending
        false, // features12.descriptorBindingPartiallyBound
        false, // features12.descriptorBindingVariableDescriptorCount
        false, // features12.runtimeDescriptorArray
        false, // features12.samplerFilterMinmax
        false, // features12.scalarBlockLayout
        false, // features12.imagelessFramebuffer
        false, // features12.uniformBufferStandardLayout
        false, // features12.shaderSubgroupExtendedTypes
        false, // features12.separateDepthStencilLayouts
        false, // features12.hostQueryReset
        false, // features12.timelineSemaphore
        false, // features12.bufferDeviceAddress
        false, // features12.bufferDeviceAddressCaptureReplay
        false, // features12.bufferDeviceAddressMultiDevice
        false, // features12.vulkanMemoryModel
        false, // features12.vulkanMemoryModelDeviceScope
        false, // features12.vulkanMemoryModelAvailabilityVisibilityChains
        false, // features12.shaderOutputViewportIndex
        false, // features12.shaderOutputLayer
        false // features12.subgroupBroadcastDynamicId
    };
    static_assert(epiArrLen(kFeatures) == static_cast<epiU32>(gfxPhysicalDeviceFeature::COUNT));
#endif

    for (epiU32 i = 0; i < static_cast<epiU32>(gfxPhysicalDeviceFeature::COUNT); ++i)
    {
        m_FeatureSupported[i] = kFeatures[i];
    }
}

} // namespace internalgfx

EPI_NAMESPACE_END()
