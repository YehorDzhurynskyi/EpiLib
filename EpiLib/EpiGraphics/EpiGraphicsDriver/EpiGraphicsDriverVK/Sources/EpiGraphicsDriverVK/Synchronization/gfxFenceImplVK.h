#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

#include "EpiGraphicsDriverCommon/Synchronization/gfxFence.h"

struct VkFence_T;
struct VkDevice_T;

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxFenceImplVK : public gfxFenceImpl
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

} // internalgfx

EPI_NAMESPACE_END()
