#pragma once

#include "EpiGraphics/gfxDriverInternal.h"
#include "EpiGraphics/Synchronization/gfxSemaphore.h"

struct VkDevice_T;
struct VkSemaphore_T;

EPI_NAMESPACE_BEGIN()

class gfxSemaphoreImplVK : public gfxSemaphore::Impl
{
public:
    explicit gfxSemaphoreImplVK(VkDevice_T* device);
    gfxSemaphoreImplVK(const gfxSemaphoreImplVK& rhs) = delete;
    gfxSemaphoreImplVK& operator=(const gfxSemaphoreImplVK& rhs) = delete;
    gfxSemaphoreImplVK(gfxSemaphoreImplVK&& rhs) = default;
    gfxSemaphoreImplVK& operator=(gfxSemaphoreImplVK&& rhs) = default;
    ~gfxSemaphoreImplVK() override;

    epiBool Init(const gfxSemaphoreCreateInfo& info);

    epiBool Wait(const gfxSemaphoreWaitInfo& info, epiU64 timeout) override;

    VkSemaphore_T* GetVkSemaphore() const;

protected:
    VkDevice_T* m_VkDevice{nullptr};
    VkSemaphore_T* m_VkSemaphore{nullptr};
};

EPI_NAMESPACE_END()
