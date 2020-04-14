#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Plot/Series/SeriesXY.hxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/Plot/Series/SeriesBase.h"
#include "EpiDataVisualization/Data/DataCollection.h"

EPI_NAMESPACE_BEGIN()

class SeriesXY : public SeriesBase
{
EPI_GENREGION_BEGIN(SeriesXY)
public:
    EPI_GENHIDDEN_SeriesXY()

    constexpr static MetaTypeID TypeID{0x8f571ecc};

    enum SeriesXY_PIDs
    {
        PID_DataX = 0xa265da5e,
        PID_DataY = 0xd562eac8,
        PID_COUNT = 2
    };

protected:
    DataCollection m_DataX;
    DataCollection m_DataY;

EPI_GENREGION_END(SeriesXY)
};

EPI_NAMESPACE_END()
