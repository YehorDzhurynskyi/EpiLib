#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiBlueprint/Node/bpNodeBase.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class bpNodeBase : public Object
{
EPI_GENREGION_BEGIN(bpNodeBase)

EPI_GENHIDDEN_bpNodeBase()

public:
    constexpr static epiMetaTypeID TypeID{0x4a7a80f};

    enum bpNodeBase_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(bpNodeBase)
};

EPI_NAMESPACE_END()
