#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

class gfxQueueFamilyDescriptorImplVK : public gfxQueueFamilyDescriptor::Impl
{
public:
    gfxQueueFamilyDescriptorImplVK(epiU32 queueFamilyIndex, epiU32 queueCount, gfxQueueType supportedQueueTypes);
    gfxQueueFamilyDescriptorImplVK(const gfxQueueFamilyDescriptorImplVK& rhs) = default;
    gfxQueueFamilyDescriptorImplVK& operator=(const gfxQueueFamilyDescriptorImplVK& rhs) = default;
    gfxQueueFamilyDescriptorImplVK(gfxQueueFamilyDescriptorImplVK&& rhs) = default;
    gfxQueueFamilyDescriptorImplVK& operator=(gfxQueueFamilyDescriptorImplVK&& rhs) = default;
    ~gfxQueueFamilyDescriptorImplVK() override = default;

    epiBool IsQueueTypeSupported(gfxQueueType mask) const override;
    gfxQueueType GetQueueTypeSupportedMask() const override;
    epiU32 GetQueueCount() const override;

    epiU32 GetIndex() const;

protected:
    epiU32 m_Index{0};
    epiU32 m_QueueCount{0};
    gfxQueueType m_QueueTypeSupportedMask{0};
};

class gfxQueueFamilyImplVK : public gfxQueueFamily::Impl
{
public:
    explicit gfxQueueFamilyImplVK(const gfxQueueFamilyDescriptorImplVK& queueFamilyDesc);
    gfxQueueFamilyImplVK(const gfxQueueFamilyImplVK& rhs) = default;
    gfxQueueFamilyImplVK& operator=(const gfxQueueFamilyImplVK& rhs) = default;
    gfxQueueFamilyImplVK(gfxQueueFamilyImplVK&& rhs) = default;
    gfxQueueFamilyImplVK& operator=(gfxQueueFamilyImplVK&& rhs) = default;
    ~gfxQueueFamilyImplVK() override = default;

    void Init(const gfxDevice::Impl& device, const gfxQueueDescriptor& queueDesc) override;

    epiU32 GetIndex() const;

protected:
    epiU32 m_Index{0};
};

EPI_NAMESPACE_END()
