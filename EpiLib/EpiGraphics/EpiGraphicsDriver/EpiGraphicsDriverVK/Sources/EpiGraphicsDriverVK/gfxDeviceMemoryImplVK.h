#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

#include "EpiGraphicsDriverVK/gfxBufferImplVK.h"
#include "EpiGraphicsDriverVK/gfxPhysicalDeviceImplVK.h"

struct VkDevice_T;
struct VkDeviceMemory_T;

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxDeviceMemoryImplVK : public gfxDeviceMemoryImpl
{
public:
    explicit gfxDeviceMemoryImplVK(VkDevice_T* device);
    gfxDeviceMemoryImplVK(const gfxDeviceMemoryImplVK& rhs) = delete;
    gfxDeviceMemoryImplVK& operator=(const gfxDeviceMemoryImplVK& rhs) = delete;
    gfxDeviceMemoryImplVK(gfxDeviceMemoryImplVK&& rhs) = default;
    gfxDeviceMemoryImplVK& operator=(gfxDeviceMemoryImplVK&& rhs) = default;
    ~gfxDeviceMemoryImplVK() override;

    epiBool Init(const gfxDeviceMemoryBufferCreateInfo& info, const gfxPhysicalDeviceImplVK& physicalDeviceImpl, const gfxBufferImplVK& bufferImpl);
    epiBool Init(const gfxDeviceMemoryImageCreateInfo& info, const gfxPhysicalDeviceImplVK& physicalDeviceImpl);

    epiByte* Map(epiSize_t size, epiSize_t offset) override;
    void Unmap() override;

    VkDeviceMemory_T* GetVkDeviceMemory() const;

protected:
    VkDevice_T* m_VkDevice{nullptr};
    VkDeviceMemory_T* m_VkDeviceMemory{nullptr};
};

} // internalgfx

EPI_NAMESPACE_END()
