#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/View/dvViewPlot.hxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/ViewModel/dvViewModelPlot.h"

#include "EpiUI/uiWidget.h"

EPI_NAMESPACE_BEGIN()

class dvViewPlot : public uiWidget
{
EPI_GENREGION_BEGIN(dvViewPlot)

EPI_GENHIDDEN_dvViewPlot()

public:
    constexpr static MetaTypeID TypeID{0x195ed8c9};

    enum dvViewPlot_PIDs
    {
        PID_ViewModel = 0x373a6339,
        PID_COUNT = 1
    };

protected:
    dvViewModelPlot m_ViewModel;

EPI_GENREGION_END(dvViewPlot)
};

EPI_NAMESPACE_END()
