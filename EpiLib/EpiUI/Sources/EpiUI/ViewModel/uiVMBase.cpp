EPI_GENREGION_BEGIN(include)
#include "EpiUI/ViewModel/uiVMBase.h"
#include "EpiUI/ViewModel/uiVMBase.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

uiVMBase::uiVMBase(const epiPropertyPointer& prtyPtr)
    : m_PrtyPtr{prtyPtr}
{
}

EPI_NAMESPACE_END()
