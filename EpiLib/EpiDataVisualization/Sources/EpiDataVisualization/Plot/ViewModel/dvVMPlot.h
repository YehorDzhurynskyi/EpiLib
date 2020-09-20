#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Plot/ViewModel/dvVMPlot.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class dvVMSeriesBase;
class dvVMPlot : public Object
{
EPI_GENREGION_BEGIN(dvVMPlot)

EPI_GENHIDDEN_dvVMPlot()

public:
    constexpr static epiMetaTypeID TypeID{0xfb421c80};

    enum dvVMPlot_PIDs
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
    epiPtrArray<dvVMSeriesBase> m_Series{};
    epiRect2f m_BBox{};
    epiVec2f m_Origin{};
    epiVec2f m_Zoom{};

EPI_GENREGION_END(dvVMPlot)

public:
    dvVMPlot();
    dvVMPlot(const dvVMPlot& rhs) = default;
    dvVMPlot& operator=(const dvVMPlot& rhs) = default;
    dvVMPlot(dvVMPlot&& rhs) = default;
    dvVMPlot& operator=(dvVMPlot&& rhs) = default;
    ~dvVMPlot() = default;

public:
    template<typename T, typename ...Args>
    T& Add(Args&& ...args);
};

template<typename T, typename ...Args>
T& dvVMPlot::Add(Args&& ...args)
{
    static_assert(std::is_base_of_v<dvVMSeriesBase, T>);
    return *static_cast<T*>(m_Series.PushBack(new T(std::forward<Args&&>(args)...)));
}

EPI_NAMESPACE_END()
