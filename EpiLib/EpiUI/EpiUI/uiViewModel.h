#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiUI/uiViewModel.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class uiViewModel : public Object
{
EPI_GENREGION_BEGIN(uiViewModel)
public:
    EPI_GENHIDDEN_uiViewModel()

    constexpr static MetaTypeID TypeID{0x18331770};

    enum uiViewModel_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(uiViewModel)
};

EPI_NAMESPACE_END()
