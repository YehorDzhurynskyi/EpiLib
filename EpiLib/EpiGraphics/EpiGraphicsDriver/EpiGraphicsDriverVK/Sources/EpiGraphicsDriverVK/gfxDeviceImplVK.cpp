#include "EpiGraphicsDriverVK/gfxDeviceImplVK.h"

#include "EpiGraphicsDriverVK/gfxPhysicalDeviceImplVK.h"
#include "EpiGraphicsDriverVK/gfxSurfaceImplVK.h"
#include "EpiGraphicsDriverVK/gfxQueueFamilyImplVK.h"
#include "EpiGraphicsDriverVK/gfxQueueImplVK.h"
#include "EpiGraphicsDriverVK/gfxSwapChainImplVK.h"
#include "EpiGraphicsDriverVK/gfxRenderPassImplVK.h"
#include "EpiGraphicsDriverVK/gfxPipelineImplVK.h"
#include "EpiGraphicsDriverVK/gfxShaderProgramImplVK.h"
#include "EpiGraphicsDriverVK/gfxFrameBufferImplVK.h"
#include "EpiGraphicsDriverVK/gfxTextureImplVK.h"
#include "EpiGraphicsDriverVK/gfxTextureViewImplVK.h"
#include "EpiGraphicsDriverVK/gfxCommandPoolImplVK.h"

#include "EpiGraphicsDriverCommon/gfxSurface.h"

#include <vulkan/vulkan.hpp>

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

const epiChar* ExtensionNameOf(gfxPhysicalDeviceExtension extension)
{
    const epiU32 at = static_cast<epiU32>(extension);
    epiAssert(at < epiArrLen(kDeviceExtensionNames));

    return kDeviceExtensionNames[at];
}

}

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

epiBool gfxDeviceImplVK::Init(const gfxPhysicalDeviceImplVK& physicalDevice,
                              gfxQueueDescriptorList& queueDescriptorList,
                              const epiArray<gfxPhysicalDeviceExtension>& extensionsRequired,
                              const epiArray<gfxPhysicalDeviceFeature>& featuresRequired)
{
    epiBool isSuitable = std::all_of(queueDescriptorList.begin(),
                                     queueDescriptorList.end(),
                                     [&physicalDevice](const gfxQueueDescriptor& queueDescriptor)
    {
        return physicalDevice.IsQueueTypeSupported(queueDescriptor.GetTypeMask());
    });
    isSuitable = isSuitable && std::all_of(extensionsRequired.begin(), extensionsRequired.end(), [&physicalDevice](gfxPhysicalDeviceExtension extension) {
        return physicalDevice.IsExtensionSupported(extension);
    });
    isSuitable = isSuitable && std::all_of(featuresRequired.begin(), featuresRequired.end(), [&physicalDevice](gfxPhysicalDeviceFeature feature)
    {
        return physicalDevice.IsFeatureSupported(feature);
    });

    if (!isSuitable)
    {
        return false;
    }

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    std::map<const gfxQueueDescriptor*, const gfxQueueFamilyDescriptorImplVK*> queueMappings;

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    for (gfxQueueDescriptor& queueDescriptor : queueDescriptorList)
    {
        for (const gfxQueueFamilyDescriptorImplVK& queueFamilyDesc : physicalDevice.GetQueueFamilyDescriptors())
        {
            if (queueFamilyDesc.GetQueueCount() < queueDescriptor.GetQueueCount() ||
                !queueFamilyDesc.IsQueueTypeSupported(queueDescriptor.GetTypeMask()))
            {
                continue;
            }

            if (const epiPtrArray<gfxSurfaceImpl>& surfaceTargets = queueDescriptor.GetSurfaceTargets(); !surfaceTargets.IsEmpty())
            {
                const epiBool hasSupportForSurfaceTargets = std::all_of(surfaceTargets.begin(),
                                                                        surfaceTargets.end(),
                                                                        [&physicalDevice, &queueFamilyDesc](const gfxSurfaceImpl* surfaceTarget)
                {
                    return surfaceTarget != nullptr && surfaceTarget->IsPresentSupportedFor(physicalDevice, queueFamilyDesc);
                });

                if (!hasSupportForSurfaceTargets)
                {
                    continue;
                }
            }

            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueCount = queueDescriptor.GetQueueCount();
            queueCreateInfo.queueFamilyIndex = queueFamilyDesc.GetIndex();
            queueCreateInfo.pQueuePriorities = queueDescriptor.GetPriorities().data();

            queueMappings[&queueDescriptor] = &queueFamilyDesc;

            queueCreateInfos.push_back(queueCreateInfo);

            break;
        }
    }

    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.queueCreateInfoCount = queueCreateInfos.size();

    const epiBool allQueueDescriptorsResolved = std::all_of(queueDescriptorList.begin(),
                                                            queueDescriptorList.end(),
                                                            [&queueMappings](const gfxQueueDescriptor& desc)
    {
        return queueMappings.find(&desc) != queueMappings.end();
    });

    if (!allQueueDescriptorsResolved)
    {
        epiLogError("Couldn't resolve some of submitted queue descriptors!");
        return false;
    }

    const epiBool hasNoQueueFamilyDuplicates = std::all_of(queueMappings.begin(),
                                                           queueMappings.end(),
                                                           [&queueMappings](const std::pair<const gfxQueueDescriptor*, const gfxQueueFamilyDescriptorImplVK*>& lhs)
    {
        const gfxQueueFamilyDescriptorImplVK* needle = lhs.second;
        const epiU32 count = std::count_if(queueMappings.begin(),
                                           queueMappings.end(),
                                           [&needle](const std::pair<const gfxQueueDescriptor*, const gfxQueueFamilyDescriptorImplVK*>& rhs)
        {
            return rhs.second == needle;
        });

        return count == 1;
    });

    if (!hasNoQueueFamilyDuplicates)
    {
        // TODO: implement QueueDescriptor -> QueueFamily (many - one) relationship
        epiLogError("There is queue descriptors that map a single queue family! This feature isn't supported yet!");
        return false;
    }

    std::vector<const epiChar*> extensions;
    for (gfxPhysicalDeviceExtension extension : extensionsRequired)
    {
        if (!physicalDevice.IsExtensionSupported(extension))
        {
            // TODO: get string representation
            epiLogError("Required Vulkan device extension=`{}` is not supported!", extension);
            return false;
        }

        m_ExtensionEnabled[static_cast<epiU32>(extension)] = true;
        extensions.push_back(ExtensionNameOf(extension));
    }

    // NOTE: enable advanced vk api (like VkPhysicalDeviceFeatures2 etc)
    extensions.push_back(VK_KHR_MAINTENANCE2_EXTENSION_NAME);

    void* deviceCreateInfoNext = nullptr;

    // TODO: introduce RETAIL build config
#if EPI_NSIGHT_AFTERMATH
    extensions.push_back(VK_NV_DEVICE_DIAGNOSTICS_CONFIG_EXTENSION_NAME);
    extensions.push_back(VK_NV_DEVICE_DIAGNOSTIC_CHECKPOINTS_EXTENSION_NAME);

    VkDeviceDiagnosticsConfigCreateInfoNV diagnosticsConfigCreateInfoNV{};
    diagnosticsConfigCreateInfoNV.sType = VK_STRUCTURE_TYPE_DEVICE_DIAGNOSTICS_CONFIG_CREATE_INFO_NV;
    diagnosticsConfigCreateInfoNV.pNext = deviceCreateInfoNext;
    deviceCreateInfoNext = &diagnosticsConfigCreateInfoNV;
    diagnosticsConfigCreateInfoNV.flags = VK_DEVICE_DIAGNOSTICS_CONFIG_ENABLE_SHADER_DEBUG_INFO_BIT_NV |
                                          VK_DEVICE_DIAGNOSTICS_CONFIG_ENABLE_RESOURCE_TRACKING_BIT_NV |
                                          VK_DEVICE_DIAGNOSTICS_CONFIG_ENABLE_AUTOMATIC_CHECKPOINTS_BIT_NV;
#endif // EPI_NSIGHT_AFTERMATH

    createInfo.enabledExtensionCount = extensions.size();
    createInfo.ppEnabledExtensionNames = extensions.data();

    createInfo.pEnabledFeatures = nullptr;

    VkPhysicalDeviceVulkan12Features features12{};
    features12.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
    features12.pNext = deviceCreateInfoNext;
    deviceCreateInfoNext = &features12;

    VkPhysicalDeviceVulkan11Features features11{};
    features11.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES;
    features11.pNext = deviceCreateInfoNext;
    deviceCreateInfoNext = &features11;

    VkPhysicalDeviceFeatures2 features{};
    features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
    features.pNext = deviceCreateInfoNext;
    deviceCreateInfoNext = &features;

    VkBool32* const kFeatures[]
    {
        &features.features.robustBufferAccess,
        &features.features.fullDrawIndexUint32,
        &features.features.imageCubeArray,
        &features.features.independentBlend,
        &features.features.geometryShader,
        &features.features.tessellationShader,
        &features.features.sampleRateShading,
        &features.features.dualSrcBlend,
        &features.features.logicOp,
        &features.features.multiDrawIndirect,
        &features.features.drawIndirectFirstInstance,
        &features.features.depthClamp,
        &features.features.depthBiasClamp,
        &features.features.fillModeNonSolid,
        &features.features.depthBounds,
        &features.features.wideLines,
        &features.features.largePoints,
        &features.features.alphaToOne,
        &features.features.multiViewport,
        &features.features.samplerAnisotropy,
        &features.features.textureCompressionETC2,
        &features.features.textureCompressionASTC_LDR,
        &features.features.textureCompressionBC,
        &features.features.occlusionQueryPrecise,
        &features.features.pipelineStatisticsQuery,
        &features.features.vertexPipelineStoresAndAtomics,
        &features.features.fragmentStoresAndAtomics,
        &features.features.shaderTessellationAndGeometryPointSize,
        &features.features.shaderImageGatherExtended,
        &features.features.shaderStorageImageExtendedFormats,
        &features.features.shaderStorageImageMultisample,
        &features.features.shaderStorageImageReadWithoutFormat,
        &features.features.shaderStorageImageWriteWithoutFormat,
        &features.features.shaderUniformBufferArrayDynamicIndexing,
        &features.features.shaderSampledImageArrayDynamicIndexing,
        &features.features.shaderStorageBufferArrayDynamicIndexing,
        &features.features.shaderStorageImageArrayDynamicIndexing,
        &features.features.shaderClipDistance,
        &features.features.shaderCullDistance,
        &features.features.shaderFloat64,
        &features.features.shaderInt64,
        &features.features.shaderInt16,
        &features.features.shaderResourceResidency,
        &features.features.shaderResourceMinLod,
        &features.features.sparseBinding,
        &features.features.sparseResidencyBuffer,
        &features.features.sparseResidencyImage2D,
        &features.features.sparseResidencyImage3D,
        &features.features.sparseResidency2Samples,
        &features.features.sparseResidency4Samples,
        &features.features.sparseResidency8Samples,
        &features.features.sparseResidency16Samples,
        &features.features.sparseResidencyAliased,
        &features.features.variableMultisampleRate,
        &features.features.inheritedQueries,

        &features11.storageBuffer16BitAccess,
        &features11.uniformAndStorageBuffer16BitAccess,
        &features11.storagePushConstant16,
        &features11.storageInputOutput16,
        &features11.multiview,
        &features11.multiviewGeometryShader,
        &features11.multiviewTessellationShader,
        &features11.variablePointersStorageBuffer,
        &features11.variablePointers,
        &features11.protectedMemory,
        &features11.samplerYcbcrConversion,
        &features11.shaderDrawParameters,

        &features12.samplerMirrorClampToEdge,
        &features12.drawIndirectCount,
        &features12.storageBuffer8BitAccess,
        &features12.uniformAndStorageBuffer8BitAccess,
        &features12.storagePushConstant8,
        &features12.shaderBufferInt64Atomics,
        &features12.shaderSharedInt64Atomics,
        &features12.shaderFloat16,
        &features12.shaderInt8,
        &features12.descriptorIndexing,
        &features12.shaderInputAttachmentArrayDynamicIndexing,
        &features12.shaderUniformTexelBufferArrayDynamicIndexing,
        &features12.shaderStorageTexelBufferArrayDynamicIndexing,
        &features12.shaderUniformBufferArrayNonUniformIndexing,
        &features12.shaderSampledImageArrayNonUniformIndexing,
        &features12.shaderStorageBufferArrayNonUniformIndexing,
        &features12.shaderStorageImageArrayNonUniformIndexing,
        &features12.shaderInputAttachmentArrayNonUniformIndexing,
        &features12.shaderUniformTexelBufferArrayNonUniformIndexing,
        &features12.shaderStorageTexelBufferArrayNonUniformIndexing,
        &features12.descriptorBindingUniformBufferUpdateAfterBind,
        &features12.descriptorBindingSampledImageUpdateAfterBind,
        &features12.descriptorBindingStorageImageUpdateAfterBind,
        &features12.descriptorBindingStorageBufferUpdateAfterBind,
        &features12.descriptorBindingUniformTexelBufferUpdateAfterBind,
        &features12.descriptorBindingStorageTexelBufferUpdateAfterBind,
        &features12.descriptorBindingUpdateUnusedWhilePending,
        &features12.descriptorBindingPartiallyBound,
        &features12.descriptorBindingVariableDescriptorCount,
        &features12.runtimeDescriptorArray,
        &features12.samplerFilterMinmax,
        &features12.scalarBlockLayout,
        &features12.imagelessFramebuffer,
        &features12.uniformBufferStandardLayout,
        &features12.shaderSubgroupExtendedTypes,
        &features12.separateDepthStencilLayouts,
        &features12.hostQueryReset,
        &features12.timelineSemaphore,
        &features12.bufferDeviceAddress,
        &features12.bufferDeviceAddressCaptureReplay,
        &features12.bufferDeviceAddressMultiDevice,
        &features12.vulkanMemoryModel,
        &features12.vulkanMemoryModelDeviceScope,
        &features12.vulkanMemoryModelAvailabilityVisibilityChains,
        &features12.shaderOutputViewportIndex,
        &features12.shaderOutputLayer,
        &features12.subgroupBroadcastDynamicId
    };
    static_assert(epiArrLen(kFeatures) == static_cast<epiU32>(gfxPhysicalDeviceFeature::COUNT));

    for (gfxPhysicalDeviceFeature feature : featuresRequired)
    {
        if (!physicalDevice.IsFeatureSupported(feature))
        {
            // TODO: get string representation
            epiLogError("Required Vulkan device feature=`{}` is not supported!", feature);
            return false;
        }

        *kFeatures[static_cast<epiU32>(feature)] = true;
        m_FeatureEnabled[static_cast<epiU32>(feature)] = true;
    }

    createInfo.pNext = deviceCreateInfoNext;

    const VkResult resultCreateDevice = vkCreateDevice(physicalDevice.GetVkPhysicalDevice(), &createInfo, nullptr, &m_VkDevice);
    if (resultCreateDevice != VK_SUCCESS)
    {
        return false;
    }

    for (const auto& [queueDesc, queueFamilyDesc] : queueMappings)
    {
        std::shared_ptr<gfxQueueFamilyImplVK> queueFamily = std::make_shared<gfxQueueFamilyImplVK>(*queueFamilyDesc);
        queueFamily->Init(*this, *queueDesc);

        m_QueueFamilies.push_back(std::move(queueFamily));
    }

    // TODO: maybe assign QueueFamilies to QueueDescriptors

    return true;
}

gfxDeviceImplVK::~gfxDeviceImplVK()
{
    if (m_VkDevice != VK_NULL_HANDLE)
    {
        vkDestroyDevice(m_VkDevice, nullptr);
    }
}

epiBool gfxDeviceImplVK::IsExtensionEnabled(gfxPhysicalDeviceExtension extension) const
{
    return m_ExtensionEnabled[static_cast<epiU32>(extension)];
}

epiBool gfxDeviceImplVK::IsFeatureEnabled(gfxPhysicalDeviceFeature feature) const
{
    return m_FeatureEnabled[static_cast<epiU32>(feature)];
}

std::shared_ptr<gfxSwapChainImpl> gfxDeviceImplVK::CreateSwapChain(const gfxSwapChainCreateInfo& info,
                                                                   const gfxSurfaceImpl& surfaceImpl,
                                                                   const gfxQueueFamilyImpl& queueFamilyImpl) const
{
    std::shared_ptr<gfxSwapChainImplVK> impl = std::make_shared<gfxSwapChainImplVK>(*this);
    if (!impl->Init(info, surfaceImpl, queueFamilyImpl))
    {
        impl.reset();
    }

    return impl;
}

std::shared_ptr<gfxRenderPassImpl> gfxDeviceImplVK::CreateRenderPass(const gfxRenderPassCreateInfo& info) const
{
    std::shared_ptr<gfxRenderPassImplVK> impl = std::make_shared<gfxRenderPassImplVK>(m_VkDevice);
    if (!impl->Init(info))
    {
        impl.reset();
    }

    return impl;
}

std::shared_ptr<gfxRenderPassImpl> gfxDeviceImplVK::CreateRenderPassFromSchema(const gfxRenderPassSchema& schema) const
{
    std::shared_ptr<gfxRenderPassImplVK> impl = std::make_shared<gfxRenderPassImplVK>(m_VkDevice);
    if (!impl->Init(schema))
    {
        impl.reset();
    }

    return impl;
}

std::shared_ptr<gfxPipelineGraphicsImpl> gfxDeviceImplVK::CreatePipelineGraphics(const gfxPipelineGraphicsCreateInfo& info,
                                                                                 const gfxShaderProgramImpl& shaderProgramImpl,
                                                                                 const gfxRenderPassImpl& renderPassImpl) const
{
    std::shared_ptr<gfxPipelineGraphicsImplVK> impl = std::make_shared<gfxPipelineGraphicsImplVK>(*this);
    if (!impl->Init(info, shaderProgramImpl, renderPassImpl))
    {
        impl.reset();
    }

    return impl;
}

std::shared_ptr<gfxShaderImpl> gfxDeviceImplVK::CreateShaderFromSource(const epiChar* source, gfxShaderType type, const epiChar* entryPoint) const
{
    std::shared_ptr<gfxShaderImplVK> impl = std::make_shared<gfxShaderImplVK>(m_VkDevice);
    if (!impl->InitFromSource(source, type, entryPoint))
    {
        impl.reset();
    }

    return impl;
}

std::shared_ptr<gfxShaderImpl> gfxDeviceImplVK::CreateShaderFromBinary(const epiU8* binary, epiSize_t size, gfxShaderType type, const epiChar* entryPoint) const
{
    std::shared_ptr<gfxShaderImplVK> impl = std::make_shared<gfxShaderImplVK>(m_VkDevice);
    if (!impl->InitFromBinary(binary, size, type, entryPoint))
    {
        impl.reset();
    }

    return impl;
}

std::shared_ptr<gfxShaderProgramImpl> gfxDeviceImplVK::CreateShaderProgram(const gfxShaderProgramCreateInfoImpl& info) const
{
    std::shared_ptr<gfxShaderProgramImplVK> impl = std::make_shared<gfxShaderProgramImplVK>();
    if (!impl->Init(info))
    {
        impl.reset();
    }

    return impl;
}

std::shared_ptr<gfxFrameBufferImpl> gfxDeviceImplVK::CreateFrameBuffer(const gfxFrameBufferCreateInfo& info, const gfxRenderPassImpl& renderPassImpl) const
{
    std::shared_ptr<gfxFrameBufferImplVK> impl = std::make_shared<gfxFrameBufferImplVK>(m_VkDevice);
    if (!impl->Init(info, renderPassImpl))
    {
        impl.reset();
    }

    return impl;
}

std::shared_ptr<gfxTextureImpl> gfxDeviceImplVK::CreateTexture(const gfxTextureCreateInfo& info) const
{
    std::shared_ptr<gfxTextureImplVKOwner> impl = std::make_shared<gfxTextureImplVKOwner>(m_VkDevice);
    if (!impl->Init(info))
    {
        impl.reset();
    }

    return impl;
}

std::shared_ptr<gfxTextureViewImpl> gfxDeviceImplVK::CreateTextureView(const gfxTextureViewCreateInfo& info, const gfxTextureImpl& textureImpl) const
{
    std::shared_ptr<gfxTextureViewImplVK> impl = std::make_shared<gfxTextureViewImplVK>(m_VkDevice);
    if (!impl->Init(info, textureImpl))
    {
        impl.reset();
    }

    return impl;
}

std::shared_ptr<gfxCommandPoolImpl> gfxDeviceImplVK::CreateCommandPool(const gfxCommandPoolCreateInfo& info, const gfxQueueFamilyImpl& queueFamilyImpl) const
{
    std::shared_ptr<gfxCommandPoolImplVK> impl = std::make_shared<gfxCommandPoolImplVK>(m_VkDevice);
    if (!impl->Init(info, queueFamilyImpl))
    {
        impl.reset();
    }

    return impl;
}

VkDevice gfxDeviceImplVK::GetVkDevice() const
{
    return m_VkDevice;
}

} // namespace internalgfx

EPI_NAMESPACE_END()
