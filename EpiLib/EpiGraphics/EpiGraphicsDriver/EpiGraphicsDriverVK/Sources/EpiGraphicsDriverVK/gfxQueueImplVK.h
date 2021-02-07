#include "EpiGraphicsDriverAPI/EpiGraphicsDriverAPI.h"

#include <vulkan/vulkan.hpp>

EPI_NAMESPACE_BEGIN()

class gfxDeviceImplVK;
class gfxQueueImplVK : public gfxQueueImpl
{
public:
    gfxQueueImplVK(const gfxDeviceImplVK& device, epiU32 queueFamilyIndex);
    gfxQueueImplVK(const gfxQueueImplVK& rhs) = delete;
    gfxQueueImplVK& operator=(const gfxQueueImplVK& rhs) = delete;
    gfxQueueImplVK(gfxQueueImplVK&& rhs) = default;
    gfxQueueImplVK& operator=(gfxQueueImplVK&& rhs) = default;
    ~gfxQueueImplVK() override = default;

protected:
    VkQueue m_VKQueue{VK_NULL_HANDLE};
};

EPI_NAMESPACE_END()
