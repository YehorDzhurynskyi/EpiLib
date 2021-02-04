EPI_GENREGION_BEGIN(include)
#include "EpiUI/ViewModel/uiVMPropertyCheckboxBoolean.h"
#include "EpiUI/ViewModel/uiVMPropertyCheckboxBoolean.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

uiVMPropertyCheckboxBoolean::uiVMPropertyCheckboxBoolean(const epiPropertyPointer& prtyPtr)
    : super(prtyPtr)
{
}

void uiVMPropertyCheckboxBoolean::SetValue_Callback(epiBool value)
{
    epiAssert(m_PrtyPtr.GetTypeID() == MetaType::TypeOf<epiBool>());
    m_PrtyPtr.Set<epiBool>(value);
}

epiBool uiVMPropertyCheckboxBoolean::GetValue_Callback() const
{
    epiAssert(m_PrtyPtr.GetTypeID() == MetaType::TypeOf<epiBool>());
    return m_PrtyPtr.Get<epiBool>();
}

EPI_NAMESPACE_END()
