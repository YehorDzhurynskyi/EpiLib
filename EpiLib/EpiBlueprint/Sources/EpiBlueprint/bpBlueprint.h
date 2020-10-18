#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiBlueprint/bpBlueprint.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiBlueprint/Node/bpNodeBase.h"

EPI_NAMESPACE_BEGIN()

class bpBlueprint : public Object
{
EPI_GENREGION_BEGIN(bpBlueprint)

EPI_GENHIDDEN_bpBlueprint()

public:
    constexpr static epiMetaTypeID TypeID{0xd7cb6fe6};

    enum bpBlueprint_PIDs
    {
        PID_Nodes = 0xdcfc2af8,
        PID_COUNT = 1
    };

protected:
    epiPtrArray<bpNodeBase> m_Nodes{};

EPI_GENREGION_END(bpBlueprint)
};

EPI_NAMESPACE_END()
