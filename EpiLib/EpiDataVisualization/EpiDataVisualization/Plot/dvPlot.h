#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Plot/dvPlot.hxx"
EPI_GENREGION_END(include)

#include "EpiDataVisualization/Plot/Series/dvSeriesBase.h"

#include "EpiCore/ObjectModel/Object.h"
#include "EpiCore/Containers/Array.h"

EPI_NAMESPACE_BEGIN()

class dvPlot : public Object
{
EPI_GENREGION_BEGIN(dvPlot)
public:
    EPI_GENHIDDEN_dvPlot()

    constexpr static MetaTypeID TypeID{0x6bf8062b};

    enum dvPlot_PIDs
    {
        PID_Series = 0x3dbc041b,
        PID_COUNT = 1
    };

protected:
    epiPtrArray<dvSeriesBase> m_Series;

EPI_GENREGION_END(dvPlot)

public:
    template<typename T, typename ...Args>
    T& Add(Args&& ...args)
    {
        static_assert(std::is_base_of_v<dvSeriesBase, T>);
        return *static_cast<T*>(m_Series.PushBack(new T(std::forward<Args&&>(args)...)));
    }
};

EPI_NAMESPACE_END()
