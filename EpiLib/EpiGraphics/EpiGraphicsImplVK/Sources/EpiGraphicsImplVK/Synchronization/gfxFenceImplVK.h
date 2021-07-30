#pragma once

#include "EpiGraphics/gfxDriverInternal.h"

#include "EpiGraphics/Synchronization/gfxFence.h"

struct VkFence_T;
struct VkDevice_T;

EPI_NAMESPACE_BEGIN()

class gfxFenceImplVK : public gfxFence::Impl
{
public:
    explicit gfxFenceImplVK(VkDevice_T* device);
    gfxFenceImplVK(const gfxFenceImplVK& rhs) = delete;
    gfxFenceImplVK& operator=(const gfxFenceImplVK& rhs) = delete;
    gfxFenceImplVK(gfxFenceImplVK&& rhs) = default;
    gfxFenceImplVK& operator=(gfxFenceImplVK&& rhs) = default;
    ~gfxFenceImplVK() override;

    epiBool Init(const gfxFenceCreateInfo& info);

    epiBool Reset() override;
    epiBool Wait(epiU64 timeout) override;

    VkFence_T* GetVkFence() const;

protected:
    VkDevice_T* m_VkDevice{nullptr};
    VkFence_T* m_VkFence{nullptr};
};

EPI_NAMESPACE_END()
