#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Plot/Series/SeriesBase.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class SeriesBase : public Object
{
EPI_GENREGION_BEGIN(SeriesBase)
public:
    EPI_GENHIDDEN_SeriesBase()

    constexpr static MetaTypeID TypeID{0xf08f84b8};

    enum SeriesBase_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(SeriesBase)
};

EPI_NAMESPACE_END()
