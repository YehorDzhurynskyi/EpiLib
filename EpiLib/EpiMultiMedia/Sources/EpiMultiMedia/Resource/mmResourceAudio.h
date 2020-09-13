#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Resource/mmResourceAudio.hxx"
EPI_GENREGION_END(include)

#include "EpiMultimedia/Resource/mmResource.h"

#include "EpiData/Series/dSeries1Df.h"

EPI_NAMESPACE_BEGIN()

class mmResourceAudio : public mmResource
{
EPI_GENREGION_BEGIN(mmResourceAudio)

EPI_GENHIDDEN_mmResourceAudio()

public:
    constexpr static epiMetaTypeID TypeID{0x65770f3d};

    enum mmResourceAudio_PIDs
    {
        PID_SampleRate = 0x2d49dd9c,
        PID_Samples = 0xd62f6eeb,
        PID_COUNT = 2
    };

protected:
    epiU32 m_SampleRate{0};
    dSeries1Df m_Samples{};

EPI_GENREGION_END(mmResourceAudio)
};

EPI_NAMESPACE_END()
