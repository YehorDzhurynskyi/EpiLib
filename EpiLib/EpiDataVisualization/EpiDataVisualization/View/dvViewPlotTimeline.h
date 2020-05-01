#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/View/dvViewPlotTimeline.hxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/ViewModel/dvViewModelPlot.h"
#include "EpiDataVisualization/Drawer/dvDrawerPlotTimeline.h"

#include "EpiUI/uiWidget.h"

EPI_NAMESPACE_BEGIN()

class dvViewPlotTimeline : public uiWidget
{
EPI_GENREGION_BEGIN(dvViewPlotTimeline)
public:
    EPI_GENHIDDEN_dvViewPlotTimeline()

    constexpr static MetaTypeID TypeID{0x1939297a};

    enum dvViewPlotTimeline_PIDs
    {
        PID_ViewModel = 0x373a6339,
        PID_MouseWorldCoord = 0x6fbc4e30,
        PID_COUNT = 2
    };

protected:
    epiVec2f GetMouseWorldCoord_Callback() const;

protected:
    dvViewModelPlot* m_ViewModel{nullptr};

EPI_GENREGION_END(dvViewPlotTimeline)

public:
    void Update() override;
    void Draw(uiContext& uiContext) override;

    void OnMousePrimary(MouseAction action) override;
    void OnMouseWheel(epiFloat dZoom) override;
    void OnMouseFocus(epiBool focused) override;

protected:
    epiVec2f CalcMouseWorldCoord(const epiVec2f& origin) const;

protected:
    epiBool m_MouseDragActive;
    epiVec2f m_MouseDragPosition;
    epiVec2f m_MouseDragOrigin;
    dvDrawerPlotTimeline m_Drawer;
};

EPI_NAMESPACE_END()
