#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Data/dvDataCollection.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class dvDataCollection : public Object
{
EPI_GENREGION_BEGIN(dvDataCollection)
public:
    EPI_GENHIDDEN_dvDataCollection()

    constexpr static MetaTypeID TypeID{0x489102dd};

    enum dvDataCollection_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(dvDataCollection)
};

EPI_NAMESPACE_END()
