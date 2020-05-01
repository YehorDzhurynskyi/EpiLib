#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/View/dvViewPlotDrawArea.hxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/Drawer/dvDrawerPlotDrawArea.h"

#include "EpiUI/uiWidget.h"

EPI_NAMESPACE_BEGIN()

class dvViewPlotDrawArea : public uiWidget
{
EPI_GENREGION_BEGIN(dvViewPlotDrawArea)
public:
    EPI_GENHIDDEN_dvViewPlotDrawArea()

    constexpr static MetaTypeID TypeID{0xcb0bf25c};

    enum dvViewPlotDrawArea_PIDs
    {
        PID_ViewModel = 0x373a6339,
        PID_MouseWorldCoord = 0x6fbc4e30,
        PID_COUNT = 2
    };

protected:
    epiVec2f GetMouseWorldCoord_Callback() const;

protected:
    dvViewModelPlot* m_ViewModel{nullptr};

EPI_GENREGION_END(dvViewPlotDrawArea)

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
    dvDrawerPlotDrawArea m_Drawer;
};

EPI_NAMESPACE_END()
