EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Plot/ViewModel/dvVMSeriesBase.h"
#include "EpiDataVisualization/Plot/ViewModel/dvVMSeriesBase.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

void dvVMSeriesBase::SetColor_Callback(const Color& value)
{
    SetColor1(value);
    SetColor2(value);
}

EPI_NAMESPACE_END()
