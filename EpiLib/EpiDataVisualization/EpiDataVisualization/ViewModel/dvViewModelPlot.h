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
        PID_ClipBox = 0xa7011dd3,
        PID_Series = 0x3dbc041b,
        PID_BBox = 0xdffc9862,
        PID_Origin = 0xd95d5328,
        PID_Zoom = 0x1719d64a,
        PID_COUNT = 5
    };

protected:
    epiRect2f GetClipBox_Callback() const;
    void SetClipBox_Callback(const epiRect2f& value);
    void SetOrigin_Callback(const epiVec2f& value);
    void SetZoom_Callback(const epiVec2f& value);

protected:
    epiPtrArray<dvViewModelSeriesBase> m_Series;
    epiRect2f m_BBox;
    epiVec2f m_Origin;
    epiVec2f m_Zoom;

EPI_GENREGION_END(dvViewModelPlot)

public:
    dvViewModelPlot();
    dvViewModelPlot(const dvViewModelPlot& rhs) = default;
    dvViewModelPlot& operator=(const dvViewModelPlot& rhs) = default;
    dvViewModelPlot(dvViewModelPlot&& rhs) = default;
    dvViewModelPlot& operator=(dvViewModelPlot&& rhs) = default;
    ~dvViewModelPlot() = default;

public:
    template<typename T, typename ...Args>
    T& Add(Args&& ...args)
    {
        static_assert(std::is_base_of_v<dvViewModelSeriesBase, T>);
        return *static_cast<T*>(m_Series.PushBack(new T(std::forward<Args&&>(args)...)));
    }
};

EPI_NAMESPACE_END()
