EPI_GENREGION_BEGIN(include)
#include "EpiUI/ViewModel/uiVMPropertyBase.h"
#include "EpiUI/ViewModel/uiVMPropertyBase.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

uiVMPropertyBase::uiVMPropertyBase(const epiPropertyPointer& prtyPtr)
    : m_PrtyPtr{prtyPtr}
{
}

const epiPropertyPointer& uiVMPropertyBase::GetPrtyPtr() const
{
    return m_PrtyPtr;
}

epiPropertyPointer& uiVMPropertyBase::GetPrtyPtr()
{
    return m_PrtyPtr;
}

EPI_NAMESPACE_END()
