#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxQueueFamilyDescriptorImplVK : public gfxQueueFamilyDescriptorImpl
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

class gfxQueueFamilyImplVK : public gfxQueueFamilyImpl
{
public:
    gfxQueueFamilyImplVK(const gfxQueueFamilyDescriptorImplVK& queueFamilyDesc, const gfxQueueDescriptor& queueDesc);
    gfxQueueFamilyImplVK(const gfxQueueFamilyImplVK& rhs) = default;
    gfxQueueFamilyImplVK& operator=(const gfxQueueFamilyImplVK& rhs) = default;
    gfxQueueFamilyImplVK(gfxQueueFamilyImplVK&& rhs) = default;
    gfxQueueFamilyImplVK& operator=(gfxQueueFamilyImplVK&& rhs) = default;
    ~gfxQueueFamilyImplVK() override = default;

    void Init(const gfxDeviceImpl& device) override;

    epiU32 GetIndex() const;

protected:
    epiU32 m_Index{0};
};

} // namespace internalgfx

EPI_NAMESPACE_END()
