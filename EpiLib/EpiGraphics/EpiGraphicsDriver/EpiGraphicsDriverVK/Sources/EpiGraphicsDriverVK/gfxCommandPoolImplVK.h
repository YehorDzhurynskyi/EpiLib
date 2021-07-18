#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

struct VkDevice_T;
struct VkCommandPool_T;

EPI_NAMESPACE_BEGIN()

class gfxCommandPoolImplVK : public gfxCommandPool::Impl
{
public:
    explicit gfxCommandPoolImplVK(VkDevice_T* device);
    gfxCommandPoolImplVK(const gfxCommandPoolImplVK& rhs) = delete;
    gfxCommandPoolImplVK& operator=(const gfxCommandPoolImplVK& rhs) = delete;
    gfxCommandPoolImplVK(gfxCommandPoolImplVK&& rhs) = default;
    gfxCommandPoolImplVK& operator=(gfxCommandPoolImplVK&& rhs) = default;
    ~gfxCommandPoolImplVK() override;

    epiBool Init(const gfxCommandPoolCreateInfo& info);

protected:
    VkDevice_T* m_VkDevice{nullptr};
    VkCommandPool_T* m_VkCommandPool{nullptr};
};

EPI_NAMESPACE_END()
