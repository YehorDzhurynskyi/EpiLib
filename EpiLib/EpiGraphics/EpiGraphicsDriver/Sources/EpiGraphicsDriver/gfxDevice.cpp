EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriver/gfxDevice.h"
#include "EpiGraphicsDriver/gfxDevice.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverImpl/EpiGraphicsDriverImpl.h"

EPI_NAMESPACE_BEGIN()

gfxDevice::gfxDevice(internalgfx::gfxDeviceImpl* impl)
    : m_Impl{impl}
{
}

gfxDevice::gfxDevice(gfxDevice&& rhs)
{
    m_Impl = rhs.m_Impl;
    rhs.m_Impl = nullptr;
}

gfxDevice& gfxDevice::operator=(gfxDevice&& rhs)
{
    m_Impl = rhs.m_Impl;
    rhs.m_Impl = nullptr;

    return *this;
}

gfxDevice::~gfxDevice()
{
    delete m_Impl;
}

gfxQueue* gfxDevice::GetQueue(gfxQueueType queueTypeMask, epiBool presentSupportRequired)
{
    internalgfx::gfxQueueImpl* impl = m_Impl->GetQueue(queueTypeMask, presentSupportRequired);
    if (impl == nullptr)
    {
        return nullptr;
    }

    gfxQueue queue(impl);
    m_Queues.push_back(std::move(queue));

    return &m_Queues.back();
}

EPI_NAMESPACE_END()
