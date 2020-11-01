#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiCore/Platform/epiDeviceCPUBase.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class epiDeviceCPUBase : public Object
{
EPI_GENREGION_BEGIN(epiDeviceCPUBase)

EPI_GENHIDDEN_epiDeviceCPUBase()

public:
    constexpr static epiMetaTypeID TypeID{0x486d5c7b};

    enum epiDeviceCPUBase_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(epiDeviceCPUBase)
};

EPI_NAMESPACE_END()
