#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiUI/Plot/uiPlot.hxx"
EPI_GENREGION_END(include)

#include "EpiUI/uiWidget.h"

#include "EpiDataVisualization/Plot/ViewModel/dvVMPlot.h"

EPI_NAMESPACE_BEGIN()

class uiPlot : public uiWidget
{
EPI_GENREGION_BEGIN(uiPlot)

EPI_GENHIDDEN_uiPlot()

public:
    constexpr static epiMetaTypeID TypeID{0x41c2d746};

    enum uiPlot_PIDs
    {
        PID_ViewModel = 0x373a6339,
        PID_COUNT = 1
    };

protected:
    dvVMPlot m_ViewModel{};

EPI_GENREGION_END(uiPlot)

public:
    uiPlot();
};

EPI_NAMESPACE_END()
