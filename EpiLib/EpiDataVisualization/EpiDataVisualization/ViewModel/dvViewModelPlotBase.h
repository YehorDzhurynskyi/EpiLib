#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/ViewModel/dvViewModelPlotBase.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class dvViewModelPlotBase : public Object
{
EPI_GENREGION_BEGIN(dvViewModelPlotBase)
public:
    EPI_GENHIDDEN_dvViewModelPlotBase()

    constexpr static MetaTypeID TypeID{0x80ba64f};

    enum dvViewModelPlotBase_PIDs
    {
        PID_ClipLeft = 0xa31e15e1,
        PID_ClipTop = 0xb1714a23,
        PID_ClipRight = 0x20773762,
        PID_ClipBottom = 0x30ad1bef,
        PID_ZoomX = 0x21ac8713,
        PID_ZoomY = 0x56abb785,
        PID_ClipBox = 0xa7011dd3,
        PID_Origin = 0xd95d5328,
        PID_Zoom = 0x1719d64a,
        PID_COUNT = 9
    };

protected:
    epiFloat GetClipLeft_Callback() const;
    void SetClipLeft_Callback(epiFloat value);
    epiFloat GetClipTop_Callback() const;
    void SetClipTop_Callback(epiFloat value);
    epiFloat GetClipRight_Callback() const;
    void SetClipRight_Callback(epiFloat value);
    epiFloat GetClipBottom_Callback() const;
    void SetClipBottom_Callback(epiFloat value);
    epiFloat GetZoomX_Callback() const;
    void SetZoomX_Callback(epiFloat value);
    epiFloat GetZoomY_Callback() const;
    void SetZoomY_Callback(epiFloat value);

protected:
    epiRect2f m_ClipBox;
    epiVec2f m_Origin;
    epiVec2f m_Zoom;

EPI_GENREGION_END(dvViewModelPlotBase)
};

EPI_NAMESPACE_END()
