#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Plot/ViewModel/dvVMSeries1Df.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiDataVisualization/Plot/ViewModel/dvVMSeriesBase.h"

EPI_NAMESPACE_BEGIN()

enum class dvSeries1DfRepr : epiS32
{
EPI_GENREGION_BEGIN(dvSeries1DfRepr)
    Peak = 0
EPI_GENREGION_END(dvSeries1DfRepr)
};

class dSeries1Df;
class dvVMSeries1Df : public dvVMSeriesBase
{
EPI_GENREGION_BEGIN(dvVMSeries1Df)

EPI_GENHIDDEN_dvVMSeries1Df()

public:
    constexpr static epiMetaTypeID TypeID{0x4beb3351};

    enum dvVMSeries1Df_PIDs
    {
        PID_Series = 0x3dbc041b,
        PID_Repr = 0x9f687818,
        PID_COUNT = 2
    };

protected:
    dSeries1Df* m_Series{nullptr};
    dvSeries1DfRepr m_Repr{dvSeries1DfRepr::Peak};

EPI_GENREGION_END(dvVMSeries1Df)
};

EPI_NAMESPACE_END()
