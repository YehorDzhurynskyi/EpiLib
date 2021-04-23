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

class gfxQueue : public Object, public epiPimpl<internalgfx::gfxQueueImpl>
{
EPI_GENREGION_BEGIN(gfxQueue)

EPI_GENHIDDEN_gfxQueue()

public:
    constexpr static epiMetaTypeID TypeID{0xc80527c2};

    enum gfxQueue_PIDs
    {
        PID_Type = 0x2cecf817,
        PID_Priority = 0x9bd0be71,
        PID_COUNT = 2
    };

protected:
    gfxQueueType GetType_Callback() const;
    epiFloat GetPriority_Callback() const;

EPI_GENREGION_END(gfxQueue)

public:
    friend class gfxSwapChain;

public:
    gfxQueue() = default;
    gfxQueue(internalgfx::gfxQueueImpl* impl, epiBool isOwner);

    epiBool IsQueueTypeSupported(gfxQueueType mask) const;
};

EPI_NAMESPACE_END()
