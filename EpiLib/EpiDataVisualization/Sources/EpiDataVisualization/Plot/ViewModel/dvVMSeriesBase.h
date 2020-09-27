#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Plot/ViewModel/dvVMSeriesBase.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/Color.h"

EPI_NAMESPACE_BEGIN()

class dvVMSeriesBase : public Object
{
EPI_GENREGION_BEGIN(dvVMSeriesBase)

EPI_GENHIDDEN_dvVMSeriesBase()

public:
    constexpr static epiMetaTypeID TypeID{0x83449d66};

    enum dvVMSeriesBase_PIDs
    {
        PID_Color1 = 0x5dc0e615,
        PID_Color2 = 0xc4c9b7af,
        PID_Color = 0xa79767ed,
        PID_Z = 0x59bc5767,
        PID_COUNT = 4
    };

protected:
    void SetColor_Callback(const Color& value);

protected:
    Color m_Color1{};
    Color m_Color2{};
    epiFloat m_Z{-0.99f};

EPI_GENREGION_END(dvVMSeriesBase)
};

EPI_NAMESPACE_END()
