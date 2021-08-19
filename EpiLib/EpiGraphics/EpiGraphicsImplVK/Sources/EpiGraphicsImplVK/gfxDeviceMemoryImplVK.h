#pragma once

#include "EpiGraphicsImpl/gfxDeviceMemoryImpl.h"

struct VkDevice_T;
struct VkDeviceMemory_T;

EPI_NAMESPACE_BEGIN()

class gfxPhysicalDeviceImplVK;
class gfxDeviceMemoryImplVK : public gfxDeviceMemory::Impl
{
public:
    explicit gfxDeviceMemoryImplVK(VkDevice_T* device);
    gfxDeviceMemoryImplVK(const gfxDeviceMemoryImplVK& rhs) = delete;
    gfxDeviceMemoryImplVK& operator=(const gfxDeviceMemoryImplVK& rhs) = delete;
    gfxDeviceMemoryImplVK(gfxDeviceMemoryImplVK&& rhs) = default;
    gfxDeviceMemoryImplVK& operator=(gfxDeviceMemoryImplVK&& rhs) = default;
    ~gfxDeviceMemoryImplVK() override;

    epiBool Init(const gfxDeviceMemoryCreateInfo& info, const gfxPhysicalDeviceImplVK& physicalDeviceImpl);

    epiBool BindBuffer(const gfxBindBufferMemoryInfo& info) override;
    epiBool BindImage(const gfxBindImageMemoryInfo& info) override;

    epiByte* Map(epiSize_t size, epiSize_t offset) override;
    void Unmap() override;

    VkDeviceMemory_T* GetVkDeviceMemory() const;

protected:
    epiBool ValidateMemoryRequirements(epiSize_t requiredSize,
                                       epiSize_t requiredAlignment,
                                       uint32_t requiredMemoryTypeBits,
                                       epiSize_t actualOffset) const;

protected:
    VkDevice_T* m_VkDevice{nullptr};
    VkDeviceMemory_T* m_VkDeviceMemory{nullptr};

    epiSize_t m_AllocatedSize{0};
    epiS32 m_MemoryTypeIndex{-1};
};

EPI_NAMESPACE_END()
