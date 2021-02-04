#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiUI/ViewModel/uiVMPropertyCheckboxBoolean.hxx"
EPI_GENREGION_END(include)

#include "EpiUI/ViewModel/uiVMPropertyBase.h"

EPI_NAMESPACE_BEGIN()

class uiVMPropertyCheckboxBoolean : public uiVMPropertyBase
{
EPI_GENREGION_BEGIN(uiVMPropertyCheckboxBoolean)

EPI_GENHIDDEN_uiVMPropertyCheckboxBoolean()

public:
    constexpr static epiMetaTypeID TypeID{0x3f445053};

    enum uiVMPropertyCheckboxBoolean_PIDs
    {
        PID_Value = 0xdcb67730,
        PID_COUNT = 1
    };

protected:
    epiBool GetValue_Callback() const;
    void SetValue_Callback(epiBool value);

EPI_GENREGION_END(uiVMPropertyCheckboxBoolean)

public:
    uiVMPropertyCheckboxBoolean(const epiPropertyPointer& prtyPtr);
};

EPI_NAMESPACE_END()
