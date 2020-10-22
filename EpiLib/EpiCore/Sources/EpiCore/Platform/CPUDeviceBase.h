#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiCore/Platform/CPUDeviceBase.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class CPUDeviceBase : public Object
{
EPI_GENREGION_BEGIN(CPUDeviceBase)

EPI_GENHIDDEN_CPUDeviceBase()

public:
    constexpr static epiMetaTypeID TypeID{0x51656917};

    enum CPUDeviceBase_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(CPUDeviceBase)
};

EPI_NAMESPACE_END()
