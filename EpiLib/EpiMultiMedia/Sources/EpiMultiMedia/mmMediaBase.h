#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/mmMediaBase.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class mmMediaBase : public Object
{
EPI_GENREGION_BEGIN(mmMediaBase)

EPI_GENHIDDEN_mmMediaBase()

public:
    constexpr static epiMetaTypeID TypeID{0xd69a4946};

    enum mmMediaBase_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(mmMediaBase)
};

EPI_NAMESPACE_END()
