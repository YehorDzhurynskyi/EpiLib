#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Drawer/dvDrawerSeriesY.hxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/Drawer/dvDrawerSeriesBase.h"

EPI_NAMESPACE_BEGIN()

class dvDrawerSeriesY : public dvDrawerSeriesBase
{
EPI_GENREGION_BEGIN(dvDrawerSeriesY)
public:
    EPI_GENHIDDEN_dvDrawerSeriesY()

    constexpr static MetaTypeID TypeID{0x12b61696};

    enum dvDrawerSeriesY_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(dvDrawerSeriesY)

public:
    void Draw_Internal(uiContext& uiContext, const dvViewModelPlot& plot, const dvViewModelSeriesBase& series, const epiRect2f& frame);
};

EPI_NAMESPACE_END()
