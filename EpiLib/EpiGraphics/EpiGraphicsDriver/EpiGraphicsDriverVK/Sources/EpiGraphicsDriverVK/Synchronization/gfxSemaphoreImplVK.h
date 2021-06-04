#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"
#include "EpiGraphicsDriverCommon/Synchronization/gfxSemaphore.h"

struct VkSemaphore_T;
struct VkDevice_T;

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxSemaphoreImplVK : public gfxSemaphoreImpl
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

} // internalgfx

EPI_NAMESPACE_END()
