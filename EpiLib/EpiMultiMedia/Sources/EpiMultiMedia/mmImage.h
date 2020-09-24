#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/mmImage.hxx"
EPI_GENREGION_END(include)

#include "EpiMultimedia/mmMediaBase.h"

EPI_NAMESPACE_BEGIN()

class mmImage : public mmMediaBase
{
EPI_GENREGION_BEGIN(mmImage)

EPI_GENHIDDEN_mmImage()

public:
    constexpr static epiMetaTypeID TypeID{0x1b93299};

    enum mmImage_PIDs
    {
        PID_BitDepth = 0x7d479868,
        PID_Width = 0x4ddb6a2b,
        PID_Height = 0xf2e1e039,
        PID_Data = 0xdc15c5d,
        PID_COUNT = 4
    };

protected:
    epiU32 m_BitDepth{0};
    epiSize_t m_Width{0};
    epiSize_t m_Height{0};
    epiArray<epiByte> m_Data{};

EPI_GENREGION_END(mmImage)
};

EPI_NAMESPACE_END()
