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
        PID_MouseWorldCoord = 0x6fbc4e30,
        PID_COUNT = 2
    };

protected:
    epiVec2f GetMouseWorldCoord_Callback() const;

protected:
    dvViewModelPlotBase m_ViewModel;

EPI_GENREGION_END(dvViewPlotBase)

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
