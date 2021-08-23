#include "EpiGraphicsImplVK/gfxDeviceMemoryAllocatorImplVK.h"

#include "EpiGraphicsImplVK/gfxErrorVK.h"
#include "EpiGraphicsImplVK/gfxEnumVK.h"
#include "EpiGraphicsImplVK/gfxDeviceImplVK.h"
#include "EpiGraphicsImplVK/gfxInstanceImplVK.h"
#include "EpiGraphicsImplVK/gfxBufferImplVK.h"
#include "EpiGraphicsImplVK/gfxImageImplVK.h"

#define VMA_IMPLEMENTATION
#include "vk_mem_alloc.h"

namespace
{

EPI_NAMESPACE_USING()

VmaAllocatorCreateFlagBits gfxDeviceMemoryAllocatorCreateMaskTo(gfxDeviceMemoryAllocatorCreateMask mask)
{
    return epiMask((mask & gfxDeviceMemoryAllocatorCreateMask_ExternallySynchronized) ? VMA_ALLOCATOR_CREATE_EXTERNALLY_SYNCHRONIZED_BIT : VmaAllocatorCreateFlagBits{});
}

VmaAllocationCreateFlagBits gfxDeviceMemoryAllocationCreateMaskTo(gfxDeviceMemoryAllocationCreateMask mask)
{
    return epiMask((mask & gfxDeviceMemoryAllocationCreateMask_DedicatedMemory) ? VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT : VmaAllocationCreateFlagBits{},
                   (mask & gfxDeviceMemoryAllocationCreateMask_NeverAllocate) ? VMA_ALLOCATION_CREATE_NEVER_ALLOCATE_BIT : VmaAllocationCreateFlagBits{},
                   (mask & gfxDeviceMemoryAllocationCreateMask_Mapped) ? VMA_ALLOCATION_CREATE_MAPPED_BIT : VmaAllocationCreateFlagBits{},
                   (mask & gfxDeviceMemoryAllocationCreateMask_CanBecomeLost) ? VMA_ALLOCATION_CREATE_CAN_BECOME_LOST_BIT : VmaAllocationCreateFlagBits{},
                   (mask & gfxDeviceMemoryAllocationCreateMask_CanMakeOtherLost) ? VMA_ALLOCATION_CREATE_CAN_MAKE_OTHER_LOST_BIT : VmaAllocationCreateFlagBits{},
                   (mask & gfxDeviceMemoryAllocationCreateMask_UserDataCopyString) ? VMA_ALLOCATION_CREATE_USER_DATA_COPY_STRING_BIT : VmaAllocationCreateFlagBits{},
                   (mask & gfxDeviceMemoryAllocationCreateMask_UpperAddress) ? VMA_ALLOCATION_CREATE_UPPER_ADDRESS_BIT : VmaAllocationCreateFlagBits{},
                   (mask & gfxDeviceMemoryAllocationCreateMask_DontBind) ? VMA_ALLOCATION_CREATE_DONT_BIND_BIT : VmaAllocationCreateFlagBits{},
                   (mask & gfxDeviceMemoryAllocationCreateMask_WithinBudget) ? VMA_ALLOCATION_CREATE_WITHIN_BUDGET_BIT : VmaAllocationCreateFlagBits{},
                   (mask & gfxDeviceMemoryAllocationCreateMask_StrategyBestFit) ? VMA_ALLOCATION_CREATE_STRATEGY_BEST_FIT_BIT : VmaAllocationCreateFlagBits{},
                   (mask & gfxDeviceMemoryAllocationCreateMask_StrategyWorstFit) ? VMA_ALLOCATION_CREATE_STRATEGY_WORST_FIT_BIT : VmaAllocationCreateFlagBits{},
                   (mask & gfxDeviceMemoryAllocationCreateMask_StrategyFirstFit) ? VMA_ALLOCATION_CREATE_STRATEGY_FIRST_FIT_BIT : VmaAllocationCreateFlagBits{},
                   (mask & gfxDeviceMemoryAllocationCreateMask_StrategyMinMemory) ? VMA_ALLOCATION_CREATE_STRATEGY_MIN_MEMORY_BIT : VmaAllocationCreateFlagBits{},
                   (mask & gfxDeviceMemoryAllocationCreateMask_StrategyMinTime) ? VMA_ALLOCATION_CREATE_STRATEGY_MIN_TIME_BIT : VmaAllocationCreateFlagBits{},
                   (mask & gfxDeviceMemoryAllocationCreateMask_StrategyMinFragmentation) ? VMA_ALLOCATION_CREATE_STRATEGY_MIN_FRAGMENTATION_BIT : VmaAllocationCreateFlagBits{});
}

VmaMemoryUsage gfxDeviceMemoryAllocationUsageTo(gfxDeviceMemoryAllocationUsage usage)
{
    switch (usage)
    {
    case gfxDeviceMemoryAllocationUsage::Unknown: return VMA_MEMORY_USAGE_UNKNOWN;
    case gfxDeviceMemoryAllocationUsage::GpuOnly: return VMA_MEMORY_USAGE_GPU_ONLY;
    case gfxDeviceMemoryAllocationUsage::CpuOnly: return VMA_MEMORY_USAGE_CPU_ONLY;
    case gfxDeviceMemoryAllocationUsage::CpuToGpu: return VMA_MEMORY_USAGE_CPU_TO_GPU;
    case gfxDeviceMemoryAllocationUsage::GpuToCpu: return VMA_MEMORY_USAGE_GPU_TO_CPU;
    case gfxDeviceMemoryAllocationUsage::CpuCopy: return VMA_MEMORY_USAGE_CPU_COPY;
    case gfxDeviceMemoryAllocationUsage::GpuLazilyAllocated: return VMA_MEMORY_USAGE_GPU_LAZILY_ALLOCATED;
    default: epiLogError("Unhandled gfxDeviceMemoryAllocationUsage=`{}`", usage); return VMA_MEMORY_USAGE_MAX_ENUM; // TODO: use str repr of enum
    }
}

} // namespace

EPI_NAMESPACE_BEGIN()

gfxDeviceMemoryAllocationImplVK::gfxDeviceMemoryAllocationImplVK(const gfxDeviceMemoryAllocator& allocator)
    : gfxDeviceMemoryAllocation::Impl{allocator}
{
}

gfxDeviceMemoryAllocationImplVK::~gfxDeviceMemoryAllocationImplVK()
{
    const std::shared_ptr<gfxDeviceMemoryAllocatorImplVK> allocatorImpl = ImplOf<gfxDeviceMemoryAllocatorImplVK>(m_Allocator);

    vmaFreeMemory(allocatorImpl->GetVmaAllocator(), m_VmaAllocation);
}

std::optional<gfxBuffer> gfxDeviceMemoryAllocationImplVK::InitForCreatedBuffer(const gfxDeviceMemoryAllocationCreateInfo& info,
                                                                               const gfxBufferCreateInfo& bufferInfo)
{
    const std::shared_ptr<gfxDeviceMemoryAllocatorImplVK> allocatorImpl = ImplOf<gfxDeviceMemoryAllocatorImplVK>(m_Allocator);

    VmaAllocationCreateInfo createInfo{};
    createInfo.flags = gfxDeviceMemoryAllocationCreateMaskTo(info.GetCreateMask());
    createInfo.usage = gfxDeviceMemoryAllocationUsageTo(info.GetUsage());
    createInfo.requiredFlags = gfxDeviceMemoryPropertyMaskTo(info.GetRequiredPropertiesMask());
    createInfo.preferredFlags = gfxDeviceMemoryPropertyMaskTo(info.GetPreferredPropertiesMask());
    createInfo.priority = info.GetPriority();
    // TODO: set other properties

    VkBufferCreateInfo bufferCreateInfo{};

    VkBuffer bufferVk{nullptr};
    if (const VkResult result = vmaCreateBuffer(allocatorImpl->GetVmaAllocator(),
                                                &bufferCreateInfo,
                                                &createInfo,
                                                &bufferVk,
                                                &m_VmaAllocation,
                                                nullptr); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vmaCreateBuffer!");
        return std::nullopt;
    }

    return std::nullopt;
}

std::optional<gfxImage> gfxDeviceMemoryAllocationImplVK::InitForCreatedImage(const gfxDeviceMemoryAllocationCreateInfo& info,
                                                                             const gfxImageCreateInfo& imageInfo)
{
    return std::nullopt;
}

epiBool gfxDeviceMemoryAllocationImplVK::InitForAllocatedBuffer(const gfxDeviceMemoryAllocationCreateInfo& info,
                                                                const gfxBuffer& buffer)
{
    const std::shared_ptr<gfxDeviceMemoryAllocatorImplVK> allocatorImpl = ImplOf<gfxDeviceMemoryAllocatorImplVK>(m_Allocator);
    const std::shared_ptr<gfxBufferImplVK> bufferImpl = ImplOf<gfxBufferImplVK>(buffer);

    VmaAllocationCreateInfo createInfo{};
    createInfo.flags = gfxDeviceMemoryAllocationCreateMaskTo(info.GetCreateMask());
    createInfo.usage = gfxDeviceMemoryAllocationUsageTo(info.GetUsage());
    createInfo.requiredFlags = gfxDeviceMemoryPropertyMaskTo(info.GetRequiredPropertiesMask());
    createInfo.preferredFlags = gfxDeviceMemoryPropertyMaskTo(info.GetPreferredPropertiesMask());
    createInfo.priority = info.GetPriority();
    // TODO: set other properties

    if (const VkResult result = vmaAllocateMemoryForBuffer(allocatorImpl->GetVmaAllocator(), bufferImpl->GetVkBuffer(), &createInfo, &m_VmaAllocation, nullptr); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vmaAllocateMemoryForBuffer!");
        return false;
    }

    if (const VkResult result = vmaBindBufferMemory(allocatorImpl->GetVmaAllocator(), m_VmaAllocation, bufferImpl->GetVkBuffer()); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vmaBindBufferMemory!");
        return false;
    }

    return true;
}

epiBool gfxDeviceMemoryAllocationImplVK::InitForAllocatedImage(const gfxDeviceMemoryAllocationCreateInfo& info,
                                                               const gfxImage& image)
{
    const std::shared_ptr<gfxDeviceMemoryAllocatorImplVK> allocatorImpl = ImplOf<gfxDeviceMemoryAllocatorImplVK>(m_Allocator);
    const std::shared_ptr<gfxImageImplVK> imageImpl = ImplOf<gfxImageImplVK>(image);

    VmaAllocationCreateInfo createInfo{};
    createInfo.flags = gfxDeviceMemoryAllocationCreateMaskTo(info.GetCreateMask());
    createInfo.usage = gfxDeviceMemoryAllocationUsageTo(info.GetUsage());
    createInfo.requiredFlags = gfxDeviceMemoryPropertyMaskTo(info.GetRequiredPropertiesMask());
    createInfo.preferredFlags = gfxDeviceMemoryPropertyMaskTo(info.GetPreferredPropertiesMask());
    createInfo.priority = info.GetPriority();
    // TODO: set other properties

    if (const VkResult result = vmaAllocateMemoryForImage(allocatorImpl->GetVmaAllocator(), imageImpl->GetVkImage(), &createInfo, &m_VmaAllocation, nullptr); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vmaAllocateMemoryForImage!");
        return false;
    }

    if (const VkResult result = vmaBindImageMemory(allocatorImpl->GetVmaAllocator(), m_VmaAllocation, imageImpl->GetVkImage()); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vmaBindImageMemory!");
        return false;
    }

    return true;
}

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
    // TODO: record allocations on cmd parameter set

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

std::optional<gfxDeviceMemoryAllocationBuffer> gfxDeviceMemoryAllocatorImplVK::CreateBuffer(const gfxDeviceMemoryAllocationCreateInfo& allocationInfo,
                                                                                            const gfxBufferCreateInfo& bufferInfo)
{
    gfxDeviceMemoryAllocator allocator(shared_from_this());

    std::shared_ptr<gfxDeviceMemoryAllocationImplVK> impl = std::make_shared<gfxDeviceMemoryAllocationImplVK>(allocator);

    std::optional<gfxBuffer> buffer = impl->InitForCreatedBuffer(allocationInfo, bufferInfo);
    if (!buffer.has_value())
    {
        epiLogError("Failed to create Buffer!");
        return std::nullopt;
    }

    return gfxDeviceMemoryAllocationBuffer(impl, std::move(*buffer));
}

std::optional<gfxDeviceMemoryAllocationImage> gfxDeviceMemoryAllocatorImplVK::CreateImage(const gfxDeviceMemoryAllocationCreateInfo& allocationInfo,
                                                                                          const gfxImageCreateInfo& imageInfo)
{
    gfxDeviceMemoryAllocator allocator(shared_from_this());

    std::shared_ptr<gfxDeviceMemoryAllocationImplVK> impl = std::make_shared<gfxDeviceMemoryAllocationImplVK>(allocator);

    std::optional<gfxImage> image = impl->InitForCreatedImage(allocationInfo, imageInfo);
    if (!image.has_value())
    {
        epiLogError("Failed to create Image!");
        return std::nullopt;
    }

    return gfxDeviceMemoryAllocationImage(impl, std::move(*image));
}

std::optional<gfxDeviceMemoryAllocation> gfxDeviceMemoryAllocatorImplVK::AllocateBuffer(const gfxDeviceMemoryAllocationCreateInfo& info,
                                                                                        const gfxBuffer& buffer)
{
    gfxDeviceMemoryAllocator allocator(shared_from_this());

    std::shared_ptr<gfxDeviceMemoryAllocationImplVK> impl = std::make_shared<gfxDeviceMemoryAllocationImplVK>(allocator);
    if (!impl->InitForAllocatedBuffer(info, buffer))
    {
        epiLogError("Failed to allocate Buffer!");
        return std::nullopt;
    }

    return gfxDeviceMemoryAllocation(impl);
}

std::optional<gfxDeviceMemoryAllocation> gfxDeviceMemoryAllocatorImplVK::AllocateImage(const gfxDeviceMemoryAllocationCreateInfo& info,
                                                                                       const gfxImage& image)
{
    gfxDeviceMemoryAllocator allocator(shared_from_this());

    std::shared_ptr<gfxDeviceMemoryAllocationImplVK> impl = std::make_shared<gfxDeviceMemoryAllocationImplVK>(allocator);
    if (!impl->InitForAllocatedImage(info, image))
    {
        epiLogError("Failed to allocate Image!");
        return std::nullopt;
    }

    return gfxDeviceMemoryAllocation(impl);
}

VmaAllocator gfxDeviceMemoryAllocatorImplVK::GetVmaAllocator() const
{
    return m_VmaAllocator;
}

EPI_NAMESPACE_END()
