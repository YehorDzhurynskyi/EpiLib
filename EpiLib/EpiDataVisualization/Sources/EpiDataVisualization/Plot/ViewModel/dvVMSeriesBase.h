#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Plot/ViewModel/dvVMSeriesBase.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/Color.h"

EPI_NAMESPACE_BEGIN()

class dSeriesBase;
class dvVMSeriesBase : public Object
{
EPI_GENREGION_BEGIN(dvVMSeriesBase)

EPI_GENHIDDEN_dvVMSeriesBase()

public:
    constexpr static epiMetaTypeID TypeID{0x83449d66};

    enum dvVMSeriesBase_PIDs
    {
        PID_Model = 0x16545ddd,
        PID_Color = 0xa79767ed,
        PID_COUNT = 2
    };

protected:
    dSeriesBase* m_Model{nullptr};
    Color m_Color{};

EPI_GENREGION_END(dvVMSeriesBase)
};

EPI_NAMESPACE_END()
