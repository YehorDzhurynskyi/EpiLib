#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/mmAudio.hxx"
EPI_GENREGION_END(include)

#include "EpiMultimedia/mmMediaBase.h"

#include "EpiData/Series/dSeries1Df.h"

EPI_NAMESPACE_BEGIN()

class mmAudio : public mmMediaBase
{
EPI_GENREGION_BEGIN(mmAudio)

EPI_GENHIDDEN_mmAudio()

public:
    constexpr static epiMetaTypeID TypeID{0xdcf90053};

    enum mmAudio_PIDs
    {
        PID_SampleRate = 0x2d49dd9c,
        PID_BitRate = 0x33cbeca8,
        PID_Channels = 0xa6280e0,
        PID_COUNT = 3
    };

protected:
    epiU32 m_SampleRate{0};
    epiU32 m_BitRate{0};
    epiArray<dSeries1Df> m_Channels{};

EPI_GENREGION_END(mmAudio)
};

EPI_NAMESPACE_END()
