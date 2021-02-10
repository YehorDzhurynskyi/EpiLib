#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriver/gfxQueue.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsEnum/EpiGraphicsEnum.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxQueueImpl;

} // namespace internalgfx

class gfxQueue : public Object
{
EPI_GENREGION_BEGIN(gfxQueue)

EPI_GENHIDDEN_gfxQueue()

public:
    constexpr static epiMetaTypeID TypeID{0xc80527c2};

    enum gfxQueue_PIDs
    {
        PID_IsPresentSupported = 0xa555aead,
        PID_COUNT = 1
    };

protected:
    epiBool GetIsPresentSupported_Callback() const;

EPI_GENREGION_END(gfxQueue)

public:
    gfxQueue() = default;
    gfxQueue(internalgfx::gfxQueueImpl* impl);
    gfxQueue(const gfxQueue& rhs) = delete;
    gfxQueue& operator=(const gfxQueue& rhs) = delete;
    gfxQueue(gfxQueue&& rhs);
    gfxQueue& operator=(gfxQueue&& rhs);
    ~gfxQueue();

    epiBool IsQueueTypeSupported(gfxQueueType mask) const;

protected:
    internalgfx::gfxQueueImpl* m_Impl{nullptr};
};

EPI_NAMESPACE_END()
