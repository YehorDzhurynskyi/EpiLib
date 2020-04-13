#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/DataCollection.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class DataCollection : public Object
{
EPI_GENREGION_BEGIN(DataCollection)
public:
    EPI_GENHIDDEN_DataCollection()

    constexpr static MetaTypeID TypeID{0xbc47ff11};

    enum DataCollection_PIDs
    {
        PID_COUNT = 0
    };

protected:

EPI_GENREGION_END(DataCollection)
};

EPI_NAMESPACE_END()
