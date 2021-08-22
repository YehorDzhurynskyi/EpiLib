#include "EpiGraphicsImplVK/gfxDeviceMemoryAllocatorImplVK.h"

#include "EpiGraphicsImplVK/gfxErrorVK.h"
#include "EpiGraphicsImplVK/gfxDeviceImplVK.h"
#include "EpiGraphicsImplVK/gfxInstanceImplVK.h"

#define VMA_IMPLEMENTATION
#include "vk_mem_alloc.h"

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

    if (const VkResult result = vmaCreateAllocator(&allocatorInfo, &m_VmaAllocator); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vmaCreateAllocator!");
        return false;
    }

    return true;
}

EPI_NAMESPACE_END()
