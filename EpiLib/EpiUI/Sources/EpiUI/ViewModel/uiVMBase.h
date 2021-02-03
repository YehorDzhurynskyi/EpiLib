#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiUI/ViewModel/uiVMBase.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"
#include "EpiCore/ObjectModel/Property/epiPropertyPointer.h"

EPI_NAMESPACE_BEGIN()

class uiVMBase : public Object
{
EPI_GENREGION_BEGIN(uiVMBase)

EPI_GENHIDDEN_uiVMBase()

public:
    constexpr static epiMetaTypeID TypeID{0xa4cab0fa};

    enum uiVMBase_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(uiVMBase)

public:
    uiVMBase(const epiPropertyPointer& prtyPtr);

protected:
    epiPropertyPointer m_PrtyPtr;
};

EPI_NAMESPACE_END()
