#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/Provider/mmImageProviderBase.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class mmImageProviderBase : public Object
{
EPI_GENREGION_BEGIN(mmImageProviderBase)

EPI_GENHIDDEN_mmImageProviderBase()

public:
    constexpr static epiMetaTypeID TypeID{0x8ce91c70};

    enum mmImageProviderBase_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(mmImageProviderBase)
};

EPI_NAMESPACE_END()
