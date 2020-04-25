#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/ViewModel/dvViewModelPlot.hxx"
EPI_GENREGION_END(include)

#include "EpiUI/uiViewModel.h"

EPI_NAMESPACE_BEGIN()

class dvViewModelSeriesBase;
class dvViewModelPlot : public uiViewModel
{
EPI_GENREGION_BEGIN(dvViewModelPlot)
public:
    EPI_GENHIDDEN_dvViewModelPlot()

    constexpr static MetaTypeID TypeID{0x46670485};

    enum dvViewModelPlot_PIDs
    {
        PID_ClipLeft = 0xa31e15e1,
        PID_ClipTop = 0xb1714a23,
        PID_ClipRight = 0x20773762,
        PID_ClipBottom = 0x30ad1bef,
        PID_ZoomX = 0x21ac8713,
        PID_ZoomY = 0x56abb785,
        PID_WorkingBox = 0x3cf1ba0c,
        PID_Series = 0x3dbc041b,
        PID_ClipBox = 0xa7011dd3,
        PID_Origin = 0xd95d5328,
        PID_Zoom = 0x1719d64a,
        PID_COUNT = 11
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
    epiRect2f GetWorkingBox_Callback() const;

protected:
    epiPtrArray<dvViewModelSeriesBase> m_Series;
    epiRect2f m_ClipBox;
    epiVec2f m_Origin;
    epiVec2f m_Zoom;

EPI_GENREGION_END(dvViewModelPlot)

public:
    template<typename T, typename ...Args>
    T& Add(Args&& ...args)
    {
        static_assert(std::is_base_of_v<dvViewModelSeriesBase, T>);
        return *static_cast<T*>(m_Series.PushBack(new T(std::forward<Args&&>(args)...)));
    }
};

EPI_NAMESPACE_END()
