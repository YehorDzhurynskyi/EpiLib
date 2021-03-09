#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

#include "EpiGraphicsDriverVK/gfxQueueImplVK.h"

struct VkDevice_T;

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxPhysicalDeviceImplVK;
class gfxDeviceImplVK : public gfxDeviceImpl
{
public:
    gfxDeviceImplVK() = default;
    gfxDeviceImplVK(const gfxDeviceImplVK& rhs) = delete;
    gfxDeviceImplVK& operator=(const gfxDeviceImplVK& rhs) = delete;
    gfxDeviceImplVK(gfxDeviceImplVK&& rhs) = default;
    gfxDeviceImplVK& operator=(gfxDeviceImplVK&& rhs) = default;
    ~gfxDeviceImplVK() override;

    epiBool Init(const gfxPhysicalDeviceImplVK& physicalDevice,
                 gfxQueueDescriptorList& queueDescriptorList,
                 gfxPhysicalDeviceExtension extensionMask);

    VkDevice_T* GetVkDevice() const;

protected:
    VkDevice_T* m_VkDevice{nullptr};

    epiPtrArray<gfxQueueImpl> m_Queues;
    gfxPhysicalDeviceExtension m_ExtensionMaskEnabled{0};
};

} // namespace internalgfx

EPI_NAMESPACE_END()
