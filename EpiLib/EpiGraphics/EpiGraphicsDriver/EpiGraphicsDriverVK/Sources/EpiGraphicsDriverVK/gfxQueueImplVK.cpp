#include "EpiGraphicsDriverVK/gfxQueueImplVK.h"

#include "EpiGraphicsDriverVK/gfxDeviceImplVK.h"

EPI_NAMESPACE_BEGIN()

gfxQueueImplVK::gfxQueueImplVK(const gfxDeviceImplVK& device, epiU32 queueFamilyIndex)
{
    vkGetDeviceQueue(device.GetVkDevice(), queueFamilyIndex, 0, &m_VKQueue);
}

EPI_NAMESPACE_END()
