#include "EpiGraphicsImplVK/gfxDeviceMemoryAllocatorImplVK.h"

#include "EpiGraphicsImplVK/gfxErrorVK.h"
#include "EpiGraphicsImplVK/gfxEnumVK.h"
#include "EpiGraphicsImplVK/gfxDeviceImplVK.h"
#include "EpiGraphicsImplVK/gfxInstanceImplVK.h"
#include "EpiGraphicsImplVK/gfxBufferImplVK.h"
#include "EpiGraphicsImplVK/gfxImageImplVK.h"
#include "EpiGraphicsImplVK/gfxQueueFamilyImplVK.h"

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

std::optional<gfxBuffer> gfxDeviceMemoryAllocationImplVK::InitBuffer(const gfxDeviceMemoryAllocationCreateInfo& info,
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
    bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferCreateInfo.flags = gfxBufferCreateMaskTo(bufferInfo.GetCreateMask());
    bufferCreateInfo.size = bufferInfo.GetSize();
    bufferCreateInfo.usage = gfxBufferUsageMaskTo(bufferInfo.GetUsageMask());
    bufferCreateInfo.sharingMode = gfxSharingModeTo(bufferInfo.GetSharingMode());

    std::vector<epiU32> queueFamilyIndices;
    if (bufferInfo.GetSharingMode() == gfxSharingMode::Concurrent)
    {
        queueFamilyIndices.reserve(bufferInfo.GetQueueFamilies().Size());

        std::transform(bufferInfo.GetQueueFamilies().begin(),
                       bufferInfo.GetQueueFamilies().end(),
                       std::back_inserter(queueFamilyIndices),
                       [](const gfxQueueFamily& family)
        {
            const std::shared_ptr<gfxQueueFamilyImplVK> familyImpl = ImplOf<gfxQueueFamilyImplVK>(family);
            return familyImpl->GetIndex();
        });

        bufferCreateInfo.queueFamilyIndexCount = queueFamilyIndices.size();
        bufferCreateInfo.pQueueFamilyIndices = queueFamilyIndices.data();
    }

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

    const std::shared_ptr<gfxBufferImplVK> bufferImpl = std::make_shared<gfxBufferImplVK>(m_Allocator.GetDevice());
    if (!bufferImpl->Init(bufferVk))
    {
        epiLogError("Failed to init Buffer!");
        return std::nullopt;
    }

    return gfxBuffer(bufferImpl);
}

std::optional<gfxImage> gfxDeviceMemoryAllocationImplVK::InitImage(const gfxDeviceMemoryAllocationCreateInfo& info,
                                                                   const gfxImageCreateInfo& imageInfo)
{
    const std::shared_ptr<gfxDeviceMemoryAllocatorImplVK> allocatorImpl = ImplOf<gfxDeviceMemoryAllocatorImplVK>(m_Allocator);

    VmaAllocationCreateInfo createInfo{};
    createInfo.flags = gfxDeviceMemoryAllocationCreateMaskTo(info.GetCreateMask());
    createInfo.usage = gfxDeviceMemoryAllocationUsageTo(info.GetUsage());
    createInfo.requiredFlags = gfxDeviceMemoryPropertyMaskTo(info.GetRequiredPropertiesMask());
    createInfo.preferredFlags = gfxDeviceMemoryPropertyMaskTo(info.GetPreferredPropertiesMask());
    createInfo.priority = info.GetPriority();
    // TODO: set other properties

    VkImageCreateInfo imageCreateInfo{};
    imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageCreateInfo.flags = gfxImageCreateMaskTo(imageInfo.GetCreateMask());
    imageCreateInfo.imageType = gfxImageTypeTo(imageInfo.GetType());
    imageCreateInfo.format = gfxFormatTo(imageInfo.GetFormat());
    imageCreateInfo.extent.width = imageInfo.GetExtent().x;
    imageCreateInfo.extent.height = imageInfo.GetExtent().y;
    imageCreateInfo.extent.depth = imageInfo.GetExtent().z;
    imageCreateInfo.mipLevels = imageInfo.GetMipLevels();
    imageCreateInfo.arrayLayers = imageInfo.GetArrayLayers();
    imageCreateInfo.samples = gfxSampleCountMaskTo(imageInfo.GetSampleCount());
    imageCreateInfo.tiling = gfxImageTilingTo(imageInfo.GetTiling());
    imageCreateInfo.usage = gfxImageUsageMaskTo(imageInfo.GetUsageMask());
    imageCreateInfo.sharingMode = gfxSharingModeTo(imageInfo.GetSharingMode());
    imageCreateInfo.initialLayout = gfxImageLayoutTo(imageInfo.GetInitialLayout());

    std::vector<epiU32> queueFamilyIndices;
    if (imageInfo.GetSharingMode() == gfxSharingMode::Concurrent)
    {
        queueFamilyIndices.reserve(imageInfo.GetQueueFamilies().Size());

        std::transform(imageInfo.GetQueueFamilies().begin(),
                       imageInfo.GetQueueFamilies().end(),
                       std::back_inserter(queueFamilyIndices),
                       [](const gfxQueueFamily& family)
        {
            const std::shared_ptr<gfxQueueFamilyImplVK> familyImpl = ImplOf<gfxQueueFamilyImplVK>(family);

            return familyImpl->GetIndex();
        });

        imageCreateInfo.queueFamilyIndexCount = queueFamilyIndices.size();
        imageCreateInfo.pQueueFamilyIndices = queueFamilyIndices.data();
    }

    VkImage imageVk{nullptr};
    if (const VkResult result = vmaCreateImage(allocatorImpl->GetVmaAllocator(),
                                               &imageCreateInfo,
                                               &createInfo,
                                               &imageVk,
                                               &m_VmaAllocation,
                                               nullptr); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vmaCreateImage!");
        return std::nullopt;
    }

    const std::shared_ptr<gfxImageImplVK> imageImpl = std::make_shared<gfxImageImplVK>(m_Allocator.GetDevice());
    if (!imageImpl->Init(imageVk))
    {
        epiLogError("Failed to init Image!");
        return std::nullopt;
    }

    return gfxImage(imageImpl);
}

epiBool gfxDeviceMemoryAllocationImplVK::InitBufferAllocated(const gfxDeviceMemoryAllocationCreateInfo& info,
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

    return BindBuffer(buffer);
}

epiBool gfxDeviceMemoryAllocationImplVK::InitImageAllocated(const gfxDeviceMemoryAllocationCreateInfo& info,
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

    return BindImage(image);
}

epiBool gfxDeviceMemoryAllocationImplVK::IsPropertyEnabled(gfxDeviceMemoryPropertyMask mask) const
{
    const std::shared_ptr<gfxDeviceMemoryAllocatorImplVK> allocatorImpl = ImplOf<gfxDeviceMemoryAllocatorImplVK>(m_Allocator);
    const std::shared_ptr<gfxPhysicalDeviceImplVK> physicalDeviceImpl = ImplOf<gfxPhysicalDeviceImplVK>(m_Allocator.GetDevice().GetPhysicalDevice());

    VmaAllocationInfo info{};
    vmaGetAllocationInfo(allocatorImpl->GetVmaAllocator(), m_VmaAllocation, &info);

    VkMemoryPropertyFlags memFlags;
    vmaGetMemoryTypeProperties(allocatorImpl->GetVmaAllocator(), info.memoryType, &memFlags);

    const VkMemoryPropertyFlags maskVk = gfxDeviceMemoryPropertyMaskTo(mask);

    return (memFlags & maskVk) == maskVk;
}

epiBool gfxDeviceMemoryAllocationImplVK::BindBuffer(const gfxBuffer& buffer)
{
    const std::shared_ptr<gfxDeviceMemoryAllocatorImplVK> allocatorImpl = ImplOf<gfxDeviceMemoryAllocatorImplVK>(m_Allocator);
    const std::shared_ptr<gfxBufferImplVK> bufferImpl = ImplOf<gfxBufferImplVK>(buffer);

    if (const VkResult result = vmaBindBufferMemory(allocatorImpl->GetVmaAllocator(), m_VmaAllocation, bufferImpl->GetVkBuffer()); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vmaBindBufferMemory!");
        return false;
    }

    return true;
}

epiBool gfxDeviceMemoryAllocationImplVK::BindImage(const gfxImage& image)
{
    const std::shared_ptr<gfxDeviceMemoryAllocatorImplVK> allocatorImpl = ImplOf<gfxDeviceMemoryAllocatorImplVK>(m_Allocator);
    const std::shared_ptr<gfxImageImplVK> imageImpl = ImplOf<gfxImageImplVK>(image);

    if (const VkResult result = vmaBindImageMemory(allocatorImpl->GetVmaAllocator(), m_VmaAllocation, imageImpl->GetVkImage()); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vmaBindImageMemory!");
        return false;
    }

    return true;
}

epiBool gfxDeviceMemoryAllocationImplVK::IsMapped() const
{
    const std::shared_ptr<gfxDeviceMemoryAllocatorImplVK> allocatorImpl = ImplOf<gfxDeviceMemoryAllocatorImplVK>(m_Allocator);

    VmaAllocationInfo info{};
    vmaGetAllocationInfo(allocatorImpl->GetVmaAllocator(), m_VmaAllocation, &info);

    return info.pMappedData != nullptr;
}

epiByte* gfxDeviceMemoryAllocationImplVK::Mapped()
{
    const std::shared_ptr<gfxDeviceMemoryAllocatorImplVK> allocatorImpl = ImplOf<gfxDeviceMemoryAllocatorImplVK>(m_Allocator);

    VmaAllocationInfo info{};
    vmaGetAllocationInfo(allocatorImpl->GetVmaAllocator(), m_VmaAllocation, &info);

    return reinterpret_cast<epiByte*>(info.pMappedData);
}

void gfxDeviceMemoryAllocationImplVK::Map()
{
    const std::shared_ptr<gfxDeviceMemoryAllocatorImplVK> allocatorImpl = ImplOf<gfxDeviceMemoryAllocatorImplVK>(m_Allocator);

    void* mapped = nullptr;
    if (const VkResult result = vmaMapMemory(allocatorImpl->GetVmaAllocator(), m_VmaAllocation, &mapped); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vmaMapMemory!");
    }
}

void gfxDeviceMemoryAllocationImplVK::Unmap()
{
    const std::shared_ptr<gfxDeviceMemoryAllocatorImplVK> allocatorImpl = ImplOf<gfxDeviceMemoryAllocatorImplVK>(m_Allocator);

    vmaUnmapMemory(allocatorImpl->GetVmaAllocator(), m_VmaAllocation);
}

epiBool gfxDeviceMemoryAllocationImplVK::Invalidate(epiSize_t offset, epiSize_t size)
{
    const std::shared_ptr<gfxDeviceMemoryAllocatorImplVK> allocatorImpl = ImplOf<gfxDeviceMemoryAllocatorImplVK>(m_Allocator);

    if (const VkResult result = vmaInvalidateAllocation(allocatorImpl->GetVmaAllocator(),
                                                        m_VmaAllocation,
                                                        offset,
                                                        size == 0 ? VK_WHOLE_SIZE : size); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vmaInvalidateAllocation!");
        return false;
    }

    return true;
}

epiBool gfxDeviceMemoryAllocationImplVK::Flush(epiSize_t offset, epiSize_t size)
{
    const std::shared_ptr<gfxDeviceMemoryAllocatorImplVK> allocatorImpl = ImplOf<gfxDeviceMemoryAllocatorImplVK>(m_Allocator);

    if (const VkResult result = vmaFlushAllocation(allocatorImpl->GetVmaAllocator(),
                                                   m_VmaAllocation,
                                                   offset,
                                                   size == 0 ? VK_WHOLE_SIZE : size); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vmaFlushAllocation!");
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

    std::optional<gfxBuffer> buffer = impl->InitBuffer(allocationInfo, bufferInfo);
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

    std::optional<gfxImage> image = impl->InitImage(allocationInfo, imageInfo);
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
    if (!impl->InitBufferAllocated(info, buffer))
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
    if (!impl->InitImageAllocated(info, image))
    {
        epiLogError("Failed to allocate Image!");
        return std::nullopt;
    }

    return gfxDeviceMemoryAllocation(impl);
}

void gfxDeviceMemoryAllocatorImplVK::SetCurrentFrameIndex(epiU32 value)
{
    vmaSetCurrentFrameIndex(m_VmaAllocator, value);
}

std::optional<gfxDeviceMemoryAllocatorBudget> gfxDeviceMemoryAllocatorImplVK::QueryBudget() const
{
    VmaBudget budgetVma{};

    vmaGetBudget(m_VmaAllocator, &budgetVma);

    gfxDeviceMemoryAllocatorBudget budget{};
    budget.SetBlockBytes(budgetVma.blockBytes);
    budget.SetAllocationBytes(budgetVma.allocationBytes);
    budget.SetUsageBytes(budgetVma.usage);
    budget.SetBudgetBytes(budgetVma.budget);

    return budget;
}

std::optional<gfxDeviceMemoryAllocatorStats> gfxDeviceMemoryAllocatorImplVK::QueryStats() const
{
    VmaStats statsVma{};

    vmaCalculateStats(m_VmaAllocator, &statsVma);

    auto convert = [](const VmaStatInfo& infoVma)
    {
        gfxDeviceMemoryAllocatorStatInfo info{};
        info.SetBlockCount(infoVma.blockCount);
        info.SetAllocationCount(infoVma.allocationCount);
        info.SetUnusedRangeCount(infoVma.unusedRangeCount);
        info.SetUsedBytes(infoVma.usedBytes);
        info.SetUnusedBytes(infoVma.unusedBytes);
        info.SetAllocationSizeMin(infoVma.allocationSizeMin);
        info.SetAllocationSizeAvg(infoVma.allocationSizeAvg);
        info.SetAllocationSizeMax(infoVma.allocationSizeMax);
        info.SetUnusedRangeSizeMin(infoVma.unusedRangeSizeMin);
        info.SetUnusedRangeSizeAvg(infoVma.unusedRangeSizeAvg);
        info.SetUnusedRangeSizeMax(infoVma.unusedRangeSizeMax);

        return info;
    };

    gfxDeviceMemoryAllocatorStats stats{};
    stats.SetTotal(convert(statsVma.total));

    stats.GetMemoryTypes().Reserve(VK_MAX_MEMORY_TYPES);
    std::transform(statsVma.memoryType,
                   statsVma.memoryType + VK_MAX_MEMORY_TYPES,
                   std::back_inserter(stats.GetMemoryTypes()),
                   [&convert](const VmaStatInfo& infoVma)
    {
        return convert(infoVma);
    });

    stats.GetMemoryHeaps().Reserve(VK_MAX_MEMORY_HEAPS);
    std::transform(statsVma.memoryHeap,
                   statsVma.memoryHeap + VK_MAX_MEMORY_HEAPS,
                   std::back_inserter(stats.GetMemoryHeaps()),
                   [&convert](const VmaStatInfo& infoVma)
    {
        return convert(infoVma);
    });

    return stats;
}

VmaAllocator gfxDeviceMemoryAllocatorImplVK::GetVmaAllocator() const
{
    return m_VmaAllocator;
}

EPI_NAMESPACE_END()
