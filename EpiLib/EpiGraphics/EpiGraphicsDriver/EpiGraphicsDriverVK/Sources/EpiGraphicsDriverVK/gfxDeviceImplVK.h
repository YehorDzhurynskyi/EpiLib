#pragma once

#include "EpiGraphicsDriverImpl/EpiGraphicsDriverImpl.h"

#include "EpiGraphicsDriverVK/gfxQueueImplVK.h"

struct VkDevice_T;

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxPhysicalDeviceImplVK;
class gfxDeviceImplVK : public gfxDeviceImpl
{
public:
    gfxDeviceImplVK(const gfxPhysicalDeviceImplVK& physicalDevice, gfxQueueType queueTypeMask, gfxPhysicalDeviceExtension extensionMask, epiBool presentSupportRequired);
    gfxDeviceImplVK(const gfxDeviceImplVK& rhs) = delete;
    gfxDeviceImplVK& operator=(const gfxDeviceImplVK& rhs) = delete;
    gfxDeviceImplVK(gfxDeviceImplVK&& rhs) = default;
    gfxDeviceImplVK& operator=(gfxDeviceImplVK&& rhs) = default;
    ~gfxDeviceImplVK() override;

    gfxQueueImpl* GetQueue(gfxQueueType queueTypeMask, epiBool presentSupportRequired) const override;

    VkDevice_T* GetVkDevice() const;

protected:
    VkDevice_T* m_VkDevice{nullptr};

    const gfxPhysicalDeviceImplVK& m_PhysicalDevice;
    epiPtrArray<gfxQueueImpl> m_Queues;
};

} // namespace internalgfx

EPI_NAMESPACE_END()
