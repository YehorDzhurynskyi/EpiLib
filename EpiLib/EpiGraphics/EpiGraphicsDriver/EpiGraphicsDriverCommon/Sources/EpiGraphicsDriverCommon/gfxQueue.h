#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxQueue.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxEnum.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxQueueImpl;

} // internalgfx

class gfxQueue : public Object
{
EPI_GENREGION_BEGIN(gfxQueue)

EPI_GENHIDDEN_gfxQueue()

public:
    constexpr static epiMetaTypeID TypeID{0xc80527c2};

    enum gfxQueue_PIDs
    {
        PID_Type = 0x2cecf817,
        PID_COUNT = 1
    };

protected:
    gfxQueueType GetType_Callback() const;

EPI_GENREGION_END(gfxQueue)

public:
    gfxQueue() = default;
    gfxQueue(internalgfx::gfxQueueImpl* impl);
    gfxQueue(const gfxQueue& rhs) = delete;
    gfxQueue& operator=(const gfxQueue& rhs) = delete;
    gfxQueue(gfxQueue&& rhs);
    gfxQueue& operator=(gfxQueue&& rhs);
    ~gfxQueue();

protected:
    internalgfx::gfxQueueImpl* m_Impl{nullptr};
};

EPI_NAMESPACE_END()
