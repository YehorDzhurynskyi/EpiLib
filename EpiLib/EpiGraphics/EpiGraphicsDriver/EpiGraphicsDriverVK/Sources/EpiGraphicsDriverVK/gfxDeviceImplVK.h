#include "EpiGraphicsDriverAPI/EpiGraphicsDriverAPI.h"

#include <vulkan/vulkan.hpp>

EPI_NAMESPACE_BEGIN()

class gfxPhysicalDeviceImplVK;
class gfxQueueImplVK;
class gfxDeviceImplVK : public gfxDeviceImpl
{
public:
    gfxDeviceImplVK(const gfxPhysicalDeviceImplVK& physicalDevice, gfxQueueFamily queueFamilyMask, gfxPhysicalDeviceExtension extensionMask);
    gfxDeviceImplVK(const gfxDeviceImplVK& rhs) = delete;
    gfxDeviceImplVK& operator=(const gfxDeviceImplVK& rhs) = delete;
    gfxDeviceImplVK(gfxDeviceImplVK&& rhs) = default;
    gfxDeviceImplVK& operator=(gfxDeviceImplVK&& rhs) = default;
    ~gfxDeviceImplVK() override;

    gfxQueueImpl* GetQueue(gfxQueueFamily family) const override;

    VkDevice GetVkDevice() const;

protected:
    VkDevice m_VkDevice{VK_NULL_HANDLE};
    std::unique_ptr<gfxQueueImplVK> m_QueueGraphics;
    std::unique_ptr<gfxQueueImplVK> m_QueueCompute;
    std::unique_ptr<gfxQueueImplVK> m_QueueTransfer;
    std::unique_ptr<gfxQueueImplVK> m_QueueSparseBinding;
    std::unique_ptr<gfxQueueImplVK> m_QueueProtected;
    std::unique_ptr<gfxQueueImplVK> m_QueuePresentation;
};

EPI_NAMESPACE_END()
