#pragma once

#include "EpiGraphicsDriverImpl/EpiGraphicsDriverImpl.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxQueueFamilyImplVK : public gfxQueueFamilyImpl
{
public:
    gfxQueueFamilyImplVK(epiU32 queueFamilyIndex, epiU32 queueCount, gfxQueueType supportedQueueTypes, epiBool isPresentSupported);
    gfxQueueFamilyImplVK(const gfxQueueFamilyImplVK& rhs) = default;
    gfxQueueFamilyImplVK& operator=(const gfxQueueFamilyImplVK& rhs) = default;
    gfxQueueFamilyImplVK(gfxQueueFamilyImplVK&& rhs) = default;
    gfxQueueFamilyImplVK& operator=(gfxQueueFamilyImplVK&& rhs) = default;
    ~gfxQueueFamilyImplVK() override = default;

    epiBool IsQueueTypeSupported(gfxQueueType mask) const override;
    epiU32 QueueTypeSupportedCount() const override;

    epiBool IsPresentSupported() const override;

    epiU32 GetIndex() const;

protected:
    epiU32 m_Index{0};
    epiU32 m_QueueCount{0};
    gfxQueueType m_QueueTypeSupported{0};
    epiBool m_IsPresentSupported{false}; // TODO: won't work if Surface will be changed
};

} // namespace internalgfx

EPI_NAMESPACE_END()
