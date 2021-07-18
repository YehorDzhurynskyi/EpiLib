#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

struct VkQueue_T;
struct VkFence_T;

EPI_NAMESPACE_BEGIN()

class gfxDeviceImplVK;
class gfxQueueFamilyImplVK;
class gfxQueueImplVK : public gfxQueue::Impl
{
public:
    gfxQueueImplVK(const gfxDeviceImplVK& device, const gfxQueueFamilyImplVK& queueFamily, epiU32 queueIndex, epiFloat priority);
    gfxQueueImplVK(const gfxQueueImplVK& rhs) = delete;
    gfxQueueImplVK& operator=(const gfxQueueImplVK& rhs) = delete;
    gfxQueueImplVK(gfxQueueImplVK&& rhs);
    gfxQueueImplVK& operator=(gfxQueueImplVK&& rhs);
    ~gfxQueueImplVK() override = default;

    epiBool Submit(const epiArray<gfxQueueSubmitInfo>& infos) override;
    epiBool Submit(const epiArray<gfxQueueSubmitInfo>& infos, const gfxFence& signalFence) override;

    epiBool Present(const gfxQueuePresentInfo& info) override;

    epiBool Wait() override;

    gfxQueueType GetType() const override;
    epiFloat GetPriority() const override;
    epiBool IsQueueTypeSupported(gfxQueueType mask) const override;

    VkQueue_T* GetVkQueue() const;

protected:
    epiBool Submit(const epiArray<gfxQueueSubmitInfo>& infos, VkFence_T* signalFence);

protected:
    VkQueue_T* m_VkQueue{nullptr};
    gfxQueueType m_Type{0};
    epiFloat m_Priority{0.0f};
};

EPI_NAMESPACE_END()
