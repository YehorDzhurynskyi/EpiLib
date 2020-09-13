#pragma once

#include "EpiData/Series/dSeries1Df.h"
#include "EpiData/Series/dSeries1Dc.h"

EPI_NAMESPACE_BEGIN()

class spMath final
{
public:
    static dSeries1Dc DFT_Real(const dSeries1Df& series);

    static dSeries1Df IDFT_Real(const dSeries1Dc& series);
    static dSeries1Df IDFT_Real(const dSeries1Dc& series, epiSize_t N);
};

EPI_NAMESPACE_END()
