#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiUI/Plot/uiPlotTimeline.hxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/Plot/ViewModel/dvVMPlot.h"
#include "EpiDataVisualization/Plot/Drawer/dvDrawerPlotTimeline.h"

#include "EpiUI/uiWidget.h"

EPI_NAMESPACE_BEGIN()

class uiPlotTimeline : public uiWidget
{
EPI_GENREGION_BEGIN(uiPlotTimeline)

EPI_GENHIDDEN_uiPlotTimeline()

public:
    constexpr static epiMetaTypeID TypeID{0x7ad9cd7};

    enum uiPlotTimeline_PIDs
    {
        PID_ViewModel = 0x373a6339,
        PID_MouseWorldCoord = 0x6fbc4e30,
        PID_COUNT = 2
    };

protected:
    epiVec2f GetMouseWorldCoord_Callback() const;

protected:
    dvVMPlot* m_ViewModel{nullptr};

EPI_GENREGION_END(uiPlotTimeline)

public:
    void Update() override;
    void Draw(uiContext& uiContext) override;

    void OnMousePrimary(uiMouseAction action) override;
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
