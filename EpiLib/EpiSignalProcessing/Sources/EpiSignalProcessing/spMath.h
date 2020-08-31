#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiSignalProcessing/spMath.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiData/Series/dSeriesY.h"
#include "EpiData/Series/dSeriesXY.h"
#include "EpiData/Series/dSeriesXYComplex.h"

EPI_NAMESPACE_BEGIN()

class spMath : public Object
{
EPI_GENREGION_BEGIN(spMath)

EPI_GENHIDDEN_spMath()

public:
    constexpr static MetaTypeID TypeID{0xedf74a6c};

    enum spMath_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(spMath)

public:
    static dSeriesXYComplex DFT(const dSeriesY& series);
    static dSeriesXYComplex DFT(const dSeriesXY& series);
    static dSeriesXYComplex IDFT(const dSeriesXY& series);
};

EPI_NAMESPACE_END()
