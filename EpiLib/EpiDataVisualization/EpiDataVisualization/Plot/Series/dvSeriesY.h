#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Plot/Series/dvSeriesY.hxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/Plot/Series/dvSeriesBase.h"
#include "EpiDataVisualization/Data/dvDataCollection.h"

EPI_NAMESPACE_BEGIN()

class dvSeriesY : public dvSeriesBase
{
EPI_GENREGION_BEGIN(dvSeriesY)
public:
    EPI_GENHIDDEN_dvSeriesY()

    constexpr static MetaTypeID TypeID{0x5a38f05a};

    enum dvSeriesY_PIDs
    {
        PID_DataY = 0xd562eac8,
        PID_StepX = 0x595fdc36,
        PID_COUNT = 2
    };

protected:
    dvDataCollection m_DataY;
    epiFloat m_StepX{0.0f};

EPI_GENREGION_END(dvSeriesY)

public:
    void Add(epiFloat y);
};

EPI_NAMESPACE_END()
