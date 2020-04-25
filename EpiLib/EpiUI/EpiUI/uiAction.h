#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiUI/uiAction.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

// TODO: move to epi
enum class MouseAction
{
    Release,
    Click,
    DClick
};

class uiAction : public Object
{
EPI_GENREGION_BEGIN(uiAction)
public:
    EPI_GENHIDDEN_uiAction()

    constexpr static MetaTypeID TypeID{0x6e1e61ac};

    enum uiAction_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(uiAction)
};

EPI_NAMESPACE_END()
