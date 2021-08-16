#pragma once

#include "EpiGraphics/gfxQueueFamily.h"

#include "EpiGraphics/gfxDevice.h"

EPI_NAMESPACE_BEGIN()

class gfxQueueFamilyDescriptor::Impl
{
public:
    static std::shared_ptr<gfxQueueFamilyDescriptor::Impl> ExtractImpl(const gfxQueueFamilyDescriptor& queueFamilyDescriptor) { return queueFamilyDescriptor.m_Impl; }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    virtual epiBool IsQueueTypeSupported(gfxQueueType mask) const = 0;
    virtual gfxQueueType GetQueueTypeSupportedMask() const = 0;
    virtual epiU32 GetQueueCount() const = 0;
};

class gfxQueueFamily::Impl
{
public:
    static std::shared_ptr<gfxQueueFamily::Impl> ExtractImpl(const gfxQueueFamily& queueFamily) { return queueFamily.m_Impl; }

public:
    explicit Impl(const gfxQueueFamilyDescriptor::Impl& queueFamilyDesc)
        : m_QueueTypeMask{queueFamilyDesc.GetQueueTypeSupportedMask()}
    {
    }

    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    virtual void Init(const gfxDevice::Impl& device, const gfxQueueDescriptor& queueDesc) = 0;

    gfxQueueType GetQueueTypeMask() const { return m_QueueTypeMask; }
    epiU32 GetQueueCount() const { return m_Queues.Size(); }

    const epiArray<std::shared_ptr<gfxQueue::Impl>>& GetQueues() const { return m_Queues; }

protected:
    epiArray<std::shared_ptr<gfxQueue::Impl>> m_Queues;
    gfxQueueType m_QueueTypeMask{0};
};

EPI_NAMESPACE_END()
