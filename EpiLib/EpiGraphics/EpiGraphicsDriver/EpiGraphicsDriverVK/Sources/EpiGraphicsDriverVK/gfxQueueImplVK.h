#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

struct VkQueue_T;

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxDeviceImplVK;
class gfxQueueFamilyImplVK;
class gfxQueueImplVK : public gfxQueueImpl
{
public:
    gfxQueueImplVK(const gfxDeviceImplVK& device, const gfxQueueFamilyImplVK& queueFamily, epiU32 queueIndex, epiFloat priority);
    gfxQueueImplVK(const gfxQueueImplVK& rhs) = delete;
    gfxQueueImplVK& operator=(const gfxQueueImplVK& rhs) = delete;
    gfxQueueImplVK(gfxQueueImplVK&& rhs);
    gfxQueueImplVK& operator=(gfxQueueImplVK&& rhs);
    ~gfxQueueImplVK() override = default;

    epiBool Submit(const gfxQueueSubmitInfo& info, const epiPtrArray<const gfxCommandBufferImpl>& commandBuffers) override;

    gfxQueueType GetType() const override;
    epiFloat GetPriority() const override;
    epiBool IsQueueTypeSupported(gfxQueueType mask) const override;

    VkQueue_T* GetVkQueue() const;

protected:
    VkQueue_T* m_VkQueue{nullptr};
    gfxQueueType m_Type{0};
    epiFloat m_Priority{0.0f};
};

} // namespace internalgfx

EPI_NAMESPACE_END()
