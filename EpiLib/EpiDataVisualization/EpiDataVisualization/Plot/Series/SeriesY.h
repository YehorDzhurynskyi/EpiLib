#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Plot/Series/SeriesY.hxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/Plot/Series/SeriesBase.h"
#include "EpiDataVisualization/Data/DataCollection.h"

EPI_NAMESPACE_BEGIN()

class SeriesY : public SeriesBase
{
EPI_GENREGION_BEGIN(SeriesY)
public:
    EPI_GENHIDDEN_SeriesY()

    constexpr static MetaTypeID TypeID{0x4aed7335};

    enum SeriesY_PIDs
    {
        PID_DataY = 0xd562eac8,
        PID_StepX = 0x595fdc36,
        PID_COUNT = 2
    };

protected:
    DataCollection m_DataY;
    epiFloat m_StepX{0.0f};

EPI_GENREGION_END(SeriesY)
};

EPI_NAMESPACE_END()
