#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/mmFrame.hxx"
EPI_GENREGION_END(include)

#include "EpiMultimedia/mmMediaBase.h"
#include "EpiMultimedia/mmImage.h"

#include "EpiData/Series/dSeries1Df.h"

EPI_NAMESPACE_BEGIN()

class mmFrame : public mmMediaBase
{
EPI_GENREGION_BEGIN(mmFrame)

EPI_GENHIDDEN_mmFrame()

public:
    constexpr static epiMetaTypeID TypeID{0x717c0a0b};

    enum mmFrame_PIDs
    {
        PID_Image = 0x4fc2b5b,
        PID_COUNT = 1
    };

protected:
    mmImage m_Image{};

EPI_GENREGION_END(mmFrame)
};

EPI_NAMESPACE_END()
