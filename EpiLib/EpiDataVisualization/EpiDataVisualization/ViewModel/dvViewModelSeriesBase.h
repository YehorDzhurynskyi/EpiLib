#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/ViewModel/dvViewModelSeriesBase.hxx"
EPI_GENREGION_END(include)

#include "EpiUI/uiViewModel.h"

#include "EpiCore/Color.h"

EPI_NAMESPACE_BEGIN()

class dvSeriesBase;
class dvViewModelSeriesBase : public uiViewModel
{
EPI_GENREGION_BEGIN(dvViewModelSeriesBase)
public:
    EPI_GENHIDDEN_dvViewModelSeriesBase()

    constexpr static MetaTypeID TypeID{0xd973e2d9};

    enum dvViewModelSeriesBase_PIDs
    {
        PID_Model = 0x16545ddd,
        PID_Color = 0xa79767ed,
        PID_COUNT = 2
    };

protected:
    dvSeriesBase* m_Model{nullptr};
    Color m_Color;

EPI_GENREGION_END(dvViewModelSeriesBase)
};

EPI_NAMESPACE_END()
