#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Plot/dvPlotBase.hxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/Plot/Series/dvSeriesBase.h"

#include "EpiCore/ObjectModel/Object.h"
#include "EpiCore/Containers/Array.h"

EPI_NAMESPACE_BEGIN()

class dvPlotBase : public Object
{
EPI_GENREGION_BEGIN(dvPlotBase)
public:
    EPI_GENHIDDEN_dvPlotBase()

    constexpr static MetaTypeID TypeID{0x153dd6b7};

    enum dvPlotBase_PIDs
    {
        PID_RangeX = 0xbf8d4d13,
        PID_RangeY = 0xc88a7d85,
        PID_ClipBox = 0xa7011dd3,
        PID_Series = 0x3dbc041b,
        PID_COUNT = 4
    };

protected:
    epiVec2f GetRangeX_Callback() const;
    void SetRangeX_Callback(const epiVec2f& value);
    epiVec2f GetRangeY_Callback() const;
    void SetRangeY_Callback(const epiVec2f& value);

protected:
    epiRect2f m_ClipBox;
    epiPtrArray<dvSeriesBase> m_Series;

EPI_GENREGION_END(dvPlotBase)
};

EPI_NAMESPACE_END()
