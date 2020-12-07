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
        PID_NumberOfLogicalThreads = 0x7f08e3a,
        PID_COUNT = 1
    };

protected:
    epiSize_t GetNumberOfLogicalThreads_Callback() const;

EPI_GENREGION_END(epiDeviceCPUBase)

public:
    epiString ToString() const override;
};

EPI_NAMESPACE_END()
