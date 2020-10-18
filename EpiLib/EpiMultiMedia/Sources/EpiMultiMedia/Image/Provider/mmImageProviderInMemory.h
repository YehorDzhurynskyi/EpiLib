#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/Provider/mmImageProviderInMemory.hxx"
EPI_GENREGION_END(include)

#include "EpiMultimedia/Image/Provider/mmImageProviderBase.h"
#include "EpiMultimedia/Image/mmImage.h"

EPI_NAMESPACE_BEGIN()

class mmImageProviderInMemory : public mmImageProviderBase
{
EPI_GENREGION_BEGIN(mmImageProviderInMemory)

EPI_GENHIDDEN_mmImageProviderInMemory()

public:
    constexpr static epiMetaTypeID TypeID{0x1fb0d977};

    enum mmImageProviderInMemory_PIDs
    {
        PID_Image = 0x4fc2b5b,
        PID_COUNT = 1
    };

protected:
    mmImage* m_Image{nullptr};

EPI_GENREGION_END(mmImageProviderInMemory)
};

EPI_NAMESPACE_END()
