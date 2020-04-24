#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/View/dvViewPlotBase.hxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/ViewModel/dvViewModelPlotBase.h"

#include "EpiUI/uiWidget.h"

EPI_NAMESPACE_BEGIN()

class dvViewPlotBase : public uiWidget
{
EPI_GENREGION_BEGIN(dvViewPlotBase)
public:
    EPI_GENHIDDEN_dvViewPlotBase()

    constexpr static MetaTypeID TypeID{0xa80a4c41};

    enum dvViewPlotBase_PIDs
    {
        PID_ViewModel = 0x373a6339,
        PID_COUNT = 1
    };

protected:
    dvViewModelPlotBase m_ViewModel;

EPI_GENREGION_END(dvViewPlotBase)

public:
    void OnMouseWheel(epiFloat dZoom) override;
};

EPI_NAMESPACE_END()
