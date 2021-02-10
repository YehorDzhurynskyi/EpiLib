#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriver/gfxDevice.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriver/gfxQueue.h"

#include "EpiGraphicsEnum/EpiGraphicsEnum.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxDeviceImpl;

} // namespace internalgfx

class gfxDevice : public Object
{
EPI_GENREGION_BEGIN(gfxDevice)

EPI_GENHIDDEN_gfxDevice()

public:
    constexpr static epiMetaTypeID TypeID{0xa849dda8};

    enum gfxDevice_PIDs
    {
        PID_Queues = 0xc86607a0,
        PID_COUNT = 1
    };

protected:
    epiArray<gfxQueue> m_Queues{};

EPI_GENREGION_END(gfxDevice)

public:
    gfxDevice() = default;
    gfxDevice(internalgfx::gfxDeviceImpl* impl);
    gfxDevice(const gfxDevice& rhs) = delete;
    gfxDevice& operator=(const gfxDevice& rhs) = delete;
    gfxDevice(gfxDevice&& rhs);
    gfxDevice& operator=(gfxDevice&& rhs);
    ~gfxDevice();

    gfxQueue* GetQueue(gfxQueueType queueTypeMask, epiBool presentSupportRequired);

protected:
    internalgfx::gfxDeviceImpl* m_Impl{nullptr};
};

EPI_NAMESPACE_END()
