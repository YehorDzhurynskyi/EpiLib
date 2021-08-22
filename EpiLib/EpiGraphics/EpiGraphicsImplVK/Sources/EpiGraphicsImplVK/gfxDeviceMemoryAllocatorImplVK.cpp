#include "EpiGraphicsImplVK/gfxDeviceMemoryAllocatorImplVK.h"

#include "EpiGraphicsImplVK/gfxErrorVK.h"
#include "EpiGraphicsImplVK/gfxDeviceImplVK.h"
#include "EpiGraphicsImplVK/gfxInstanceImplVK.h"

#define VMA_IMPLEMENTATION
#include "vk_mem_alloc.h"

namespace
{

EPI_NAMESPACE_USING()

VmaAllocatorCreateFlagBits gfxDeviceMemoryAllocatorCreateMaskTo(gfxDeviceMemoryAllocatorCreateMask mask)
{
    return epiMask((mask & gfxDeviceMemoryAllocatorCreateMask_ExternallySynchronized) ? VMA_ALLOCATOR_CREATE_EXTERNALLY_SYNCHRONIZED_BIT : VmaAllocatorCreateFlagBits{});
}

} // namespace

EPI_NAMESPACE_BEGIN()

gfxDeviceMemoryAllocatorImplVK::gfxDeviceMemoryAllocatorImplVK(const gfxDevice& device)
    : gfxDeviceMemoryAllocator::Impl{device}
{
}

gfxDeviceMemoryAllocatorImplVK::~gfxDeviceMemoryAllocatorImplVK()
{
    vmaDestroyAllocator(m_VmaAllocator);
}

epiBool gfxDeviceMemoryAllocatorImplVK::Init(const gfxDeviceMemoryAllocatorCreateInfo& info)
{
    const std::shared_ptr<gfxInstanceImplVK> instance = ImplOf<gfxInstanceImplVK>(m_Device.GetPhysicalDevice().GetInstance());
    const std::shared_ptr<gfxPhysicalDeviceImplVK> physicalDevice = ImplOf<gfxPhysicalDeviceImplVK>(m_Device.GetPhysicalDevice());
    const std::shared_ptr<gfxDeviceImplVK> device = ImplOf<gfxDeviceImplVK>(m_Device);

    VmaAllocatorCreateInfo allocatorInfo = {};
    allocatorInfo.vulkanApiVersion = instance->GetVkAPIVersion();
    allocatorInfo.instance = instance->GetVkInstance();
    allocatorInfo.physicalDevice = physicalDevice->GetVkPhysicalDevice();
    allocatorInfo.device = device->GetVkDevice();
    allocatorInfo.frameInUseCount = info.GetFrameInUseCount();
    allocatorInfo.preferredLargeHeapBlockSize = info.GetPreferredLargeHeapBlockSize();

    allocatorInfo.flags = gfxDeviceMemoryAllocatorCreateMaskTo(info.GetCreateMask());
    allocatorInfo.flags |= device->IsExtensionEnabled(gfxPhysicalDeviceExtension::GetMemoryRequirements2) &&
                           device->IsExtensionEnabled(gfxPhysicalDeviceExtension::DedicatedAllocation) ?
                           VMA_ALLOCATOR_CREATE_KHR_DEDICATED_ALLOCATION_BIT :
                           VmaAllocatorCreateFlagBits{};
    allocatorInfo.flags |= device->IsExtensionEnabled(gfxPhysicalDeviceExtension::BindMemory2) ?
                           VMA_ALLOCATOR_CREATE_KHR_BIND_MEMORY2_BIT :
                           VmaAllocatorCreateFlagBits{};
    allocatorInfo.flags |= instance->IsExtensionEnabled(gfxInstanceExtension::GetPhysicalDeviceProperties2) &&
                           device->IsExtensionEnabled(gfxPhysicalDeviceExtension::MemoryBudget) ?
                           VMA_ALLOCATOR_CREATE_EXT_MEMORY_BUDGET_BIT :
                           VmaAllocatorCreateFlagBits{};
    allocatorInfo.flags |= /* TODO: device->IsFeatureEnabled(gfxPhysicalDeviceFeature::DeviceCoherentMemory) &&*/
                           device->IsExtensionEnabled(gfxPhysicalDeviceExtension::AMDDeviceCoherentMemory) ?
                           VMA_ALLOCATOR_CREATE_AMD_DEVICE_COHERENT_MEMORY_BIT :
                           VmaAllocatorCreateFlagBits{};
    allocatorInfo.flags |= device->IsFeatureEnabled(gfxPhysicalDeviceFeature::BufferDeviceAddress) &&
                           device->IsExtensionEnabled(gfxPhysicalDeviceExtension::BufferDeviceAddress) ?
                           VMA_ALLOCATOR_CREATE_BUFFER_DEVICE_ADDRESS_BIT :
                           VmaAllocatorCreateFlagBits{};
    allocatorInfo.flags |= device->IsExtensionEnabled(gfxPhysicalDeviceExtension::MemoryPriority) ?
                           VMA_ALLOCATOR_CREATE_EXT_MEMORY_PRIORITY_BIT :
                           VmaAllocatorCreateFlagBits{};

    if (const VkResult result = vmaCreateAllocator(&allocatorInfo, &m_VmaAllocator); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vmaCreateAllocator!");
        return false;
    }

    return true;
}

EPI_NAMESPACE_END()
