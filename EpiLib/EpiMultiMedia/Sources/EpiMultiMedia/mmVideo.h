#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/mmVideo.hxx"
EPI_GENREGION_END(include)

#include "EpiMultimedia/mmMediaBase.h"
#include "EpiMultimedia/mmFrame.h"

#include "EpiData/Series/dSeries1Df.h"

EPI_NAMESPACE_BEGIN()

class mmVideo : public mmMediaBase
{
EPI_GENREGION_BEGIN(mmVideo)

EPI_GENHIDDEN_mmVideo()

public:
    constexpr static epiMetaTypeID TypeID{0xb843ecea};

    enum mmVideo_PIDs
    {
        PID_FrameRate = 0x3317143d,
        PID_BitRate = 0x33cbeca8,
        PID_Frames = 0xf9c28c0c,
        PID_COUNT = 3
    };

protected:
    epiU32 m_FrameRate{0};
    epiU32 m_BitRate{0};
    epiArray<mmFrame> m_Frames{};

EPI_GENREGION_END(mmVideo)
};

EPI_NAMESPACE_END()
