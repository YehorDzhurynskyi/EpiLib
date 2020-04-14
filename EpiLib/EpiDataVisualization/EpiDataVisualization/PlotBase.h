#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/PlotBase.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"
#include "EpiCore/Color.h"

EPI_NAMESPACE_BEGIN()

class PlotBase : public Object
{
EPI_GENREGION_BEGIN(PlotBase)
public:
    EPI_GENHIDDEN_PlotBase()

    constexpr static MetaTypeID TypeID{0xc8207ffd};

    enum PlotBase_PIDs
    {
        PID_Size = 0x57f28b54,
        PID_BGColor = 0x3d10110a,
        PID_COUNT = 2
    };

protected:
    epiVec2f m_Size;
    Color m_BGColor;

EPI_GENREGION_END(PlotBase)

public:
    void Translate(epiVec2f dPos);
    void Rotate(epiFloat dRot);
};

EPI_NAMESPACE_END()
