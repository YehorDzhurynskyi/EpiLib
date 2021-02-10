#pragma once

#include "EpiGraphicsDriverImpl/EpiGraphicsDriverImpl.h"

struct VkQueue_T;

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxDeviceImplVK;
class gfxQueueFamilyImplVK;
class gfxQueueImplVK : public gfxQueueImpl
{
public:
    gfxQueueImplVK(const gfxDeviceImplVK& device, const gfxQueueFamilyImplVK& queueFamily, epiU32 queueIndex);
    gfxQueueImplVK(const gfxQueueImplVK& rhs) = delete;
    gfxQueueImplVK& operator=(const gfxQueueImplVK& rhs) = delete;
    gfxQueueImplVK(gfxQueueImplVK&& rhs);
    gfxQueueImplVK& operator=(gfxQueueImplVK&& rhs);
    ~gfxQueueImplVK() override = default;

    epiBool IsQueueTypeSupported(gfxQueueType mask) const override;
    epiBool IsPresentSupported() const override;

protected:
    VkQueue_T* m_VkQueue{nullptr};

    const gfxQueueFamilyImplVK* m_QueueFamily{nullptr};
};

} // namespace internalgfx

EPI_NAMESPACE_END()
