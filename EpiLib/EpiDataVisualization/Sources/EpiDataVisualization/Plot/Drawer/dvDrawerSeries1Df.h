#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Plot/Drawer/dvDrawerSeries1Df.hxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/Plot/Drawer/dvDrawerSeriesBase.h"
#include "EpiDataVisualization/Plot/ViewModel/dvVMSeries1Df.h"

EPI_NAMESPACE_BEGIN()

class dvDrawerSeries1Df : public dvDrawerSeriesBase
{
EPI_GENREGION_BEGIN(dvDrawerSeries1Df)

EPI_GENHIDDEN_dvDrawerSeries1Df()

public:
    constexpr static epiMetaTypeID TypeID{0xe4164c70};

    enum dvDrawerSeries1Df_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(dvDrawerSeries1Df)

public:
    void Draw(drwContext& ctx, const dvVMSeries1Df& series, const epiRect2f& worldFrame, const epiRect2f& uiFrame);
};

EPI_NAMESPACE_END()
