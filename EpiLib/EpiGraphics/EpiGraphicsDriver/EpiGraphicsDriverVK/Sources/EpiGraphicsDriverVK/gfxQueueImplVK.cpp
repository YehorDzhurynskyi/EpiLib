#include "EpiGraphicsDriverVK/gfxQueueImplVK.h"

#include "EpiGraphicsDriverVK/gfxDeviceImplVK.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxQueueImplVK::gfxQueueImplVK(const gfxDeviceImplVK& device, epiU32 queueFamilyIndex)
{
    vkGetDeviceQueue(device.GetVkDevice(), queueFamilyIndex, 0, &m_VKQueue);
}

} // namespace internalgfx

EPI_NAMESPACE_END()
