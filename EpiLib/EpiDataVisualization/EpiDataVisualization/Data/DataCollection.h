#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Data/DataCollection.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

// TODO: should it be a struct in epi file?
class DataCollection : public Object
{
EPI_GENREGION_BEGIN(DataCollection)
public:
    EPI_GENHIDDEN_DataCollection()

    constexpr static MetaTypeID TypeID{0xbc47ff11};

    enum DataCollection_PIDs
    {
        PID_Data = 0xdc15c5d,
        PID_COUNT = 1
    };

protected:
    epiArray<epiFloat> m_Data;

EPI_GENREGION_END(DataCollection)
};

EPI_NAMESPACE_END()
