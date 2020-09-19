#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiUI/Plot/uiPlotDrawArea.hxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/Plot/Drawer/dvDrawerPlotDrawArea.h"

#include "EpiUI/uiWidget.h"

EPI_NAMESPACE_BEGIN()

class uiPlotDrawArea : public uiWidget
{
EPI_GENREGION_BEGIN(uiPlotDrawArea)

EPI_GENHIDDEN_uiPlotDrawArea()

public:
    constexpr static epiMetaTypeID TypeID{0xd59f47f1};

    enum uiPlotDrawArea_PIDs
    {
        PID_ViewModel = 0x373a6339,
        PID_MouseWorldCoord = 0x6fbc4e30,
        PID_COUNT = 2
    };

protected:
    epiVec2f GetMouseWorldCoord_Callback() const;

protected:
    dvVMPlot* m_ViewModel{nullptr};

EPI_GENREGION_END(uiPlotDrawArea)

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
    dvDrawerPlotDrawArea m_DrawerDrawArea;
};

EPI_NAMESPACE_END()
