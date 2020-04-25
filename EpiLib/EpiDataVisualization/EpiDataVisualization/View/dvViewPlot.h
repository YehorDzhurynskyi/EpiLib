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
public:
    EPI_GENHIDDEN_dvViewPlot()

    constexpr static MetaTypeID TypeID{0x195ed8c9};

    enum dvViewPlot_PIDs
    {
        PID_ViewModel = 0x373a6339,
        PID_MouseWorldCoord = 0x6fbc4e30,
        PID_COUNT = 2
    };

protected:
    epiVec2f GetMouseWorldCoord_Callback() const;

protected:
    dvViewModelPlot m_ViewModel;

EPI_GENREGION_END(dvViewPlot)

public:
    void Update() override;

    void OnMousePrimary(MouseAction action) override;
    void OnMouseWheel(epiFloat dZoom) override;

private:
    epiVec2f CalcMouseWorldCoord(const epiVec2f& origin) const;

private:
    epiBool m_MouseDragActive;
    epiVec2f m_MouseDragPosition;
    epiVec2f m_MouseDragOrigin;
};

EPI_NAMESPACE_END()
