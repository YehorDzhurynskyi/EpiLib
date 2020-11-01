#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiCore/epiBuildInfo.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class epiBuildInfo : public Object
{
EPI_GENREGION_BEGIN(epiBuildInfo)

EPI_GENHIDDEN_epiBuildInfo()

public:
    constexpr static epiMetaTypeID TypeID{0x4b7542a4};

    enum epiBuildInfo_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(epiBuildInfo)

public:
    epiString ToString() const override;
};

EPI_NAMESPACE_END()
