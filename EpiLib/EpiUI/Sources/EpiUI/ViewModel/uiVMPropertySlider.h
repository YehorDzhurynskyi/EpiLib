#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiUI/ViewModel/uiVMPropertySlider.hxx"
EPI_GENREGION_END(include)

#include "EpiUI/ViewModel/uiVMPropertyBase.h"

EPI_NAMESPACE_BEGIN()

class uiVMPropertySlider : public uiVMPropertyBase
{
EPI_GENREGION_BEGIN(uiVMPropertySlider)

EPI_GENHIDDEN_uiVMPropertySlider()

public:
    constexpr static epiMetaTypeID TypeID{0x6d78787f};

    enum uiVMPropertySlider_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(uiVMPropertySlider)

public:
    uiVMPropertySlider(const epiPropertyPointer& prtyPtr);
};

EPI_NAMESPACE_END()
