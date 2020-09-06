#pragma once

#include "EpiData/Series/dSeriesY.h"
#include "EpiData/Series/dSeriesXY.h"
#include "EpiData/Series/dSeriesYComplex.h"

EPI_NAMESPACE_BEGIN()

class spMath final
{
public:
    static dSeriesYComplex DFT_Real(const dSeriesY& series);

    static dSeriesY IDFT_Real(const dSeriesYComplex& series);
    static dSeriesY IDFT_Real(const dSeriesYComplex& series, epiSize_t N);
};

EPI_NAMESPACE_END()
