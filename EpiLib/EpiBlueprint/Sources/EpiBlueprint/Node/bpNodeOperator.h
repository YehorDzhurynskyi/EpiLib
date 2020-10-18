#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiBlueprint/Node/bpNodeOperator.hxx"
EPI_GENREGION_END(include)

#include "EpiBlueprint/Node/bpNodeBase.h"

EPI_NAMESPACE_BEGIN()

class bpNodeOperator : public bpNodeBase
{
EPI_GENREGION_BEGIN(bpNodeOperator)

EPI_GENHIDDEN_bpNodeOperator()

public:
    constexpr static epiMetaTypeID TypeID{0x99883288};

    enum bpNodeOperator_PIDs
    {
        PID_Input = 0x19e91dd3,
        PID_Output = 0xcb7211a8,
        PID_COUNT = 2
    };

protected:
    epiPtrArray<bpNodeBase> m_Input{};
    epiPtrArray<bpNodeBase> m_Output{};

EPI_GENREGION_END(bpNodeOperator)
};

EPI_NAMESPACE_END()
