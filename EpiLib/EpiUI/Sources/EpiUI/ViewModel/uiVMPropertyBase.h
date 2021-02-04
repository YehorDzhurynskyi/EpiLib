#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiUI/ViewModel/uiVMPropertyBase.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"
#include "EpiCore/ObjectModel/Property/epiPropertyPointer.h"

EPI_NAMESPACE_BEGIN()

class uiVMPropertyBase : public Object
{
EPI_GENREGION_BEGIN(uiVMPropertyBase)

EPI_GENHIDDEN_uiVMPropertyBase()

public:
    constexpr static epiMetaTypeID TypeID{0xd49507c9};

    enum uiVMPropertyBase_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(uiVMPropertyBase)

public:
    uiVMPropertyBase(const epiPropertyPointer& prtyPtr);

    const epiPropertyPointer& GetPrtyPtr() const;
    epiPropertyPointer& GetPrtyPtr();

protected:
    epiPropertyPointer m_PrtyPtr;
};

EPI_NAMESPACE_END()
