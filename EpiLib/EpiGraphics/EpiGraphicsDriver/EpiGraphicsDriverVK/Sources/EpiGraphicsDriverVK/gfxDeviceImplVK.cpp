#include "EpiGraphicsDriverVK/gfxDeviceImplVK.h"

#include "EpiGraphicsDriverVK/gfxErrorVK.h"
#include "EpiGraphicsDriverVK/gfxEnumVK.h"
#include "EpiGraphicsDriverVK/gfxPhysicalDeviceImplVK.h"
#include "EpiGraphicsDriverVK/gfxSurfaceImplVK.h"
#include "EpiGraphicsDriverVK/gfxQueueFamilyImplVK.h"
#include "EpiGraphicsDriverVK/gfxQueueImplVK.h"
#include "EpiGraphicsDriverVK/gfxSwapChainImplVK.h"
#include "EpiGraphicsDriverVK/gfxRenderPassImplVK.h"
#include "EpiGraphicsDriverVK/gfxPipelineLayoutImplVK.h"
#include "EpiGraphicsDriverVK/gfxPipelineImplVK.h"
#include "EpiGraphicsDriverVK/gfxShaderProgramImplVK.h"
#include "EpiGraphicsDriverVK/gfxFrameBufferImplVK.h"
#include "EpiGraphicsDriverVK/gfxTextureImplVK.h"
#include "EpiGraphicsDriverVK/gfxTextureViewImplVK.h"
#include "EpiGraphicsDriverVK/gfxSamplerImplVK.h"
#include "EpiGraphicsDriverVK/gfxCommandPoolImplVK.h"
#include "EpiGraphicsDriverVK/gfxBufferImplVK.h"
#include "EpiGraphicsDriverVK/gfxDeviceMemoryImplVK.h"
#include "EpiGraphicsDriverVK/gfxDescriptorPoolImplVK.h"
#include "EpiGraphicsDriverVK/gfxDescriptorSetLayoutImplVK.h"
#include "EpiGraphicsDriverVK/gfxDescriptorSetImplVK.h"

#include "EpiGraphicsDriverVK/Synchronization/gfxSemaphoreImplVK.h"
#include "EpiGraphicsDriverVK/Synchronization/gfxFenceImplVK.h"

#include "EpiGraphicsDriverCommon/gfxSurface.h"

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

gfxDeviceImplVK::gfxDeviceImplVK(const gfxPhysicalDeviceImplVK& physicalDevice)
    : m_PhysicalDevice{physicalDevice}
{
}

epiBool gfxDeviceImplVK::Init(gfxQueueDescriptorList& queueDescriptorList,
                              const epiArray<gfxPhysicalDeviceExtension>& extensionsRequired,
                              const epiArray<gfxPhysicalDeviceFeature>& featuresRequired)
{
    epiBool isSuitable = std::all_of(queueDescriptorList.begin(),
                                     queueDescriptorList.end(),
                                     [this](const gfxQueueDescriptor& queueDescriptor)
    {
        return m_PhysicalDevice.IsQueueTypeSupported(queueDescriptor.GetTypeMask());
    });
    isSuitable = isSuitable && std::all_of(extensionsRequired.begin(), extensionsRequired.end(), [this](gfxPhysicalDeviceExtension extension) {
        return m_PhysicalDevice.IsExtensionSupported(extension);
    });
    isSuitable = isSuitable && std::all_of(featuresRequired.begin(), featuresRequired.end(), [this](gfxPhysicalDeviceFeature feature)
    {
        return m_PhysicalDevice.IsFeatureSupported(feature);
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
        for (const gfxQueueFamilyDescriptorImplVK& queueFamilyDesc : m_PhysicalDevice.GetQueueFamilyDescriptors())
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
                                                                        [this, &queueFamilyDesc](const gfxSurfaceImpl* surfaceTarget)
                {
                    return surfaceTarget != nullptr && surfaceTarget->IsPresentSupportedFor(m_PhysicalDevice, queueFamilyDesc);
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
        if (!m_PhysicalDevice.IsExtensionSupported(extension))
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
#if EPI_NVIDIA_NSIGHT_AFTERMATH
    // NOTE: can't be used with a RenderDoc together
    // extensions.push_back(VK_NV_DEVICE_DIAGNOSTICS_CONFIG_EXTENSION_NAME);
    // extensions.push_back(VK_NV_DEVICE_DIAGNOSTIC_CHECKPOINTS_EXTENSION_NAME);

    VkDeviceDiagnosticsConfigCreateInfoNV diagnosticsConfigCreateInfoNV{};
    diagnosticsConfigCreateInfoNV.sType = VK_STRUCTURE_TYPE_DEVICE_DIAGNOSTICS_CONFIG_CREATE_INFO_NV;
    diagnosticsConfigCreateInfoNV.pNext = deviceCreateInfoNext;
    deviceCreateInfoNext = &diagnosticsConfigCreateInfoNV;
    diagnosticsConfigCreateInfoNV.flags = VK_DEVICE_DIAGNOSTICS_CONFIG_ENABLE_SHADER_DEBUG_INFO_BIT_NV |
                                          VK_DEVICE_DIAGNOSTICS_CONFIG_ENABLE_RESOURCE_TRACKING_BIT_NV |
                                          VK_DEVICE_DIAGNOSTICS_CONFIG_ENABLE_AUTOMATIC_CHECKPOINTS_BIT_NV;
#endif // EPI_NVIDIA_NSIGHT_AFTERMATH

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
        if (!m_PhysicalDevice.IsFeatureSupported(feature))
        {
            // TODO: get string representation
            epiLogError("Required Vulkan device feature=`{}` is not supported!", feature);
            return false;
        }

        *kFeatures[static_cast<epiU32>(feature)] = true;
        m_FeatureEnabled[static_cast<epiU32>(feature)] = true;
    }

    createInfo.pNext = deviceCreateInfoNext;

    if (const VkResult result = vkCreateDevice(m_PhysicalDevice.GetVkPhysicalDevice(), &createInfo, nullptr, &m_VkDevice); result != VK_SUCCESS)
    {
        gfxLogErrorEx(result, "Failed to call vkCreateDevice!");
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

epiBool gfxDeviceImplVK::UpdateDescriptorSets(const epiArray<gfxDescriptorSetWrite>& writes, const epiArray<gfxDescriptorSetCopy>& copies) const
{
    auto transformImageInfos = [](const gfxDescriptorSetWrite& write) -> std::vector<VkDescriptorImageInfo>
    {
        std::vector<VkDescriptorImageInfo> imageInfos;
        imageInfos.reserve(write.GetImageInfos().Size());

        std::transform(write.GetImageInfos().begin(),
                       write.GetImageInfos().end(),
                       std::back_inserter(imageInfos),
                       [](const gfxDescriptorImageInfo& imageInfo)
        {
            // TODO: implement
            VkDescriptorImageInfo imageInfoVk{};
            return imageInfoVk;
        });

        return imageInfos;
    };

    auto transformBufferInfos = [](const gfxDescriptorSetWrite& write) -> std::vector<VkDescriptorBufferInfo>
    {
        std::vector<VkDescriptorBufferInfo> bufferInfos;
        bufferInfos.reserve(write.GetBufferInfos().Size());

        std::transform(write.GetBufferInfos().begin(),
                       write.GetBufferInfos().end(),
                       std::back_inserter(bufferInfos),
                       [](const gfxDescriptorBufferInfo& bufferInfo)
        {
            const gfxBufferImplVK* buffer = static_cast<const gfxBufferImplVK*>(gfxBufferImpl::ExtractImpl(bufferInfo.GetBuffer()));
            epiAssert(buffer != nullptr);

            VkDescriptorBufferInfo bufferInfoVk{};
            bufferInfoVk.buffer = buffer->GetVkBuffer();
            bufferInfoVk.offset = bufferInfo.GetOffset();
            bufferInfoVk.range = bufferInfo.GetRange();

            return bufferInfoVk;
        });

        return bufferInfos;
    };

    auto transformBufferViewInfos = [](const gfxDescriptorSetWrite& write) -> std::vector<VkBufferView>
    {
        // TODO: implement
        std::vector<VkBufferView> bufferViewInfos;
        return bufferViewInfos;
    };

    const epiBool writesAreValid = std::all_of(writes.begin(), writes.end(), [](const gfxDescriptorSetWrite& write)
    {
        // NOTE: should be provided either image infos or buffer infos or buffer view infos
        const epiBool isValid = (gfxDescriptorSetImpl::ExtractImpl(write.GetDstSet()) != nullptr) &&
                                ((write.GetImageInfos().Size() ^ write.GetBufferInfos().Size()) /* TODO: ^ write.GetBufferViewInfos() */);
        if (!isValid)
        {
            return false;
        }

        // TODO: validate image infos
        // TODO: validate buffer view infos

        const epiBool isBufferInfosValid = write.GetBufferInfos().IsEmpty() || std::all_of(write.GetBufferInfos().begin(),
                                                                                           write.GetBufferInfos().end(),
                                                                                           [](const gfxDescriptorBufferInfo& bufferInfo)
        {
            return gfxBufferImpl::ExtractImpl(bufferInfo.GetBuffer()) != nullptr;
        });

        if (!isBufferInfosValid)
        {
            return false;
        }

        return true;
    });

    if (!writesAreValid)
    {
        epiLogError("Failed to Update Descriptor Sets! Some of the provided DescriptorSetWrite is invalid!");
        return false;
    }

    const epiBool copiesAreValid = std::all_of(copies.begin(), copies.end(), [](const gfxDescriptorSetCopy& copy)
    {
        return gfxDescriptorSetImpl::ExtractImpl(copy.GetSrcSet()) != nullptr && gfxDescriptorSetImpl::ExtractImpl(copy.GetDstSet()) != nullptr;
    });

    if (!copiesAreValid)
    {
        epiLogError("Failed to Update Descriptor Sets! Some of the provided DescriptorSetCopy is invalid!");
        return false;
    }

    std::vector<VkWriteDescriptorSet> writesVk;
    writesVk.reserve(writes.Size());

    std::vector<std::vector<VkDescriptorImageInfo>> writesImageInfosVk;
    writesImageInfosVk.reserve(writes.Size());

    std::vector<std::vector<VkDescriptorBufferInfo>> writesBufferInfosVk;
    writesBufferInfosVk.reserve(writes.Size());

    std::vector<std::vector<VkBufferView>> writesBufferViewInfosVk;
    writesBufferViewInfosVk.reserve(writes.Size());

    std::transform(writes.begin(),
                   writes.end(),
                   std::back_inserter(writesVk),
                   [&writesImageInfosVk,
                    &writesBufferInfosVk,
                    &writesBufferViewInfosVk,
                    &transformImageInfos,
                    &transformBufferInfos,
                    &transformBufferViewInfos](const gfxDescriptorSetWrite& write)
    {
        const gfxDescriptorSetImplVK* set = static_cast<const gfxDescriptorSetImplVK*>(gfxDescriptorSetImpl::ExtractImpl(write.GetDstSet()));
        epiAssert(set != nullptr);

        std::vector<VkDescriptorImageInfo>& imageInfos = writesImageInfosVk.emplace_back(std::move(transformImageInfos(write)));
        std::vector<VkDescriptorBufferInfo>& bufferInfos = writesBufferInfosVk.emplace_back(std::move(transformBufferInfos(write)));
        std::vector<VkBufferView>& bufferViewInfos = writesBufferViewInfosVk.emplace_back(std::move(transformBufferViewInfos(write)));

        VkWriteDescriptorSet writeVk{};
        writeVk.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        writeVk.dstSet = set->GetVkDescriptorSet();
        writeVk.dstBinding = write.GetDstBinding();
        writeVk.dstArrayElement = write.GetDstArrayElement();
        writeVk.descriptorCount = write.GetDescriptorCount();
        writeVk.descriptorType = gfxDescriptorTypeTo(write.GetDescriptorType());
        writeVk.pImageInfo = !imageInfos.empty() ? imageInfos.data() : nullptr;
        writeVk.pBufferInfo = !bufferInfos.empty() ? bufferInfos.data() : nullptr;
        writeVk.pTexelBufferView = !bufferViewInfos.empty() ? bufferViewInfos.data() : nullptr;

        return writeVk;
    });

    std::vector<VkCopyDescriptorSet> copiesVk;
    copiesVk.reserve(copies.Size());

    std::transform(copies.begin(),
                   copies.end(),
                   std::back_inserter(copiesVk),
                   [](const gfxDescriptorSetCopy& copy)
    {
        const gfxDescriptorSetImplVK* srcSet = static_cast<const gfxDescriptorSetImplVK*>(gfxDescriptorSetImpl::ExtractImpl(copy.GetSrcSet()));
        epiAssert(srcSet != nullptr);

        const gfxDescriptorSetImplVK* dstSet = static_cast<const gfxDescriptorSetImplVK*>(gfxDescriptorSetImpl::ExtractImpl(copy.GetDstSet()));
        epiAssert(dstSet != nullptr);

        VkCopyDescriptorSet copyVk{};
        copyVk.sType = VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET;
        copyVk.srcSet = srcSet->GetVkDescriptorSet();
        copyVk.srcBinding = copy.GetSrcBinding();
        copyVk.srcArrayElement = copy.GetSrcArrayElement();
        copyVk.dstSet = dstSet->GetVkDescriptorSet();
        copyVk.dstBinding = copy.GetDstBinding();
        copyVk.dstArrayElement = copy.GetDstArrayElement();
        copyVk.descriptorCount = copy.GetDescriptorCount();

        return copyVk;
    });

    vkUpdateDescriptorSets(m_VkDevice, writesVk.size(), writesVk.data(), copiesVk.size(), copiesVk.data());
}

std::shared_ptr<gfxSwapChainImpl> gfxDeviceImplVK::CreateSwapChain(const gfxSwapChainCreateInfo& info,
                                                                   const gfxSurfaceImpl& surfaceImpl,
                                                                   const gfxQueueFamilyImpl& queueFamilyImpl,
                                                                   const gfxRenderPassImpl& renderPassImpl) const
{
    std::shared_ptr<gfxSwapChainImplVK> impl = std::make_shared<gfxSwapChainImplVK>(*this);
    if (!impl->Init(info, surfaceImpl, queueFamilyImpl, renderPassImpl))
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

std::shared_ptr<gfxPipelineLayoutImpl> gfxDeviceImplVK::CreatePipelineLayout(const gfxPipelineLayoutCreateInfo& info) const
{
    std::shared_ptr<gfxPipelineLayoutImplVK> impl = std::make_shared<gfxPipelineLayoutImplVK>(m_VkDevice);
    if (!impl->Init(info))
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
    if (!impl->Init(info,
                    static_cast<const gfxShaderProgramImplVK&>(shaderProgramImpl),
                    static_cast<const gfxRenderPassImplVK&>(renderPassImpl)))
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

std::shared_ptr<gfxFrameBufferImpl> gfxDeviceImplVK::CreateFrameBuffer(const gfxFrameBufferCreateInfo& info, const gfxRenderPassImpl& renderPassImpl, const epiPtrArray<const gfxTextureViewImpl>& textureViewImpls) const
{
    std::shared_ptr<gfxFrameBufferImplVK> impl = std::make_shared<gfxFrameBufferImplVK>(m_VkDevice);
    if (!impl->Init(info, renderPassImpl, textureViewImpls))
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

std::shared_ptr<gfxSamplerImpl> gfxDeviceImplVK::CreateSampler(const gfxSamplerCreateInfo& info) const
{
    std::shared_ptr<gfxSamplerImplVK> impl = std::make_shared<gfxSamplerImplVK>(m_VkDevice);
    if (!impl->Init(info))
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

std::shared_ptr<gfxBufferImpl> gfxDeviceImplVK::CreateBuffer(const gfxBufferCreateInfo& info) const
{
    std::shared_ptr<gfxBufferImplVK> impl = std::make_shared<gfxBufferImplVK>(m_VkDevice);
    if (!impl->Init(info))
    {
        impl.reset();
    }

    return impl;
}

std::shared_ptr<gfxDeviceMemoryImpl> gfxDeviceImplVK::CreateDeviceMemory(const gfxDeviceMemoryBufferCreateInfo& info, const gfxBufferImpl& bufferImpl) const
{
    std::shared_ptr<gfxDeviceMemoryImplVK> impl = std::make_shared<gfxDeviceMemoryImplVK>(m_VkDevice);
    if (!impl->Init(info, m_PhysicalDevice, static_cast<const gfxBufferImplVK&>(bufferImpl)))
    {
        impl.reset();
    }

    return impl;
}

std::shared_ptr<gfxDeviceMemoryImpl> gfxDeviceImplVK::CreateDeviceMemory(const gfxDeviceMemoryImageCreateInfo& info) const
{
    std::shared_ptr<gfxDeviceMemoryImplVK> impl = std::make_shared<gfxDeviceMemoryImplVK>(m_VkDevice);
    if (!impl->Init(info, m_PhysicalDevice))
    {
        impl.reset();
    }

    return impl;
}

std::shared_ptr<gfxDescriptorSetLayoutImpl> gfxDeviceImplVK::CreateDescriptorSetLayout(const gfxDescriptorSetLayoutCreateInfo& info) const
{
    std::shared_ptr<gfxDescriptorSetLayoutImplVK> impl = std::make_shared<gfxDescriptorSetLayoutImplVK>(m_VkDevice);
    if (!impl->Init(info))
    {
        impl.reset();
    }

    return impl;
}

std::shared_ptr<gfxDescriptorPoolImpl> gfxDeviceImplVK::CreateDescriptorPool(const gfxDescriptorPoolCreateInfo& info, const epiPtrArray<const gfxDescriptorSetLayoutImpl>& layoutsImpls) const
{
    epiPtrArray<const gfxDescriptorSetLayoutImplVK> layoutsImplsVk;
    layoutsImplsVk.Reserve(layoutsImpls.Size());

    std::transform(layoutsImpls.begin(), layoutsImpls.end(), std::back_inserter(layoutsImplsVk), [](const gfxDescriptorSetLayoutImpl* layoutImpl)
    {
        return static_cast<const gfxDescriptorSetLayoutImplVK*>(layoutImpl);
    });

    std::shared_ptr<gfxDescriptorPoolImplVK> impl = std::make_shared<gfxDescriptorPoolImplVK>(m_VkDevice);
    if (!impl->Init(info, layoutsImplsVk))
    {
        impl.reset();
    }

    return impl;
}

std::shared_ptr<gfxSemaphoreImpl> gfxDeviceImplVK::CreateSemaphoreFrom(const gfxSemaphoreCreateInfo& info) const
{
    std::shared_ptr<gfxSemaphoreImplVK> impl = std::make_shared<gfxSemaphoreImplVK>(m_VkDevice);
    if (!impl->Init(info))
    {
        impl.reset();
    }

    return impl;
}

std::shared_ptr<gfxFenceImpl> gfxDeviceImplVK::CreateFence(const gfxFenceCreateInfo& info) const
{
    std::shared_ptr<gfxFenceImplVK> impl = std::make_shared<gfxFenceImplVK>(m_VkDevice);
    if (!impl->Init(info))
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
